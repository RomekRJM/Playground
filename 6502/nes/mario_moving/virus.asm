MoveVirus:
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

  LDA virusAlive
  BNE :+
    JSR SpawnNewVirus
    RTS
  :

MoveVirusOnX:
  LDA virusXDirection
  BNE :+
    LDA virusLeft
    CLC
    ADC virusXSpeed
    STA virusLeft
    CMP #$fd
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
    CMP #$fd
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


RenderVirus:
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
  CMP #VIRUS_FRAME_0
  BEQ :+
    LDA #VIRUS_FRAME_0
    STA virusAnimationFrame
    JMP SetVirusFrame
  :
  LDA #VIRUS_FRAME_1
  STA virusAnimationFrame

SetVirusFrame:
  STA $0200, X
  INX
  INY
  CPY #$04
  BNE LoadVirusSprites
  STX spriteCounter
  RTS


SpawnNewVirus:
  JSR NextRandomBool
  STA virusXDirection
  JSR NextRandomBool
  STA virusYDirection
  JSR NextRandom1or2
  STA virusXSpeed
  JSR NextRandom1or2
  STA virusYSpeed

  INC virusAlive
  INC virusCntr
  RTS
