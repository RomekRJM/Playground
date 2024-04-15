variable "docker_host" {
  type        = string
  default     = "unix:///var/run/docker.sock"
  description = "Allows to specify the docker host to connect to. Default is the local docker socket."
}
