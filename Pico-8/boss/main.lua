function _init()
  restartPlayer()
  restartBoss()
end


function _draw()
    cls()
    map(0, 0, 0, 0, 128, 128)
    drawPlayer()
    drawBoss()
end


function _update()
   updatePlayer()
   updateBoss()
end
