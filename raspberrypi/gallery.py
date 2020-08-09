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
handler = RotatingFileHandler(LOG_PATH, maxBytes=1024*1024*10, backupCount=3)
logger.addHandler(handler)


GITLAB_GROUP = os.getenv("GITLAB_GROUP")
GITLAB_TOKEN = os.getenv("GITLAB_TOKEN")
GITLAB_USER = os.getenv("GITLAB_USER")
GALLERY_PROJECTS = {"query":  "{ group(fullPath: \"" + GITLAB_GROUP
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

    def list_projects_in_group(self):
        response = requests.post(
            url=self.graphql_url,
            params=GALLERY_PROJECTS,
            headers={
                "Authorization": "Bearer {}".format(self.private_token),
                "Content-Type": "application/json"
            }
        )
        response.raise_for_status()

        nodes = response.json()['data']['group']['projects']['nodes']

        return [{"id": x["id"].split("/")[-1], "name": x["name"], "description": x["description"]} for x in nodes]

    def get_repo_descriptor(self, repo_id):
        response = requests.get(
            url="{}/projects/{}/repository/files/{}/raw?ref=master".format(self.api_url, repo_id, REPO_DESCRIPTOR),
            headers={
                "Authorization": "Bearer {}".format(self.private_token),
                "Content-Type": "application/json"
            }
        )
        response.raise_for_status()

        return response.text


def clone_repos():
    gitlab_client = GitlabClient(GITLAB_TOKEN)
    projects = gitlab_client.list_projects_in_group()
    repo_dirs = []

    for repo in projects:
        name = repo['name']
        description = repo['description']
        id = repo["id"]
        repo_dir = "{}/{}".format(PATH, name)

        if REPO_FULL_MARKER in description:
            gitlab_client.get_repo_descriptor(id)
        else:
            if not os.path.isdir(repo_dir):
                Repo.clone_from(
                    "https://gitlab-ci-token:{}@gitlab.com/{}/{}.git".format(GITLAB_TOKEN, GITLAB_USER.lower(), repo),
                    repo_dir)

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


def fill_in_repo(src, f, repo_dir):
    logger.info("Copying files from {} to {}".format(src, repo_dir))
    git = Repo.init("/tmp", bare=True).git
    old_path = str(f.resolve())

    repo_size = MAX_REPO_SIZE - directory_size(repo_dir)

    logger.debug("Repo {} size before changes {}".format(repo_dir, repo_size))

    if f.is_file() and is_media_file(f):
        new_path = old_path.replace(src, repo_dir)
        logger.info("Moving file from {} to {}".format(old_path, new_path))
        repo_size -= f.stat().st_size
        if repo_size <= 0:
            logger.info("File not moved, as repo size exceeds maximum")
            return False

        current_file_hash = git.hash_object(f.absolute())
        copyfile(old_path, new_path)
        logger.info("File {} created.".format(new_path))

    elif f.is_dir():
        new_path = Path("{}/{}".format(repo_dir, old_path.replace(src, "")))
        logger.info("Creating directory {}".format(new_path.absolute()))

        if not new_path.exists():
            new_path.mkdir()
            logger.info("Directory already exists")

    return True


def add_new_repo():
    return "dummy_name"


def execute(src, repo_dir, repo_dirs):
    path = Path(src)

    for f in path.glob('**/*'):
        if not fill_in_repo(src, f, repo_dir):
            repo_dir = add_new_repo()


if __name__ == "__main__":
    repo_dirs = clone_repos()

    execute("/home/sabina/workspace/photos", "/tmp", repo_dirs)

    print(directory_size("/tmp"))
