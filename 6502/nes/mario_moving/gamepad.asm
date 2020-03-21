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
