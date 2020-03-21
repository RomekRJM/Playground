RenderPlayer:
  LDX spriteCounter
  LDY #$00
LoadPlayerSprites:
  LDA SpriteData, X
  CPY #$03
  BNE :+
	CLC
	ADC playerX
:
  CPY #$00
  BNE :+
	CLC
	ADC playerY
:
  INY
  CPY #$04
  BNE :+
	LDY #$00
:

  STA $0200, X
  INX
  CPX #$20
  BNE LoadPlayerSprites
	STX spriteCounter

  RTS
