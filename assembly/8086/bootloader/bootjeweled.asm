[bits 16] ; use 16 bits
[org 0x7c00] ; sets the start address

mov ah, 0   ; set display mode function.
mov al, 13h ; mode 13h = 320x200 pixels, 256 colors.
int 10h     ; set it!

game_loop:

  redraw_cursor:
  mov bl, 7
  call draw_cursor

  mov al, 8
  mov [col], word 14
  mov [row], word 10
  mov [col_e], word 34
  mov [row_e], word 30

  draw_gems:

  call draw_square
  mov ax, [col]
  adc ax, 30
  mov [col], ax
  adc ax, 20
  mov [col_e], ax
  cmp ax, 320
  jle draw_gems

  mov [col], word 14
  mov [col_e], word 34

  mov ax, [row]
  adc ax, 30
  mov [row], ax
  adc ax, 20
  mov [row_e], ax
  cmp ax, 200
  jle draw_gems

get_input:
  mov ah, 1    ; Check if key pressed
  int 22
  pushf
  xor ax, ax       ; Wait for a key
  int 22
  popf
  jnz get_input

  push ax
  mov bl, 0
  call draw_cursor
  pop ax

  cmp al, 100 ; d pressed
  jne check_right

  cmp [cur_xe], word 296
  jg check_right

  mov ax, word [cur_x]
  add ax, 30
  mov [cur_x], ax
  add ax, 58
  mov [cur_xe], ax

check_right:
  cmp al, 97 ; a pressed
  jne check_down

  cmp [cur_x], word 10
  jle check_down

  mov ax, word [cur_xe]
  sub ax, 30
  mov [cur_xe], ax
  sub ax, 58
  mov [cur_x], ax

check_down:
  cmp al, 115 ; s pressed
  jne check_up

  cmp [cur_ye], word 184
  jge check_up

  mov ax, word [cur_ye]
  add ax, 2
  mov [cur_y], ax
  add ax, 28
  mov [cur_ye], ax

check_up:
  cmp al, 119 ; w pressed
  jne continue_game_loop

  cmp [cur_y], word 6
  jle continue_game_loop

  mov ax, word [cur_ye]
  sub ax, 30
  mov [cur_ye], ax
  sub ax, 28
  mov [cur_y], ax

continue_game_loop:
  jmp game_loop


draw_square:
  mov cx, [col]  ;col
  mov dx, [row]  ;row

draw_line:
  inc cx
  mov ah, 0ch ; put pixel
  int 10h

  cmp cx, [col_e]
  jne draw_line

  mov cx, [col]
  inc dx
  cmp dx, [row_e]
  jne draw_line

  ret

rand_color:
  ;int 1ah    ; get number of ticks since midnight
  mov al, 10
  ret

draw_cursor:
  mov ax, word [cur_x]
  mov [col], ax
  mov ax, word [cur_y]
  mov [row], ax
  mov ax, word [cur_xe]
  mov [col_e], ax
  mov ax, word [cur_ye]
  mov [row_e], ax
  mov al, bl
  call draw_square
  ret

col: dw 14
row: dw 10
col_e: dw 34
row_e: dw 30

cur_x: dw 10
cur_y: dw 6
cur_xe: dw 68
cur_ye: dw 34

times 510-($-$$) db 0 ; fill the output file with zeroes until 510 bytes are full
dw 0xaa55 ; magic number that tells the BIOS this is bootable
