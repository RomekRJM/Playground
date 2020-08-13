from datetime import datetime
import logging
from logging.handlers import RotatingFileHandler
import os
from pathlib import Path
from shutil import copyfile

from git import Repo, RemoteProgress
import requests


def sanitize_path(path):
    return path[:-1] if path and path.endswith("/") else path


LOG_PATH = os.getenv("LOG_PATH", "/var/log/gallery.log")

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s %(name)-9s %(levelname)-8s %(message)s'
)
logger = logging.getLogger("GALLERY")
handler = RotatingFileHandler(LOG_PATH, maxBytes=1024 * 1024 * 10, backupCount=3)
logger.addHandler(handler)

GITLAB_GROUP = os.getenv("GITLAB_GROUP")
GITLAB_TOKEN = os.getenv("GITLAB_TOKEN")
GITLAB_USER = os.getenv("GITLAB_USER")
SOURCE_LOCATION = sanitize_path(os.getenv("SOURCE_LOCATION"))
GALLERY_PROJECTS = {"query": "{ group(fullPath: \"" + GITLAB_GROUP
                             + "\") { id name projects { nodes { name description id } } } }"}
TEMPORARY_LOCATION = sanitize_path("/home/sabina/tmp")

MAX_REPO_SIZE = 4950000000  # 4.95GiB as git will double that in .git/ and gitlab has 10GiB / repo limit
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
                "namespace_id": group_id,
                "visibility": "private"
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

    def add_group(self, group_name):
        response = requests.post(
            url="{}/groups".format(self.api_url),
            headers=self.headers,
            params={
                "name": group_name,
                "path": group_name
            }
        )
        response.raise_for_status()

    def get_group(self, group_name):
        response = requests.get(
            url="{}/groups".format(self.api_url),
            headers=self.headers,
            params={
                "name": group_name
            }
        )
        response.raise_for_status()

        return response.json()


class ProgressLogger(RemoteProgress):
    def __init__(self):
        super().__init__()
        self.last_update = datetime.now()

    def update(self, op_code, cur_count, max_count=None, message=''):
        _cur_count = int(float(cur_count))
        _max_count = int(float(max_count or 100.0))
        _percentage = min(cur_count * 100 / (max_count or 100.0), 100)
        _op_code = self.__to_text(op_code)

        logger.info("{} {}/{} {}% {}".format(_op_code, _cur_count, _max_count, _percentage, message))

        update_time = (datetime.now() - self.last_update).total_seconds()

        if update_time > 30:
            for han in logger.handlers:
                han.flush()

            self.last_update = datetime.now()

    @staticmethod
    def __to_text(op_code):
        text = ""
        x = 1
        op_code_names = ["BEGIN", "END", "COUNTING", "COMPRESSING", "WRITING", "RECEIVING", "RESOLVING",
                         "FINDING_SOURCES", "CHECKING_OUT"]

        for o in op_code_names:
            if op_code & x == x:
                text += o + " "

            x = x << 1

        return text


def clone_or_pull_repo(repo_name, repo_dir):
    new_project_path = os.path.join(repo_dir, repo_name)
    progress = ProgressLogger()

    if os.path.exists(new_project_path):
        logger.info("Pulling project {} into {}".format(repo_name, new_project_path))
        Repo(new_project_path).remotes.origin.pull(progress=progress)
    else:
        logger.info("Cloning project {} into {}".format(repo_name, new_project_path))
        Repo.clone_from(
            "https://gitlab-ci-token:{}@gitlab.com/{}/{}.git".format(GITLAB_TOKEN, GITLAB_GROUP.lower(), repo_name),
            new_project_path, progress)

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
                repo_dir = clone_or_pull_repo(name, TEMPORARY_LOCATION)

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

        if f.stat().st_size > MAX_REPO_SIZE:
            logger.error("File {} can not be added as it's to large.".format(old_path))

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

    return clone_or_pull_repo(project_name, dst_dir)


def commit_and_push_repo_with_descriptor(repo_dir):
    repo = Repo.init(repo_dir)
    logger.info("Indexing changes, this might take a while.")
    repo.git.add()
    repo.index.commit("Add images.")
    add_repo_descriptor(repo, repo_dir)
    repo.git.add(["."])
    repo.index.commit("Modify repo descriptors.")
    repo.config_writer().set_value("http", "postBuffer", "52428800").release()
    logger.info("Pushing changes to the remote repo, this might take a while.")
    repo.remotes.origin.push(progress=ProgressLogger())


def add_repo_descriptor(repo, repo_dir):
    ls = repo.git.ls_files("-s").splitlines()
    descriptor_path = os.path.join(repo_dir, REPO_DESCRIPTOR)

    with open(descriptor_path, "w") as f:
        for line in ls:
            if len(line.split("\t")) != 2:
                continue

            data, file_path = line.split("\t")

            if len(data.split()) != 3:
                continue

            _, git_hash, _ = data.split()

            f.write("{}\t{}\n".format(git_hash, file_path))


def load_hashes_from_repo_descriptors(dst_dir, projects_in_group):
    file_hashes = {}
    for project in projects_in_group["projects"]:
        repo_descriptor_path = Path(os.path.join(dst_dir, project["name"], REPO_DESCRIPTOR))
        if not repo_descriptor_path.exists():
            continue

        with open(repo_descriptor_path) as f:
            lines = f.readlines()
            for line in lines:
                git_hash, file_path = line.split("\t")
                file_hashes[git_hash] = file_path.replace("\n", "")

    return file_hashes


def ensure_temporary_location_exists():
    if os.path.exists(TEMPORARY_LOCATION):
        if not os.path.isdir(TEMPORARY_LOCATION):
            raise FileExistsError("{} already exists but is not a directory.".format(TEMPORARY_LOCATION))
        return

    os.makedirs(TEMPORARY_LOCATION)


def ensure_group_exists(gitlab_client, group_name):
    group = gitlab_client.get_group(group_name)

    if not group:
        gitlab_client.add_group(group_name)


def ensure_project_exists_in_group(gitlab_client, dst_dir):
    projects_in_group = gitlab_client.list_projects_in_group()

    if not projects_in_group.get("projects"):
        create_and_clone_repo(gitlab_client, projects_in_group["groupId"], dst_dir)


def get_current_project(projects_in_group):
    return next(filter(lambda x: not x["full"], projects_in_group["projects"]))


def close_repo(gitlab_client, project_id):
    gitlab_client.set_project_description(project_id, REPO_FULL_MARKER)


def execute(src, dst_dir):
    logger.info("Starting script.")
    gitlab_client = GitlabClient(GITLAB_TOKEN)
    ensure_temporary_location_exists()
    ensure_group_exists(gitlab_client, GITLAB_GROUP)
    ensure_project_exists_in_group(gitlab_client, dst_dir)

    projects_in_group = gitlab_client.list_projects_in_group()
    clone_repos(gitlab_client, projects_in_group)
    file_hashes = load_hashes_from_repo_descriptors(dst_dir, projects_in_group)

    group_id = projects_in_group["groupId"]
    path = Path(src)
    project = get_current_project(projects_in_group)

    logger.info("Discovering files and folders to copy from {}. This might take a while.".format(src))

    for f in path.glob('**/*'):
        repo_dir = os.path.join(dst_dir, project["name"])
        if not fill_in_repo(src, f, repo_dir, file_hashes):
            commit_and_push_repo_with_descriptor(repo_dir)
            close_repo(gitlab_client, project["id"])
            repo_dir = create_and_clone_repo(gitlab_client, group_id, dst_dir)
            fill_in_repo(src, f, repo_dir, file_hashes)

    commit_and_push_repo_with_descriptor(repo_dir)


if __name__ == "__main__":
    execute(SOURCE_LOCATION, TEMPORARY_LOCATION)
