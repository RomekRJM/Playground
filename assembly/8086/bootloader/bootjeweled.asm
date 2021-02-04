[bits 16] ; use 16 bits
[org 0x7c00] ; sets the start address

mov ah, 0   ; set display mode function.
mov al, 13h ; mode 13h = 320x200 pixels, 256 colors.
int 10h     ; set it!

game_loop:

  inner_game_loop:

    call draw_square
    mov ax, col
    adc ax, 30
    mov [col_e], ax
    adc ax, 20
    mov [col], ax
    cmp ax, 290
    jle inner_game_loop

    mov ax, 10
    mov [col], ax
    mov ax, [row]
    adc ax, 30
    mov [row_e], ax
    adc ax, 20
    mov [row], ax
    cmp ax, 150
    jle inner_game_loop

  jmp game_loop


draw_square:
  mov cx, [col]  ;col
  mov dx, [row]  ;row

  colcount:
  inc cx
  mov ah, 0ch ; put pixel
  mov al, 0ch ; pick color
  int 10h

  cmp cx, [col_e]
  jne colcount

  mov cx, [col]  ; reset to start of col
  inc dx      ; next row
  cmp dx, [row_e]
  jne colcount

  ret

col: dw 20
row: dw 20
col_e: dw 50
row_e: dw 50

times 510-($-$$) db 0 ; fill the output file with zeroes until 510 bytes are full
dw 0xaa55 ; magic number that tells the BIOS this is bootable
