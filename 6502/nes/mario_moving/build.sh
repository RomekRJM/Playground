#!/bin/bash

ca65 hellomario.asm -o hellomario.o --debug-info
ld65 hellomario.o -o hellomario.nes -t nes --dbgfile hellomario.dbgfile

open -a ~/Downloads/Nestopia.app hellomario.nes