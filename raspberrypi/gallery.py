import os
from pathlib import Path

from git import Repo
import requests


GITLAB_GROUP = os.getenv("GITLAB_GROUP")
GITLAB_TOKEN = os.getenv("GITLAB_TOKEN")
GITLAB_USER = os.getenv("GITLAB_USER")
GALLERY_PROJECTS={"query":  "{ group(fullPath: \"rsgallery\") { id name projects { nodes { name } } } }"}
PATH="/tmp"

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
                "https://gitlab-ci-token:{}@gitlab.com/{}/{}.git"
                    .format(GITLAB_TOKEN, GITLAB_USER.lower(), repo),
                repo_dir)

        repo_dirs.append(repo_dir)

    return repo_dirs

def directory_size(path):
    root_directory = Path(path)
    return sum(f.stat().st_size for f in root_directory.glob('*') if f.is_file())


if __name__ == "__main__":
    projects = GitlabClient(GITLAB_TOKEN).list_projects_in_group(GITLAB_GROUP)
    repo_dirs = clone_repos(projects)

    print([{r: directory_size(r)} for r in repo_dirs])
