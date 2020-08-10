from datetime import datetime
import logging
from logging.handlers import RotatingFileHandler
import os
from pathlib import Path
from shutil import copyfile

from git import Repo
import requests

LOG_PATH = os.getenv("LOG_PATH", "/var/log/gallery.log")

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger("GALLERY")
handler = RotatingFileHandler(LOG_PATH, maxBytes=1024 * 1024 * 10, backupCount=3)
logger.addHandler(handler)

GITLAB_GROUP = os.getenv("GITLAB_GROUP")
GITLAB_TOKEN = os.getenv("GITLAB_TOKEN")
GITLAB_USER = os.getenv("GITLAB_USER")
GALLERY_PROJECTS = {"query": "{ group(fullPath: \"" + GITLAB_GROUP
                             + "\") { id name projects { nodes { name description id } } } }"}
TEMPORARY_LOCATION = "/tmp"

MAX_REPO_SIZE = 9900000000 # 9.9GB
MEDIA_FILES = ["jpg", "jpeg", "png", "mov"]
REPO_FULL_MARKER = "REPO_FULL"
REPO_DESCRIPTOR = "repo.descriptor"


class GitlabClient:
    def __init__(self, private_token):
        self.api_url = "https://gitlab.com/api/v4"
        self.graphql_url = "https://gitlab.com/api/graphql"
        self.private_token = private_token
        self.headers = {
            "Authorization": "Bearer {}".format(self.private_token),
            "Content-Type": "application/json"
        }

    def list_projects_in_group(self):
        response = requests.post(
            url=self.graphql_url,
            params=GALLERY_PROJECTS,
            headers=self.headers
        )
        response.raise_for_status()

        group = response.json()['data']['group']
        nodes = group['projects']['nodes']

        return {
            "groupId": group["id"].split("/")[-1],
            "projects":
                [
                    {
                        "id": x["id"].split("/")[-1],
                        "name": x["name"],
                        "full": x["description"] and REPO_FULL_MARKER in x["description"]
                    }
                    for x in nodes
                ]
        }

    def get_repo_descriptor(self, repo_id):
        response = requests.get(
            url="{}/projects/{}/repository/files/{}/raw?ref=master".format(self.api_url, repo_id, REPO_DESCRIPTOR),
            headers=self.headers
        )
        response.raise_for_status()

        return response.text

    def add_project_in_group(self, project_name, group_id):
        response = requests.post(
            url="{}/projects".format(self.api_url),
            headers=self.headers,
            params={
                "name": project_name,
                "namespace_id": group_id
            }
        )
        response.raise_for_status()

    def set_project_description(self, project_id, description):
        response = requests.put(
            url="{}/projects/{}".format(self.api_url, project_id),
            headers=self.headers,
            params={
                "description": description
            }
        )
        response.raise_for_status()


def clone_repo(repo_name, repo_dir):
    new_project_path = os.path.join(repo_dir, repo_name)
    Repo.clone_from(
        "https://gitlab-ci-token:{}@gitlab.com/{}/{}.git".format(GITLAB_TOKEN, GITLAB_GROUP.lower(), repo_name),
        new_project_path)

    return new_project_path


def clone_repos(gitlab_client, projects_in_group):
    repo_dirs = []

    for repo in projects_in_group["projects"]:
        name = repo['name']
        full = repo['full']
        id = repo["id"]
        repo_dir = os.path.join(TEMPORARY_LOCATION, name)

        if full:
            if not os.path.exists(repo_dir):
                Path(repo_dir).mkdir()

            with open(os.path.join(repo_dir, REPO_DESCRIPTOR)) as f:
                f.write(gitlab_client.get_repo_descriptor(id))
        else:
            if not os.path.isdir(repo_dir):
                repo_dir = clone_repo(name, TEMPORARY_LOCATION)

        repo_dirs.append(repo_dir)

    return repo_dirs


def directory_size(src):
    path = Path(src)
    return sum(f.stat().st_size for f in path.glob('**/*') if f.is_file())


def is_media_file(f):
    file_name = f.name.lower()

    for media_file in MEDIA_FILES:
        if file_name.endswith(media_file):
            return True

    return False


def fill_in_repo(src, f, repo_dir, file_hashes):
    git = Repo.init(TEMPORARY_LOCATION, bare=True).git
    old_path = str(f.resolve())

    repo_size = MAX_REPO_SIZE - directory_size(repo_dir)

    logger.debug("Repo {} size before changes {}".format(repo_dir, repo_size))

    if f.is_file() and is_media_file(f):
        current_file_hash = git.hash_object(f.absolute())
        previous_file = file_hashes.get(current_file_hash)
        if previous_file:
            logger.info("File {} already exists under {}".format(old_path, previous_file))
            return True

        new_path = old_path.replace(src, repo_dir)
        logger.info("Copying file from {} to {}".format(old_path, new_path))
        repo_size -= f.stat().st_size
        if repo_size <= 0:
            logger.info("File not copied, as repo size exceeds maximum")
            return False

        new_dir = os.path.dirname(new_path)
        if not os.path.exists(new_dir):
            logger.info("Creating directory structure {}".format(new_dir))
            os.makedirs(new_dir)

        copyfile(old_path, new_path)
        logger.info("File {} created.".format(new_path))

    return True


def create_and_clone_repo(gitlab_client, group_id, dst_dir):
    project_name = "gal" + datetime.now().strftime("%Y%m%d%H%M%S")
    logger.info("Creating new repository {} in group {}".format(project_name, group_id))
    gitlab_client.add_project_in_group(project_name, group_id)

    return clone_repo(project_name, dst_dir)


def commit_repo_descriptor(repo_dir):
    git = Repo.init(repo_dir, bare=True).git
    git.index.add(["."])
    git.index.commit("Add images.")
    ls = git.ls_files("-s").splitlines()
    descriptor_path = os.path.join(repo_dir, REPO_DESCRIPTOR)

    with open(descriptor_path, "w") as f:
        for line in ls:
            if len(line.split()) != 4:
                continue

            _, git_hash, _, file_path = line.split()
            f.write("{} {}\n".format(git_hash, file_path))

    git.index.add(["."])
    git.index.commit("Modify repo descriptors.")


def load_hashes_from_repo_descriptors(src, projects_in_group):
    file_hashes = {}
    for project in projects_in_group["projects"]:
        repo_descriptor_path = Path(os.path.join(src, project["name"], REPO_DESCRIPTOR))
        if not repo_descriptor_path.exists():
            continue

        with open(repo_descriptor_path) as f:
            lines = f.readlines()
            for line in lines:
                git_hash, path = line.split()
                file_hashes["git_hash"] = path

    return file_hashes


def ensure_temporary_location_exists():
    if os.path.exists(TEMPORARY_LOCATION):
        if not os.path.isdir(TEMPORARY_LOCATION):
            raise FileExistsError("{} already exists but is not a directory.".format(TEMPORARY_LOCATION))
        return

    os.makedirs(TEMPORARY_LOCATION)


def get_current_project(projects_in_group):
    return next(filter(lambda x: not x["full"], projects_in_group["projects"]))


def close_repo(gitlab_client, project_id):
    gitlab_client.set_project_description(project_id, )


def execute(src, dst_dir):
    ensure_temporary_location_exists()

    gitlab_client = GitlabClient(GITLAB_TOKEN)
    projects_in_group = gitlab_client.list_projects_in_group()
    clone_repos(gitlab_client, projects_in_group)
    file_hashes = load_hashes_from_repo_descriptors(src, projects_in_group)

    group_id = projects_in_group["groupId"]
    path = Path(src)
    project = get_current_project(projects_in_group)

    for f in path.glob('**/*'):
        repo_dir = os.path.join(dst_dir, project["name"])
        if not fill_in_repo(src, f, repo_dir, file_hashes):
            commit_repo_descriptor(repo_dir)
            close_repo(gitlab_client, project["id"])
            repo_dir = create_and_clone_repo(gitlab_client, group_id, dst_dir)
            fill_in_repo(src, f, repo_dir, file_hashes)


if __name__ == "__main__":
    # recreate_repo_descriptor("/tmp/gal202007190433")
    execute("/home/sabina/workspace/photos", TEMPORARY_LOCATION)
