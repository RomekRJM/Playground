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
			STA pillX
			JSR NextRandomByte
			STA pillY
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
		ADC pillX
:
  CPY #$00
  BNE :+
	CLC
	ADC pillY
:

  STA $0200, X
  INX
  INY
  CPY #$04
  BNE LoadPillSprites
  STX spriteCounter
  RTS
