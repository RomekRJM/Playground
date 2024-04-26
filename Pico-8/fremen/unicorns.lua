leftUnicorn = sprite:new {
    x = 0,
    y = 10,
    sprite = 8,
    w = 5,
    h = 4,
}

rightUnicorn = sprite:new {
    x = 128 - 5 * 8, -- screen_width - w * default_sprite_width
    y = 10,
    sprite = 8,
    w = 5,
    h = 4,
    flip_x = true
}

rainbowPart = sprite:new {
    x = 16,
    y = 27,
    sprite = 32,
    w = 1,
    h = 1,
}

rainbowAngleMultiplier = 16 / 360
leftRainbowX = 24
rightRainbowX = 102

function restartUnicorns()
    rainbow = {}

    for x = leftRainbowX, rightRainbowX, 1 do
        add(rainbow, deepCopy(rainbowPart:new({ x = x })))
    end
end

function drawUnicorns()
    spr(leftUnicorn.sprite, leftUnicorn.x, leftUnicorn.y, leftUnicorn.w, leftUnicorn.h,
            leftUnicorn.flip_x, leftUnicorn.flip_y)
    spr(rightUnicorn.sprite, rightUnicorn.x, rightUnicorn.y, rightUnicorn.w, rightUnicorn.h,
            rightUnicorn.flip_x, rightUnicorn.flip_y)
end

function drawRainbow()
    local rainbowCollisionX = leftRainbowX + (rightRainbowX - leftRainbowX) / 2
    local x = 0

    for i, rainbowSprite in ipairs(rainbow) do
        local angle = (frame + i * 2) % 360
        local shiftY = sin(angle * rainbowAngleMultiplier)

        if rainbowSprite.x <= rainbowCollisionX then
            x = rainbowCollisionX - rainbowSprite.x + leftRainbowX
            spr(rainbowSprite.sprite, x, rainbowSprite.y - shiftY, rainbowSprite.w, rainbowSprite.h)
        else
            x = rainbowSprite.x
            spr(rainbowSprite.sprite, x, rainbowSprite.y + shiftY, rainbowSprite.w, rainbowSprite.h)
        end

    end
end

function drawUnicornsWithRainbow()
    drawRainbow()
    drawUnicorns()
end

function updateUnicorns()
end
