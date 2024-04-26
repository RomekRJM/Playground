function _init()
    frame = 0
    restartUnicorns()
    restartArrows()
end

function _draw()
    cls()
    drawUnicornsWithRainbow()
    drawArrows()
end

function _update60()
    updateUnicorns()
    updateArrows()
    frame = frame + 1
end
