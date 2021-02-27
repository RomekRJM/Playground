#!/bin/bash

nasm bootjeweled.asm  -f bin -o bootjeweled.bin

TOTAL_BYTES=512
ZEROES=`cat bootjeweled.bin | xxd -p | sed 's/0000//g' | wc -c`
let "FREE_BYTES = $TOTAL_BYTES - (($ZEROES - 18) / 2)"
echo "Bytes left: $FREE_BYTES out of $TOTAL_BYTES"

rm -f memdump.txt

qemu-system-i386 -fda bootjeweled.bin -monitor stdio
