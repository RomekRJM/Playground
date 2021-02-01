#!/bin/bash

nasm bootjeweled.asm  -f bin -o bootjeweled.bin
qemu-system-i386 -fda bootjeweled.bin
