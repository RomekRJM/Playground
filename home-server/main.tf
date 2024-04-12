resource "docker_image" "minecraft" {
  name         = "itzg/minecraft-server"
  keep_locally = false
}

resource "docker_container" "minecraft" {
  image = docker_image.minecraft.image_id
  name  = "minecraft-server"
  env = toset(["EULA=TRUE"])
  stdin_open = true
  tty = true

  volumes {
    host_path = "/tmp"
    container_path = "/data"
  }

  ports {
    internal = 25565
    external = 25565
  }
}

resource "docker_image" "nginx" {
  name         = "nginx"
  keep_locally = false
}

resource "docker_container" "nginx" {
  image = docker_image.nginx.image_id
  name  = "nginx"

  upload {
    file = "/etc/nginx/conf.d/eryk.nginx.conf"
    source = "${path.cwd}/nginx.conf"
  }

  ports {
    internal = 80
    external = 8000
  }

  volumes {
    host_path = "${path.cwd}/eryk-sonic"
    container_path = "/usr/share/nginx/eryk-sonic"
  }
}

