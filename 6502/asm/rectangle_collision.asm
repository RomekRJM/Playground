; Rectangle collision algorithm
; Given rectangles of:
; player left=x1Player, top=y1Player, right=x2Player, bottom=y2Player
; enemy left=x1Enemy, top=y1Enemy, right=x2Enemy, bottom=y2Enemy
; algorithm puts result==1 if there is collision beetween them, or result==0 otherwise

define x1Player $00
define x2Player $01
define y1Player $02
define y2Player $03

define x1Enemy $04
define x2Enemy $05
define y1Enemy $06
define y2Enemy $07

define dim1Player $10
define dim2Player $11
define dim1Enemy $12
define dim2Enemy $13

define result $20

LDA #$ff
STA x1Player

LDA #$ff
STA y1Player

LDA #$08
STA x2Player

LDA #$08
STA y2Player

LDA #$00
STA x1Enemy

LDA #$00
STA y1Enemy

LDA #$12
STA x2Enemy

LDA #$12
STA y2Enemy

LDA #$01
STA result

LDA x1Player
STA dim1Player
LDA x2Player
STA dim2Player
LDA x1Enemy
STA dim1Enemy
LDA x2Enemy
STA dim2Enemy
JSR do_collide

LDA y1Player
STA dim1Player
LDA y2Player
STA dim2Player
LDA y1Enemy
STA dim1Enemy
LDA y2Enemy
STA dim2Enemy
JSR do_collide
JMP end

do_collide:
LDA dim1Player
CMP dim1Enemy
BCS check2
JMP check3 

check2:
CMP dim2Enemy
BCC collision 
BEQ collision 

check3:
LDA dim2Player
CMP dim1Enemy
BCS check4
JMP no_collision

check4:
CMP dim2Enemy
BCC collision
BEQ collision
JMP no_collision 

no_collision:
RTS 

collision:
LDA result
AND #$01
RTS 

end:
NOP
