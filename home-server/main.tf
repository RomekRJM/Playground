locals {
  minecraft_default_envs = {
    EULA                    = "TRUE"
    WHITELIST               = "ErykCoco,"
    OPS                     = "ErykCoco,"
    REMOVE_OLD_MODS         = "true"
    REMOVE_OLD_MODS_EXCLUDE = ""
  }

  minecraft_default_config = {
    tag = "latest"
    env = {
      "TYPE" = "FABRIC"
    }
  }

  grinch_christmas_config = {
    tag = "latest"
    env = {
      "TYPE"             = "SPIGOT",
      "SPIGET_RESOURCES" = "108842",
      "INIT_MEMORY"      = "2G",
      "MAX_MEMORY"       = "3G",
    }
  }

  castle_siege_config = {
    tag = "java17-alpine"
    env = {
      "TYPE"             = "SPIGOT",
      "SPIGET_RESOURCES" = "115123",
      "INIT_MEMORY"      = "1G",
      "MAX_MEMORY"       = "2G",
      "VERSION"          = "1.20.4"
    }
  }

  current_minecraft_config = local.castle_siege_config
}

resource "docker_image" "minecraft" {
  name         = "itzg/minecraft-server:${local.current_minecraft_config.tag}"
  keep_locally = false
}

resource "docker_container" "minecraft" {
  image        = docker_image.minecraft.image_id
  name         = "minecraft-server"
  network_mode = "host"
  restart      = "unless-stopped"
  stdin_open   = true
  tty          = true

  env = toset(
    [
      for key, value in merge(local.minecraft_default_envs, local.current_minecraft_config.env) :
      "${key}=${value}"
    ]
  )

  volumes {
    host_path      = "/tmp"
    container_path = "/data"
  }

  ports {
    internal = 25565
    external = 25565
  }
}

resource "docker_image" "nginx" {
  name         = "nginxinc/nginx-unprivileged"
  keep_locally = false
}

resource "docker_container" "nginx" {
  image        = docker_image.nginx.image_id
  name         = "nginx"
  network_mode = "host"
  restart      = "unless-stopped"

  upload {
    file   = "/etc/nginx/conf.d/eryk.nginx.conf"
    source = "${path.cwd}/nginx.conf"
  }

  ports {
    internal = 80
    external = 8000
  }

  volumes {
    host_path      = "${path.cwd}/eryk-sonic"
    container_path = "/usr/share/nginx/html/eryk-sonic"
  }
}

resource "docker_image" "multiple_pony" {
  name         = "multiple-pony:latest"
  keep_locally = false
}

resource "docker_container" "multiple_pony" {
  image        = docker_image.multiple_pony.image_id
  name         = "multiple_pony"
  network_mode = "host"
  restart      = "unless-stopped"

  env = toset(
    [
        "NODE_ENV=production",
    ]
  )

  ports {
    internal = 3000
    external = 3000
  }
}

