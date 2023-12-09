function restartBoss()
    boss = {
        sprite = 11,
        x = 88,
        y = 64,
        w = 8,
        h = 8,
        alive = true,
    }
end

function drawBoss()
    spr(boss.sprite, boss.x, boss.y, boss.w, boss.h)
end

function updateBoss()

end