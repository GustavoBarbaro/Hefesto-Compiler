#\!/bin/bash

gcc main.c asm_definitions.c binario.c asm_fast_converter.c -o exec_asm 
./exec_asm
