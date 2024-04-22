leftArrow = {
    sprite = 0,
    x = 0,
    y = 0,
    w = 2,
    h = 2,
    flip_x = false,
    flip_y = false,
    visible = true,
}

rightArrow = {
    sprite = 0,
    x = 20,
    y = 0,
    w = 2,
    h = 2,
    flip_x = true,
    flip_y = false,
    visible = true,
}

topArrow = {
    sprite = 2,
    x = 40,
    y = 0,
    w = 2,
    h = 2,
    flip_x = false,
    flip_y = false,
    visible = true,
}

bottomArrow = {
    sprite = 2,
    x = 60,
    y = 0,
    w = 2,
    h = 2,
    flip_x = false,
    flip_y = true,
    visible = true,
}

function restartArrows()

end

function drawArrows()
    spr(leftArrow.sprite, leftArrow.x, leftArrow.y, leftArrow.w, leftArrow.h, leftArrow.flip_x, leftArrow.flip_y)
    spr(rightArrow.sprite, rightArrow.x, rightArrow.y, rightArrow.w, rightArrow.h, rightArrow.flip_x, rightArrow.flip_y)
    spr(topArrow.sprite, topArrow.x, topArrow.y, topArrow.w, topArrow.h, topArrow.flip_x, topArrow.flip_y)
    spr(bottomArrow.sprite, bottomArrow.x, bottomArrow.y, bottomArrow.w, bottomArrow.h, bottomArrow.flip_x, bottomArrow.flip_y)
end

function updateArrows()

end