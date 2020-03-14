@echo on
C:\cc65\bin\ca65 -g hellomario.asm
C:\cc65\bin\ld65 hellomario.o -o hellomario.nes -t nes --dbgfile hellomario.nes.dbg
C:\fceux\fceux.exe hellomario.nes