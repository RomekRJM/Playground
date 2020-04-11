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

; 0x70 - 0x78 - virus1
; 0x79 - 0x80 - virus2
; 0x81 - 0x89 - virus3
; 0x8a - 0x92 - virus4
.define nmiTimer $a0
.define buttons $a1
.define frame   $a2
.define playerLeft $a3
.define playerTop $a4
.define playerRight $a5
.define playerBottom $a6
.define randomByte $a7
.define spriteCounter $a8
.define pillLeft $a9
.define pillTop $aa
.define pillRight $ab
.define pillBottom $ac
.define pillTimer $ad
.define pillLifeTime $ae
.define pointIndex0 $af
.define pointIndex1 $b0
.define pointIndex2 $b1
.define points $b2
.define currentPointIndex $b3
.define pointIndexOffset $b4
.define playerCollidesWithCoin $b5
.define dim1Player $b6
.define dim2Player $b7
.define dim1Object $b8
.define dim2Object $b9
.define virusLeft $ba
.define virusTop $bb
.define virusRight $bc
.define virusBottom $bd
.define virusXSpeed $be
.define virusYSpeed $bf
.define virusXDirection $c0
.define virusYDirection $c1
.define virusAlive $c2
.define virusMoveFrame $c3
.define virusAnimationFrame $c4
.define virusAnimationChangeFrame $c5
.define virusCntr $c6
.define virusPointer $c7
.define dbg1 $c8
.define dbg2 $c9

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

NO_VIRUSES = $04
VIRUS_MOVE_INTERVAL = $04
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
