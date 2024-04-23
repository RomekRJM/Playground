arrow = {
    x = 128,
    y = 80,
    sprite = 0,
    w = 2,
    h = 2,
    flip_x = false,
    flip_y = false,
    visible = true,
}
arrow.__index = arrow

function arrow:new(changes)
    return setmetatable(changes or {}, self)
end

function deepCopy(obj)
    if type(obj) ~= 'table' then
        return obj
    end

    local res = setmetatable({}, getmetatable(obj))

    for k, v in pairs(obj) do
        res[deepCopy(k)] = deepCopy(v)
    end

    return res
end

leftArrow = arrow:new(nil)
rightArrow = arrow:new({ flip_x = true })
topArrow = arrow:new({ sprite = 2, flip_x = true })
bottomArrow = arrow:new({ sprite = 2, flip_y = true })

function restartArrows()
    firstVisible = 1
    arrowUpdateBatchLen = 10
    arrowSpeed = 1
    newInvisible = 0
    frame = 0

    arrow_queue = {}
    arrow_queue_len = 128

    sequence = { leftArrow, rightArrow, topArrow, bottomArrow }

    for i = 1, arrow_queue_len do
        arrow_queue[i] = deepCopy(rnd(sequence))

        arrow_queue[i].x = arrow_queue[i].x + ((i - 1) % arrowUpdateBatchLen) * 32
    end
end

function drawArrows()

    for i = firstVisible, arrow_queue_len - 1 do
        if arrow_queue[i].visible == false then
            break
        end

        spr(arrow_queue[i].sprite, arrow_queue[i].x, arrow_queue[i].y, arrow_queue[i].w,
                arrow_queue[i].h, arrow_queue[i].flip_x, arrow_queue[i].flip_y)
    end

    print(stat(1), 0, 0)
end

function logArrows(frame)
    local log = "arrows.txt"
    printh("pass: " .. tostring(pass))
    printh("first: " .. tostring(firstVisible), log)
    printh("last: " .. tostring(lastVisible), log)

    for i = 1, arrow_queue_len do
        printh(tostring(i) .. ": " .. tostring(arrow_queue[i].x), log)
    end
end

function updateArrows()
    firstVisible = firstVisible + newInvisible
    lastVisible = firstVisible + arrowUpdateBatchLen

    newInvisible = 0

    if lastVisible > arrow_queue_len then
        lastVisible = arrow_queue_len
    end

    for i = firstVisible, lastVisible - 1 do
        arrow_queue[i].x = arrow_queue[i].x - arrowSpeed

        if arrow_queue[i].x < arrow_queue[i].w * -8 then
            arrow_queue[i].visible = false
            newInvisible = newInvisible + 1
        end
    end

    logArrows(frame)

    frame = frame + 1
end