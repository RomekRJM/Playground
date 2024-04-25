leftUnicorn = sprite:new {
    x = 1,
    y = 10,
    sprite = 8,
    w = 6,
    h = 6,
}

rightUnicorn = sprite:new {
    x = 128 - 1 - 48,
    y = 10,
    sprite = 8,
    w = 6,
    h = 6,
    flip_x = true
}

function restartUnicorns()
end

function drawUnicorns()
    spr(leftUnicorn.sprite, leftUnicorn.x, leftUnicorn.y, leftUnicorn.w, leftUnicorn.h,
            leftUnicorn.flip_x, leftUnicorn.flip_y)
    spr(rightUnicorn.sprite, rightUnicorn.x, rightUnicorn.y, rightUnicorn.w, rightUnicorn.h,
            rightUnicorn.flip_x, rightUnicorn.flip_y)
end

function updateUnicorns()
end
