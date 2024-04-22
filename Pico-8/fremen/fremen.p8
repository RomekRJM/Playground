pico-8 cartridge // http://www.pico-8.com
version 42
__lua__
#include main.lua
#include arrows.lua
#include player.lua
__gfx__
00000000000000000000000070000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000070000000000000000777000000000000000000000000007777777000000000000000000000000000000000000000000000000000000000000000000000
00000770000000000000007707700000000000000700000000007000007000000000000000000000000000000000000000000000000000000000000000000000
00007770000000000000077000770000000000000770000000007000007000000000000000000000000000000000000000000000000000000000000000000000
00077077777777700000770000077000000000000777000000007000007000000000000000000000000000000000000000000000000000000000000000000000
00770000000000700007700000007700077777777707700000007000007000000000000000000000000000000000000000000000000000000000000000000000
07700000000000700077770000077770070000000000770000007000007000000000000000000000000000000000000000000000000000000000000000000000
77000000000000700000070000070000070000000000077000007000007000000000000000000000000000000000000000000000000000000000000000000000
07700000000000700000070000070000070000000000007700007000007000000000000000000000000000000000000000000000000000000000000000000000
00770000000000700000070000070000070000000000077007777000007777000000000000000000000000000000000000000000000000000000000000000000
00077077777777700000070000070000070000000000770000770000000770000000000000000000000000000000000000000000000000000000000000000000
00007770000000000000070000070000077777777707700000077000007700000000000000000000000000000000000000000000000000000000000000000000
00000770000000000000070000070000000000000777000000007700077000000000000000000000000000000000000000000000000000000000000000000000
00000070000000000000070000070000000000000770000000000770770000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000077777770000000000000700000000000077700000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000000007000000000000000000000000000000000000000000000000000000000000000000000000
__map__
1515151515151515151515151515151716001616001616000016161616161616000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1515151515151515151515151515151516001616001616000016161616161616000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1515151515151515151515151515151516001616001616000016160000000016000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1515151515151515151515151515151516001616001616000016160000000016000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1515151515151515151515151515151516001616001616000000000000000016000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1515151515151515151515151515151516001616001616000016160000000016000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1515151515151515151515151515151516001616001616000016161616161616000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1515151515151515151515151515151516001616001616000016161616161616000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1515151515151515151515151515151516001616000000001616161616161616000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1515151515151515151515151515151516001616001616001616161616161616000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1515151515151515151515151515151516001616161616001616161616161616000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1515151515151515151515151515151516001616161616001616161616161616000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1414141414141414141414141414141416000000000000001616161616161616000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
1414141414141414141414141414141416161616161616161616161616161616000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000