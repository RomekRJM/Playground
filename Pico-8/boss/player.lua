function restartPlayer()
  --create a table for player data
    player = {
        sprite = 2,
        x = 28,
        y = 88,
        w = 8,
        h = 8,
        jump = false,
        jump_index = 1,
        alive = true,
        faces_left = false,
        moves_on_x = true,
        speed = 1.5
    }

    player_jump_lookup = {
        -5, -4, -4, -3, -3, -2, -2, -1, -1, 0,
         5, 4, 4, 3, 3, 2, 2, 1, 1
    }

end

function drawPlayer()
    if player.alive == true then
      spr(player.sprite, player.x, player.y, 1, 1, player.faces_left)
    end
end


function updatePlayer()

    if btn(⬆️) then
      player.jump = true
    end

    player.moves_on_x = false

    if btn(⬅️) then
      player.x -= player.speed
      player.x = player.x < 0 and 0 or player.x
      player.faces_left = true
      player.moves_on_x = true
    end

    if btn(➡️) then
      player.x += player.speed
      player.x = player.x > 128-player.w and 128-player.w or player.x
      player.faces_left = false
      player.moves_on_x = true
    end

    if player.jump == true then
      player.y += player_jump_lookup[player.jump_index]
      player.jump_index += 1

      if player.jump_index > 19 then
        player.jump_index = 1
        player.jump = false
      end
    end

    if player.moves_on_x == true then
      player.sprite += 1
    end

    if player.sprite > 8 then
      player.sprite = 1
    end

end
