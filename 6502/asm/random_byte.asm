define seed $1000
LDA #$00
STA seed
LDX #$00

loop:
JSR random
STA $00,X
CLC
INX
CPX #$ff
BNE  loop
BEQ end

random:
LDA seed
ROL
ROL
ADC seed
ADC #$17
STA seed
RTS

end:
NOP
