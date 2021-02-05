[bits 16] ; use 16 bits
[org 0x7c00] ; sets the start address

mov ah, 0   ; set display mode function.
mov al, 13h ; mode 13h = 320x200 pixels, 256 colors.
int 10h     ; set it!

game_loop:

  draw_cursor:

  mov al, 7
  mov [col], word 10
  mov [row], word 6
  mov [col_e], word 68
  mov [row_e], word 34
  call draw_square

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

col: dw 14
row: dw 10
col_e: dw 34
row_e: dw 30

cur_y: dw 10
cur_x: dw 8
cur_ye: dw 38
cur_xe: dw 60

times 510-($-$$) db 0 ; fill the output file with zeroes until 510 bytes are full
dw 0xaa55 ; magic number that tells the BIOS this is bootable
