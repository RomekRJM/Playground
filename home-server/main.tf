locals {
  minecraft_default_envs = {
    EULA                    = "TRUE"
    WHITELIST               = "ErykCoco,Pingwinek,Nataniczek,PokeOscar,grubykabaczek"
    OPS                     = "Nataniczek"
    REMOVE_OLD_MODS         = "true"
    REMOVE_OLD_MODS_EXCLUDE = ""
  }

  minecraft_default_config = {
    tag = "latest"
    env = {
      "TYPE"        = "FABRIC"
      "INIT_MEMORY" = "2G",
      "MAX_MEMORY"  = "5G",
    }
  }

  world_edit_config = {
    tag = "latest"
    env = {
      "TYPE"                          = "NEOFORGE",
      "NEOFORGE_VERSION"              = "21.7.1"
      "MODRINTH_PROJECTS"             = "worldedit",
      "MODRINTH_ALLOWED_VERSION_TYPE" = "beta",
      "INIT_MEMORY"                   = "2G",
      "MAX_MEMORY"                    = "3G",
      "VERSION"                       = "1.21.7"
    }
  }

  minescript_config = {
    tag = "latest"
    env = {
      "TYPE"              = "NEOFORGE",
      "NEOFORGE_VERSION"  = "beta"
      "MODRINTH_PROJECTS" = "minescript"
      "INIT_MEMORY"       = "2G",
      "MAX_MEMORY"        = "3G",
      "VERSION"           = "1.21.6"
    }
  }

  pixelmon_config = {
    tag = "2025.6.2"
    env = {
      "TYPE"                          = "NEOFORGE",
      "NEOFORGE_VERSION"              = "21.1.206"
      "MODRINTH_PROJECTS"             = "pixelmon"
      "MODRINTH_ALLOWED_VERSION_TYPE" = "beta"
      "INIT_MEMORY"                   = "5G",
      "MAX_MEMORY"                    = "6G",
      "VERSION"                       = "1.21.1"
    }
  }

  current_minecraft_config = local.minecraft_default_config
}

resource "docker_image" "minecraft" {
  name         = "itzg/minecraft-server:${local.current_minecraft_config.tag}"
  keep_locally = false
}

resource "docker_container" "minecraft" {
  count        = 1
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

