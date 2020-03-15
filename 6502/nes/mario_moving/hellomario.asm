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
.define playerSpriteX $a5
.define playerSpriteY $a6
.define moveFrame     $a7
.define spriteCounter $a8

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
    STA $0200, X
    INX
	INY
    CPY #$04
    BNE LoadPillSprites
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
  .byte $38, $75, $00, $58

.segment "VECTORS"
    .word NMI
    .word Reset
    ; 
	
.segment "CHARS"
    .incbin "hellomario.chr"
