[bits 16] ; use 16 bits
[org 0x7c00] ; sets the start address

mov ax, 13h ; ah = 0, al = 13h => 320x200 pixels, 256 colors.
int 10h     ; set it!

; here we create an array containing gems in upper memory
mov si, 2000

prepare_gem_board:
  call random_10
  mov [si], al
  inc si
  cmp si, 2060
  jle prepare_gem_board


game_loop:
  mov si, 2000

  redraw_cursor:
  mov bl, 7
  call draw_cursor

  mov al, 8
  mov [col], word 14
  mov [row], word 10
  mov [col_e], word 34
  mov [row_e], word 30

  mov si, 2000

  draw_gems:
  mov al, byte [si]
  inc si
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

check_enter:
  cmp al, 13
  jne check_right

  ; gem swap
  mov si, selected_gem_0
  mov bx, [si]
  mov di, selected_gem_1
  mov cx, [di]
  mov [si], cx
  mov [di], bx

check_right:
  cmp al, 100 ; d pressed
  jne check_left

  cmp [cur_xe], word 296
  jg check_left

  mov ax, word [cur_x]
  add ax, 30
  mov [cur_x], ax
  add ax, 58
  mov [cur_xe], ax

  inc word [selected_gem_0]
  inc word [selected_gem_1]

check_left:
  cmp al, 97 ; a pressed
  jne check_down

  cmp [cur_x], word 10
  jle check_down

  mov ax, word [cur_xe]
  sub ax, 30
  mov [cur_xe], ax
  sub ax, 58
  mov [cur_x], ax

  dec word [selected_gem_0]
  dec word [selected_gem_1]

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

  mov ax, [selected_gem_0]
  adc ax, 10
  mov [selected_gem_0], ax
  inc ax
  mov [selected_gem_1], ax

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

  mov ax, [selected_gem_0]
  sub ax, 10
  mov [selected_gem_0], ax
  dec ax
  mov [selected_gem_1], ax

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


; returns "random" value 1-4 in al
random_10:
  mov ax, [rand_number]
  rol ax, 2
  adc ax, [rand_number]
  adc ax, 13
  mov [rand_number], ax
  and ax, 11b
  inc ax
  ret

col: dw 14
row: dw 10
col_e: dw 34
row_e: dw 30

cur_x: dw 10
cur_y: dw 6
cur_xe: dw 68
cur_ye: dw 34

selected_gem_0: dw 2000
selected_gem_1: dw 2001

rand_number: db 1

times 510-($-$$) db 0 ; fill the output file with zeroes until 510 bytes are full
dw 0xaa55 ; magic number that tells the BIOS this is bootable
