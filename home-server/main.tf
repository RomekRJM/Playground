resource "docker_image" "minecraft" {
  name         = "itzg/minecraft-server:java21-alpine"
  keep_locally = false
}

resource "docker_container" "minecraft" {
  image = docker_image.minecraft.image_id
  name  = "minecraft-server"
  network_mode = "host"
  restart = "always"
  env = toset([
    "EULA=TRUE",
    "WHITELIST=ErykCoco,",
    "OPS=ErykCoco,",
    "TYPE=FABRIC",
    "INIT_MEMORY=2G",
    "MAX_MEMORY=3G",
    "REMOVE_OLD_MODS=true",
  ])
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
  network_mode = "host"
  restart = "always"

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
    container_path = "/usr/share/nginx/html/eryk-sonic"
  }
}

