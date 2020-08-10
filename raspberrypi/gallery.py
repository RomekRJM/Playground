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
PATH = "/tmp"

MAX_REPO_SIZE = 100000000
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
        repo_dir = os.path.join(PATH, name)

        if full:
            gitlab_client.get_repo_descriptor(id)
        else:
            if not os.path.isdir(repo_dir):
                repo_dir = clone_repo(name, PATH)

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


def fill_in_repo(src, f, dst_dir):
    logger.info("Copying files from {} to {}".format(src, dst_dir))
    git = Repo.init("/tmp", bare=True).git
    old_path = str(f.resolve())

    repo_size = MAX_REPO_SIZE - directory_size(dst_dir)

    logger.debug("Repo {} size before changes {}".format(dst_dir, repo_size))

    if f.is_file() and is_media_file(f):
        new_path = old_path.replace(src, dst_dir)
        logger.info("Copying file from {} to {}".format(old_path, new_path))
        repo_size -= f.stat().st_size
        if repo_size <= 0:
            logger.info("File not copied, as repo size exceeds maximum")
            return False

        current_file_hash = git.hash_object(f.absolute())
        copyfile(old_path, new_path)
        logger.info("File {} created.".format(new_path))

    elif f.is_dir():
        new_path = Path(os.path.join(dst_dir, old_path.replace(src, "")))
        logger.info("Creating directory {}".format(new_path.absolute()))

        if not new_path.exists():
            new_path.mkdir()
            logger.info("Directory already exists")

    return True


def create_and_clone_repo(gitlab_client, group_id, dst_dir):
    project_name = "gal" + datetime.now().strftime("%Y%m%d%H%M%S")
    logger.info("Creating new repository {} in group {}".format(project_name, group_id))
    gitlab_client.add_project_in_group(project_name, group_id)

    return clone_repo(project_name, dst_dir)


def execute(src, dst_dir):
    gitlab_client = GitlabClient(GITLAB_TOKEN)
    projects_in_group = gitlab_client.list_projects_in_group()
    repo_dirs = clone_repos(gitlab_client, projects_in_group)

    group_id = projects_in_group["groupId"]
    path = Path(src)

    for f in path.glob('**/*'):
        if not fill_in_repo(src, f, dst_dir):
            dst_dir = create_and_clone_repo(gitlab_client, group_id, dst_dir)
            fill_in_repo(src, f, dst_dir)


if __name__ == "__main__":
    execute("/home/sabina/workspace/photos", "/tmp")

    print(directory_size("/tmp"))
