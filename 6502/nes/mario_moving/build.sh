#!/bin/bash

ca65 hellomario.asm -o hellomario.o --debug-info
ld65 hellomario.o -o hellomario.nes -t nes --dbgfile hellomario.dbgfile

/bin/ines hellomario.nes
