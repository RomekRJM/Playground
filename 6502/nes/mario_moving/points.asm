RenderPoints:
	LDA $08
	STA pointIndexOffset
	LDA #$00
	STA pointIndex0
	STA currentPointIndex
	JSR RenderPoint

	LDA #$09
	STA pointIndexOffset
	LDA #$03
	STA pointIndex1
	STA currentPointIndex
	JSR RenderPoint

	LDA #$12
	STA pointIndexOffset
	LDA #$09
	STA pointIndex1
	STA currentPointIndex
	JSR RenderPoint

	RTS

RenderPoint:
	LDX spriteCounter
	LDY #$00
LoadPointSprites:
	LDA currentPointIndex
	CMP #$00
	BNE :+
		LDA Zero, Y
	:
	CMP #$01
	BNE :+
		LDA One, Y
	:
	CMP #$02
	BNE :+
		LDA Two, Y
	:
	CMP #$03
	BNE :+
		LDA Three, Y
	:
	CMP #$04
	BNE :+
		LDA Four, Y
	:
	CMP #$05
	BNE :+
		LDA Five, Y
	:
	CMP #$06
	BNE :+
		LDA Six, Y
	:
	CMP #$07
	BNE :+
		LDA Seven, Y
	:
	CMP #$08
	BNE :+
		LDA Eight, Y
	:
	CMP #$09
	BNE :+
		LDA Nine, Y
	:
	CPY #$03
    BNE :+
		SEC
		SBC pointIndexOffset
	:
  STA $0200, X
  INX
	INY
  CPY #$04
  BNE LoadPointSprites
	STX spriteCounter
  RTS
