SpawnPill:
	LDA pillLifeTime
	BNE :+
		LDA #PILL_LIFE_TIME
		STA pillLifeTime
	:

  INC pillTimer

	BNE :+
		DEC pillLifeTime
		BNE :+
			LDA frame
			JSR NextRandomByte
			STA pillLeft
      CLC
      ADC #PILL_WIDTH
      STA pillRight
			JSR NextRandomByte
			STA pillTop
      CLC
      ADC #PILL_HEIGHT
      STA pillBottom
			RTS
	:
	RTS

RenderPill:
	LDX spriteCounter
	LDY #$00
LoadPillSprites:
  LDA PillData, Y
	CPY #$03
  BNE :+
		CLC
		ADC pillLeft
  :
  CPY #$00
  BNE :+
	 CLC
	 ADC pillTop
  :

  STA $0200, X
  INX
  INY
  CPY #$04
  BNE LoadPillSprites
  STX spriteCounter
  RTS
