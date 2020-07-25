import requests
import os

class GitlabClient:
    def __init__(self, private_token):
        self.url = "https://gitlab.com/api/v4/"
        self.private_token = private_token

    def __build_url(self, path, params):
        base = "{}/{}?private_token={}".format(self.url, path, self.private_token)

        for key, value in enumerate(params):
            base += "&{}={}".format(key, value)

        return base

    def list_projects(self, search_criteria):
        url = self.__build_url("projects", {
            "search", "gal2",
            "simple", "true",
            "owned", "true"
        })

        response = requests.get(url=url)
        response.raise_for_status()

        return response.json()


if __name__ == "__main__":
    GITLAB_TOKEN = os.getenv("GITLAB_TOKEN")
    print(GitlabClient(GITLAB_TOKEN).list_projects(""))
