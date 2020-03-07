LDA #$00
LDX #$00
 
loop:
JSR fun
INX
CPX #$60
BNE loop
 
fun:
TXA
ROR
BCC even
BCS odd
odd:
LDA #$01
JMP end
even:
LDA #$02
JMP end
end:
STA $00,X
RTS
