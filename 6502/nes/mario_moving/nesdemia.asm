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

.define nmiTimer $00
.define buttons $01
.define frame   $02
.define playerLeft $03
.define playerTop $04
.define playerRight $05
.define playerBottom $06
.define randomByte $07
.define spriteCounter $08
.define pillLeft $09
.define pillTop $0a
.define pillRight $0b
.define pillBottom $0c
.define pillTimer $0d
.define pillLifeTime $0e
.define pointIndex0 $0f
.define pointIndex1 $10
.define pointIndex2 $11
.define points $12
.define currentPointIndex $13
.define pointIndexOffset $14
.define playerCollidesWithCoin $15
.define dim1Player $16
.define dim2Player $17
.define dim1Object $18
.define dim2Object $19
.define virusLeft $1a
.define virusTop $1b
.define virusRight $1c
.define virusBottom $1d
.define virusXSpeed $1e
.define virusYSpeed $1f
.define virusXDirection $20
.define virusYDirection $21
.define virusAlive $22
.define virusMoveFrame $23
.define virusAnimationFrame $24
.define virusAnimationChangeFrame $25
.define virusCntr $26
.define virusPointer $27
.define dbg1 $28
.define dbg2 $29
; 0x70 - 0x78 - virus1
; 0x79 - 0x80 - virus2
; 0x81 - 0x89 - virus3
; 0x8a - 0x92 - virus4

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

VIRUS_MOVE_INTERVAL = $05
VIRUS_CHANGE_FRAME_INTERVAL = $1f
VIRUS_FRAME_0 = $e0
VIRUS_FRAME_1 = $e1

PILL_LIFE_TIME = $1a

PLAYER_WIDTH = $10
PLAYER_HEIGHT = $20

PILL_WIDTH = $08
PILL_HEIGHT = $08

COLLISSION = $01
NO_COLLISSION = $00

NO_VIRUSES = $01


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
  LDA #$01
  STA nmiTimer

.include "pallete.asm"

  JSR InitPoints

MainGameLoop:
  JSR GetControllerInput
  JSR ReactOnInput
  JSR ComputeLogic
  JSR RenderGraphics
  JSR WaitForNmi
  JMP MainGameLoop

ComputeLogic:
  JSR SpawnPill
  JSR CheckCollisions
  JSR MoveViruses
  RTS

CheckCollisions:
  JSR CheckCollision
  LDA playerCollidesWithCoin
  CMP #COLLISSION
  BNE :+
    INC points
    JSR PointsToDecimal
    JSR ForcePillRespawn
    LDA #NO_COLLISSION
    STA playerCollidesWithCoin
  :
  RTS

WaitForNmi:
  LDA nmiTimer			;vblank wait
WaitForNmiLoop:
  CMP nmiTimer
  BEQ WaitForNmiLoop
  RTS

NMI:
  LDA #$02 ; copy sprite data from $0200 => PPU memory for display
  STA $4014
  INC frame
  INC nmiTimer
  RTI

.include "gamepad.asm"

RenderGraphics:
  LDA #$00
  STA spriteCounter

  JSR RenderPlayer
  JSR RenderPill
  JSR RenderViruses
  JSR RenderPoints

  RTS

.include "player.asm"

.include "virus.asm"

.include "points.asm"

.include "pill.asm"

.include "utils.asm"

.include "gfx.asm"

.segment "VECTORS"
  .word NMI
  .word Reset
  ;

.segment "CHARS"
  .incbin "hellomario.chr"
