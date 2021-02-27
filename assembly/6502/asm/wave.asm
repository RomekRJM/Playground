LDY #$01
LDX #$00 

loop:
LDA #$ff
STA $00,X
TXA 
CMP #$1f
BEQ end
AND #$01
CMP #$01
BEQ foo
TXA
CLC
ADC #$11
TAX
JMP loop
foo:
TXA 
SEC 
SBC #$0f
TAX
JMP loop

end:
NOP
