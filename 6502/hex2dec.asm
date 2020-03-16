define pointIndex0 $02
define pointIndex1 $01
define pointIndex2 $00

define points $10
define decimalInc $11

LDA #$ff
STA pointIndex0

LDA #$11
STA points

a:
JSR PointsToDecimal 
DEC points
LDA points
BNE a

PointsToDecimal:
INC pointIndex0
LDX pointIndex0
CPX #$0a
BEQ Tens
RTS 

Tens:
LDX #$00
STX pointIndex0
INC pointIndex1

End:
RTS
