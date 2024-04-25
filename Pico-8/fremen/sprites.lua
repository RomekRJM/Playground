sprite = {
    x = 128,
    y = 80,
    sprite = 0,
    w = 2,
    h = 2,
    flip_x = false,
    flip_y = false,
    visible = true,
}

function sprite:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end