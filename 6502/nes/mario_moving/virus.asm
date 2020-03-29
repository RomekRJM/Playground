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

  LDA #$01
  STA virusXSpeed
  CLC
  ADC virusLeft
  STA virusLeft
  LDA #$02
  STA virusYSpeed
  CLC
  ADC virusTop
  STA virusTop
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

  STA $0200, X
  INX
  INY
  CPY #$04
  BNE LoadVirusSprites
  STX spriteCounter
  RTS
