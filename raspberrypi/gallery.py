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
GALLERY_PROJECTS = {"query":  "{ group(fullPath: \"rsgallery\") { id name projects { nodes { name } } } }"}
PATH = "/tmp"
MAX_REPO_SIZE = 100000000
MEDIA_FILES = ["jpg", "jpeg", "png", "mov"]


class GitlabClient:
    def __init__(self, private_token):
        self.url = "https://gitlab.com/api/graphql"
        self.private_token = private_token

    def list_projects_in_group(self, group_name):
        response = requests.post(
            url=self.url,
            params=GALLERY_PROJECTS,
            headers={
                "Authorization": "Bearer {}".format(self.private_token),
                "Content-Type": "application/json"
            }
        )
        response.raise_for_status()

        nodes = response.json()['data']['group']['projects']['nodes']

        return [list(x.values())[0] for x in nodes]


def clone_repos(repos):
    repo_dirs = []

    for repo in repos:
        repo_dir = "{}/{}".format(PATH, repo)
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


def fill_in_repo(src, repo):
    logger.info("Copying files from {} to {}".format(src, repo))

    git = Repo.init("/tmp", bare=True).git
    path = Path(src)
    repo_size = MAX_REPO_SIZE - directory_size(repo)

    logger.debug("Repo {} size before changes {}".format(repo, repo_size))

    for f in path.glob('**/*'):
        old_path = str(f.resolve())

        if f.is_file() and is_media_file(f):
            new_path = old_path.replace(src, repo)
            logger.info("Moving file from {} to {}".format(old_path, new_path))
            repo_size -= f.stat().st_size
            if repo_size <= 0:
                logger.info("File not moved, as repo size exceeds maximum")
                break

            current_file_hash = git.hash_object(f.absolute())
            copyfile(old_path, new_path)
            logger.info("File {} created.".format(new_path))

        elif f.is_dir():
            new_path = Path("{}/{}".format(repo, old_path.replace(src, "")))
            logger.info("Creating directory {}".format(new_path.absolute()))

            if not new_path.exists():
                new_path.mkdir()
                logger.info("Directory already exists")


if __name__ == "__main__":
    projects = GitlabClient(GITLAB_TOKEN).list_projects_in_group(GITLAB_GROUP)
    repo_dirs = clone_repos(projects)

    fill_in_repo("/home/sabina/workspace/photos", "/tmp")

    print(directory_size("/tmp"))
