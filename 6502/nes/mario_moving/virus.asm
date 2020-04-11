LoadVirus:
  LDY virusPointer
  LDA $70 ,Y
  STA virusLeft
  INY
  LDA $70 ,Y
  STA virusTop
  INY
  LDA $70 ,Y
  STA virusRight
  INY
  LDA $70 ,Y
  STA virusBottom
  INY
  LDA $70 ,Y
  STA virusXSpeed
  INY
  LDA $70 ,Y
  STA virusYSpeed
  INY
  LDA $70 ,Y
  STA virusXDirection
  INY
  LDA $70 ,Y
  STA virusYDirection
  INY
  LDA $70 ,Y
  STA virusAlive
  INY
  STY virusPointer
  RTS

StoreVirus:
  LDA virusPointer
  SEC
  SBC #$09
  TAY
  LDA virusLeft
  STA $70 ,Y
  INY
  LDA virusTop
  STA $70 ,Y
  INY
  LDA virusRight
  STA $70 ,Y
  INY
  LDA virusBottom
  STA $70 ,Y
  INY
  LDA virusXSpeed
  STA $70 ,Y
  INY
  LDA virusYSpeed
  STA $70 ,Y
  INY
  LDA virusXDirection
  STA $70 ,Y
  INY
  LDA virusYDirection
  STA $70 ,Y
  INY
  LDA virusAlive
  STA $70 ,Y
  INY
  STY virusPointer
  RTS


MoveViruses:
  INC virusMoveFrame
  LDA virusMoveFrame
  CMP #VIRUS_MOVE_INTERVAL
  BNE :+
    LDA #$00
    STA virusMoveFrame
  :
  BEQ :+
    RTS
  :

  LDA #NO_VIRUSES
  STA virusCntr
  LDA #$00
  STA virusPointer

MoveNextVirus:
  JSR LoadVirus
  JSR MoveVirus
  JSR StoreVirus
  DEC virusCntr
  LDA virusCntr
  BNE MoveNextVirus
  RTS


MoveVirus:
  LDA virusAlive
  BNE :+
    JSR SpawnNewVirus
  :

MoveVirusOnX:
  LDA virusXDirection
  BNE :+
    LDA virusLeft
    CLC
    ADC virusXSpeed
    STA virusLeft
    CMP #$fb
    BCC MoveVirusOnY
    JSR KillVirus
    RTS
  :
  LDA virusLeft
  SEC
  SBC virusXSpeed
  STA virusLeft
  CMP #$02
  BCS MoveVirusOnY
  JSR KillVirus
  RTS

MoveVirusOnY:
  LDA virusYDirection
  BNE :+
    LDA virusTop
    CLC
    ADC virusYSpeed
    STA virusTop
    CMP #$fb
    BCC FinishMoveVirus
    JSR KillVirus
    RTS
  :
  LDA virusTop
  SEC
  SBC virusYSpeed
  STA virusTop
  CMP #$02
  BCS FinishMoveVirus
  JSR KillVirus

FinishMoveVirus:
  RTS


KillVirus:
  LDA #$00
  STA virusAlive
  RTS


RenderViruses:
  INC virusAnimationChangeFrame
  LDA virusAnimationChangeFrame
  CMP #VIRUS_CHANGE_FRAME_INTERVAL
  BNE InitVirusesRendering

  LDA #$00
  STA virusAnimationChangeFrame

  LDA virusAnimationFrame
  CMP #VIRUS_FRAME_0
  BEQ :+
    LDA #VIRUS_FRAME_0
    STA virusAnimationFrame
    JMP InitVirusesRendering
  :
  LDA #VIRUS_FRAME_1
  STA virusAnimationFrame

InitVirusesRendering:
  LDA #NO_VIRUSES
  STA virusCntr
  LDA #$00
  STA virusPointer

RenderNextVirus:
  JSR LoadVirus
  JSR RenderVirus
  JSR StoreVirus
  DEC virusCntr
  LDA virusCntr
  BNE RenderNextVirus
  RTS


RenderVirus:
  LDA virusAlive
  BNE :+
    RTS
  :

  LDX spriteCounter
  LDY #$00
LoadVirusSprites:
  LDA VirusData, Y
  CPY #$03
  BNE :+
    CLC
    ADC virusLeft
  :
  CPY #$00
  BNE :+
    CLC
    ADC virusTop
  :
  CPY #$01
  BNE SetVirusFrame
  LDA virusAnimationFrame

SetVirusFrame:
  STA $0200, X
  INX
  INY
  CPY #$04
  BNE LoadVirusSprites
  STX spriteCounter
  RTS

SpawnNewVirus:
  JSR NextRandom1or2
  STA virusXSpeed
  JSR NextRandom1or2
  STA virusYSpeed

  JSR NextRandom3Bits
  TAX
  CPX #$00  ; top-left quarter, virusLeft=0, virusTop=[0, 127]
  BNE :+
    LDA #$00
    STA virusXDirection
    STA virusYDirection
    LDA #$03
    STA virusLeft
    JSR NextRandom7Bits
    STA virusTop
    JMP EndAxisPick
  :
  CPX #$01  ; top-left quarter, virusLeft=[0,127], virusTop=0
  BNE :+
    LDA #$00
    STA virusXDirection
    STA virusYDirection
    LDA #$03
    STA virusTop
    JSR NextRandom7Bits
    STA virusLeft
    JMP EndAxisPick
  :
  CPX #$02  ; top-right quarter, virusLeft=[128,255], virusTop=0
  BNE :+
    LDA #$01
    STA virusXDirection
    LDA #$00
    STA virusYDirection
    LDA #$03
    STA virusTop
    JSR NextRandom128To255
    STA virusLeft
    JMP EndAxisPick
  :
  CPX #$03  ; top-right quarter, virusLeft=255, virusTop=[0,127]
  BNE :+
    LDA #$01
    STA virusXDirection
    LDA #$00
    STA virusYDirection
    JSR NextRandom7Bits
    STA virusTop
    LDA #$fa
    STA virusLeft
    JMP EndAxisPick
  :
  CPX #$04  ; bottom-left quarter, virusLeft=0, virusTop=[128,255]
  BNE :+
    LDA #$00
    STA virusXDirection
    STA virusLeft
    LDA #$01
    STA virusYDirection
    JSR NextRandom128To255
    STA virusTop
    JMP EndAxisPick
  :
  CPX #$05  ; bottom-left quarter, virusLeft=[0,127], virusTop=255
  BNE :+
    LDA #$00
    STA virusXDirection
    LDA #$01
    STA virusYDirection
    JSR NextRandom7Bits
    STA virusLeft
    LDA #$fa
    STA virusTop
    JMP EndAxisPick
  :
  CPX #$06  ; bottom-right quarter, virusLeft=[128,255], virusTop=255
  BNE :+
    LDA #$01
    STA virusXDirection
    STA virusYDirection
    JSR NextRandom128To255
    STA virusLeft
    LDA #$fa
    STA virusTop
    JMP EndAxisPick
  :
  CPX #$07  ; bottom-right quarter, virusLeft=255, virusTop=[128,255]
  BNE :+
    LDA #$01
    STA virusXDirection
    STA virusYDirection
    JSR NextRandom128To255
    STA virusTop
    LDA #$fa
    STA virusLeft
    JMP EndAxisPick
  :

EndAxisPick:
  LDA #$01
  STA virusAlive
  RTS
