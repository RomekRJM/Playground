;
; iNES header
;
.segment "HEADER"
.byte "NES"
.byte $1a
.byte $02 ; 2 * 16KB PRG ROM
.byte $01 ; 1 * 8KB CHR ROM
.byte %00000000 ; mapper and mirroring
.byte $00
.byte $00
.byte $00
.byte $00
.byte $00, $00, $00, $00, $00 ; filler bytes
.segment "ZEROPAGE" ; LSB 0 - FF

.define buttons $a1
.define frame   $a2
.define playerX $a3
.define playerY $a4
.define randomByte $a5
.define playerSpriteY $a6
.define moveFrame     $a7
.define spriteCounter $a8
.define pillX $a9
.define pillY $aa
.define pillTimer $ab
.define pillLifeTime $ac
.define pointIndex0 $b0
.define pointIndex1 $b1
.define pointIndex2 $b2
.define currentPointIndex $b3
.define pointIndexOffset $b4

.define dbg1 $f0
.define dbg2 $f1
.define dbg3 $f2
.define dbg4 $f3

.segment "STARTUP"

JOYPAD1 = $4016
JOYPAD2 = $4017

BUTTON_A      = 1 << 7
BUTTON_B      = 1 << 6
BUTTON_SELECT = 1 << 5
BUTTON_START  = 1 << 4
BUTTON_UP     = 1 << 3
BUTTON_DOWN   = 1 << 2
BUTTON_LEFT   = 1 << 1
BUTTON_RIGHT  = 1 << 0

MOVE_INTERVAL = $10
PILL_LIFE_TIME = $0a


Reset:
    SEI ; Disables all interrupts
    CLD ; disable decimal mode

    ; Disable sound IRQ
    LDX #$40
    STX $4017

    ; Initialize the stack register
    LDX #$FF
    TXS

    INX ; #$FF + 1 => #$00

    ; Zero out the PPU registers
    STX $2000
    STX $2001

    STX $4010

:
    BIT $2002
    BPL :-

    TXA

CLEARMEM:
    STA $0000, X ; $0000 => $00FF
    STA $0100, X ; $0100 => $01FF
    STA $0300, X
    STA $0400, X
    STA $0500, X
    STA $0600, X
    STA $0700, X
    LDA #$FF
    STA $0200, X ; $0200 => $02FF
    LDA #$00
    INX
    BNE CLEARMEM    
; wait for vblank
:
    BIT $2002
    BPL :-

    LDA #$02
    STA $4014
    NOP

    ; $3F00
    LDA #$3F
    STA $2006
    LDA #$00
    STA $2006

    LDX #$00

LoadPalettes:
    LDA PaletteData, X
    STA $2007 ; $3F00, $3F01, $3F02 => $3F1F
    INX
    CPX #$20
    BNE LoadPalettes
    
; Enable interrupts
    CLI

    LDA #%10010000 ; enable NMI change background to use second chr set of tiles ($1000)
    STA $2000
    ; Enabling sprites and background for left-most 8 pixels
    ; Enable sprites and background
    LDA #%00011110
    STA $2001

Loop:
    JSR GetControllerInput
	JSR ReactOnInput
	JSR ComputeLogic
    JSR RenderGraphics
    JMP Loop

NMI:
    LDA #$02 ; copy sprite data from $0200 => PPU memory for display
    STA $4014
	INC frame
    RTI
; end NMI

; At the same time that we strobe bit 0, we initialize the ring counter
; so we're hitting two birds with one stone here
GetControllerInput:
    LDA #$01
    ; While the strobe bit is set, buttons will be continuously reloaded.
    ; This means that reading from JOYPAD1 will only return the state of the
    ; first button: button A.
    STA JOYPAD1
    STA buttons
    LSR A        ; now A is 0
    ; By storing 0 into JOYPAD1, the strobe bit is cleared and the reloading stops.
    ; This allows all 8 buttons (newly reloaded) to be read from JOYPAD1.
    STA JOYPAD1
GetControllerInputLoop:
    LDA JOYPAD1
    LSR A	       ; bit 0 -> Carry
    ROL buttons  ; Carry -> bit 0; bit 7 -> Carry
    BCC GetControllerInputLoop
    RTS


ReactOnInput:
	; we don't want to move caracter every frame - it's to fast
	; instead we will get input every MOVE_INTERVAL frames to slow it down
	INC moveFrame
	LDA moveFrame
	CMP #MOVE_INTERVAL
	BNE :+
		LDA #$00
		STA moveFrame
	:
	BEQ :+
		RTS
	:
	
	LDA buttons
    AND #BUTTON_LEFT
    BEQ :+
		DEC playerX
	:
	
	LDA buttons
    AND #BUTTON_RIGHT
    BEQ :+
		INC playerX
	:
	
	LDA buttons
    AND #BUTTON_UP
    BEQ :+
		DEC playerY
	:
	
	LDA buttons
    AND #BUTTON_DOWN
    BEQ :+
		INC playerY
	:
	
	RTS
	

RenderGraphics:
	LDA #$00
	STA spriteCounter
	
	JSR RenderPlayer
	JSR RenderPill
	JSR RenderPoints

	RTS

    
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


ComputeLogic:
	JSR SpawnPill
	
	RTS

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


NextRandomByte:
	STA randomByte
	ROL
	ROL
	ADC randomByte
	ADC #$17
	STA randomByte
	RTS

PaletteData:
  .byte $22,$29,$1A,$0F,$22,$36,$17,$0f,$22,$30,$21,$0f,$22,$27,$17,$0F  ;background palette data
  .byte $22,$16,$27,$18,$22,$1A,$30,$27,$22,$16,$30,$27,$22,$0F,$36,$17  ;sprite palette data

SpriteData:
  .byte $08, $00, $00, $08
  .byte $08, $01, $00, $10
  .byte $10, $02, $00, $08
  .byte $10, $03, $00, $10
  .byte $18, $04, $00, $08
  .byte $18, $05, $00, $10
  .byte $20, $06, $00, $08
  .byte $20, $07, $00, $10

PillData:
  .byte $08, $75, $00, $08

Zero:
  .byte $10, $60, $00, $f0

One:
  .byte $10, $61, $00, $f0

Two:
  .byte $10, $62, $00, $f0

Three:
  .byte $10, $63, $00, $f0
  
Four:
  .byte $10, $64, $00, $f0

Five:
  .byte $10, $65, $00, $f0
  
Six:
  .byte $10, $66, $00, $f0
  
Seven:
  .byte $10, $67, $00, $f0

Eight:
  .byte $10, $68, $00, $f0

Nine:
  .byte $10, $69, $00, $f0

.segment "VECTORS"
    .word NMI
    .word Reset
    ; 
	
.segment "CHARS"
    .incbin "hellomario.chr"
