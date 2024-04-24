arrow = {
    x = 128,
    y = 80,
    sprite = 0,
    w = 2,
    h = 2,
    next_element_pad_x = 32,
    flip_x = false,
    flip_y = false,
    visible = true,
}
arrow.__index = arrow

function arrow:new(changes)
    return setmetatable(changes or {}, self)
end

leftArrow = arrow:new(nil)
rightArrow = arrow:new({ flip_x = true })
topArrow = arrow:new({ sprite = 2, flip_x = true })
bottomArrow = arrow:new({ sprite = 2, flip_y = true })

function restartArrows()
    arrowQueueIndex = 1
    arrowUpdateBatchLen = 10
    arrowSpeed = 1
    frame = 0

    arrowQueue = {}
    arrowQueueLen = 32
    visibleArrowQueue = {}
    visibleArrowQueueMaxLen = 10

    sequence = { leftArrow, rightArrow, topArrow, bottomArrow }

    for i = 1, arrowQueueLen do
        arrowQueue[i] = deepCopy(rnd(sequence))

        if i <= arrowUpdateBatchLen then
            arrowQueue[i].x = 128
        end
    end

    add(visibleArrowQueue, deepCopy(arrowQueue[1]))
    visibleArrowQueueLen = 1

    printh(tprint(arrowQueue))
end

function drawArrows()

    for _, visible_arrow in pairs(visibleArrowQueue) do
        spr(visible_arrow.sprite, visible_arrow.x, visible_arrow.y, visible_arrow.w, visible_arrow.h,
                visible_arrow.flip_x, visible_arrow.flip_y)
    end

    print(stat(1), 0, 0)
end

function logarrows()
    printh("arrowQueueIndex: " .. tostring(arrowQueueIndex))
    printh("visibleArrowQueueLen: " .. tostring(visibleArrowQueueLen))

    for _, visibleArrow in pairs(visibleArrowQueue) do
        printh(tostring(i) .. ": " .. tostring(visibleArrow.x))
    end
end

function updateArrows()

    if btn(⬆️) then
        stop()
    end

    if visibleArrowQueueLen == 0 and arrowQueueIndex == arrowQueueLen then
        return
    end

    local scheduledForDeletion = {}

    for _, visibleArrow in pairs(visibleArrowQueue) do
        visibleArrow.x = visibleArrow.x - arrowSpeed
        visibleArrow.next_element_pad_x = visibleArrow.next_element_pad_x - arrowSpeed

        if visibleArrow.next_element_pad_x == 0 and arrowQueueIndex < arrowQueueLen then
            add(visibleArrowQueue, deepCopy(arrowQueue[arrowQueueIndex]))
            arrowQueueIndex = arrowQueueIndex + 1
            visibleArrowQueueLen = visibleArrowQueueLen + 1
        end

        if visibleArrow.x < visibleArrow.w * -8 then
            add(scheduledForDeletion, visibleArrow)
        end
    end

    for _, deletedArrow in pairs(scheduledForDeletion) do
        del(visibleArrowQueue, deletedArrow)
        visibleArrowQueueLen = visibleArrowQueueLen - 1
    end

    frame = frame + 1
end
