[bits 16] ; use 16 bits
[org 0x7c00] ; sets the start address

mov ah, 0   ; set display mode function.
mov al, 13h ; mode 13h = 320x200 pixels, 256 colors.
int 10h     ; set it!

game_loop:

  mov [col], word 14
  mov [row], word 10
  mov [col_e], word 34
  mov [row_e], word 30

  inner_game_loop:

    call draw_square
    mov ax, [col]
    adc ax, 30
    mov [col], ax
    adc ax, 20
    mov [col_e], ax
    cmp ax, 320
    jle inner_game_loop

    mov [col], word 14
    mov [col_e], word 34

    mov ax, [row]
    adc ax, 30
    mov [row], ax
    adc ax, 20
    mov [row_e], ax
    cmp ax, 200
    jle inner_game_loop

  jmp game_loop


draw_square:
  mov cx, [col]  ;col
  mov dx, [row]  ;row

  draw_line:
  inc cx
  mov ah, 0ch ; put pixel
  mov al, 0ch ; pick color
  int 10h

  cmp cx, [col_e]
  jne draw_line

  mov cx, [col]
  inc dx
  cmp dx, [row_e]
  jne draw_line

  ret

col: dw 14
row: dw 10
col_e: dw 34
row_e: dw 30

times 510-($-$$) db 0 ; fill the output file with zeroes until 510 bytes are full
dw 0xaa55 ; magic number that tells the BIOS this is bootable
