function _init()
    restartUnicorns()
    restartArrows()
end

function _draw()
    cls()
    drawUnicorns()
    drawArrows()
end

function _update60()
    updateUnicorns()
    updateArrows()
end
