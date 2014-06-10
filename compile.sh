#!/bin/bash
nasm -f elf ./bin/bfgen.asm
ld -o ./bin/bfgen -m elf_i386 ./bin/bfgen.o
