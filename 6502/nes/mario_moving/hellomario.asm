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
.define tmp     $a7

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
    
    JSR RenderGraphics
    
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
    lda #$01
    ; While the strobe bit is set, buttons will be continuously reloaded.
    ; This means that reading from JOYPAD1 will only return the state of the
    ; first button: button A.
    sta JOYPAD1
    sta buttons
    lsr a        ; now A is 0
    ; By storing 0 into JOYPAD1, the strobe bit is cleared and the reloading stops.
    ; This allows all 8 buttons (newly reloaded) to be read from JOYPAD1.
    sta JOYPAD1
GetControllerInputLoop:
    lda JOYPAD1
    lsr a	       ; bit 0 -> Carry
    rol buttons  ; Carry -> bit 0; bit 7 -> Carry
    bcc GetControllerInputLoop
    rts
    

ShiftX:
    LDA buttons
    AND BUTTON_LEFT
    BEQ GoLeft
    AND BUTTON_RIGHT
    BEQ GoRight
    JMP FinishedShiftX
GoLeft:
    LDA #$0f
    STA playerX
    JMP FinishedShiftX
GoRight:
    LDA #$af
    STA playerX
    ;INC playerX
FinishedShiftX:
    LDA playerSpriteX
    CLC
    ADC playerX
    JMP ContinueLoad

ShiftY:
    JMP ContinueLoad

ClearY:
    LDY #$00
    JMP PrepareSpriteForPPU
    
RenderGraphics:
    LDX #$00
    LDY #$00
LoadSprites:
    LDA SpriteData, X
    STA playerSpriteX
    CPY #$03
    BEQ ShiftX
    CPY #$00
    BEQ ShiftY
ContinueLoad:
    INY
    CPY #$04
    BEQ ClearY
PrepareSpriteForPPU:
    STA $0200, X
    INX
    CPX #$20
    BNE LoadSprites
    
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

.segment "VECTORS"
    .word NMI
    .word Reset
    ; 
.segment "CHARS"
    .incbin "hellomario.chr"
