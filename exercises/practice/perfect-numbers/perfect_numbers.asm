DEFICIENT equ 1
PERFECT equ 2
ABUNDANT equ 3
INVALID equ -1

section .text
global classify
classify:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
