; populate memory with numbers
LDA #$01
STA $00
LDA #$00
STA $01
LDA #$ca
STA $02
LDA #$ca
STA $03
LDA #$05
STA $04
LDA #$02
STA $05
LDA #$fe
STA $06

define swaps $1000
define oldswaps $1001
LDA #$00
STA swaps
LDX #$00

; main loop checking numbers
loop:
; is X on last array element?
CPX #$06
BEQ fullruncompleted
LDY $00,X
TYA 
INX 
CMP $00,X
BEQ loop
BCS swap
JMP loop

; swap neeighbouring numbers
swap:
LDA $00,X
STY  $00,X
DEX
STA $00,X
INX
INC swaps
JMP loop

; is it fully sorted?
fullruncompleted:
LDA swaps
STA oldswaps
LDA #$00
TAX
STA swaps
LDA oldswaps
BNE loop
