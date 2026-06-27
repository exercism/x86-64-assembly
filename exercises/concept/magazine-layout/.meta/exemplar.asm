%ifndef MAGAZINE_LAYOUT_ASM
%define MAGAZINE_LAYOUT_ASM

COLUMN_COUNT equ 4
COLUMN_STRIDE equ 18
SPACE equ 0x20
RULE equ 0x3D
RULE_WIDTH equ 4
PLAIN equ 0x2E
RULED equ 0x2D
BOXED equ 0x23

%define COUNTER rcx

%macro fill_run 3
    mov COUNTER, %2
    test COUNTER, COUNTER
    jz %%done
%%loop:
    mov byte [%1 + COUNTER - 1], %3
    dec COUNTER
    jnz %%loop
%%done:
%endmacro

%macro lay_columns 2
    %assign i 0
    %rep COLUMN_COUNT
        mov qword [%1 + 8*i], %2
        add %2, COLUMN_STRIDE
    %assign i i + 1
    %endrep
%endmacro

%macro set_header 2
    %if %2 = 0
        mov byte [%1], PLAIN
    %elif %2 = 1
        mov byte [%1], RULED
    %else
        mov byte [%1], BOXED
    %endif
%endmacro

%endif

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
