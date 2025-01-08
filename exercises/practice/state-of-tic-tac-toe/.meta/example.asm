ONGOING equ 0
DRAW equ 1
WIN equ 2
INVALID equ 3

default rel

section .rodata
lines: dw 0x007, 0x070, 0x700, 0x111, 0x222, 0x444, 0x124, 0x421, 0

section .text
global gamestate
gamestate:
        cld
        xor     r8, r8                  ; bitset representing X marks on board
        xor     r9, r9                  ; bitset representing O marks on board
        xor     r10, r10                ; number of X marks on board
        xor     r11, r11                ; number of O marks on board

.read_row:
        mov     rsi, [rdi]              ; read address of next row
        add     rdi, 8
        test    rsi, rsi
        jz      .count

        shl     r8, 1
        shl     r9, 1

.read_mark:
        lodsb                           ; read mark, post-increment
        test    al, al
        jz      .read_row

        shl     r8, 1
        shl     r9, 1
        cmp     al, 'X'
        je      .x

        cmp     al, 'O'
        je      .o

        jmp     .read_mark

.x:
        inc     r8
        inc     r10                     ; update number of X marks on board
        jmp     .read_mark

.o:
        inc     r9
        inc     r11                     ; update number of O marks on board
        jmp     .read_mark

.count:
        cmp     r11, r10
        jg      .invalid                ; number of O marks > number of X marks

        mov     rdx, r11
        inc     rdx
        cmp     r10, rdx
        jg      .invalid                ; number of X marks > 1 + number of O marks

        mov     rdi, r10
        add     rdi, r11                ; total number of marks on board

        xor     r10, r10                ; found win for X?
        xor     r11, r11                ; found win for O?
        lea     rsi, [lines]
        xor     rax, rax

.read_line:
        lodsw                           ; read from lines, post-increment
        test    ax, ax
        jz      .report

        mov     rdx, rax
        and     rdx, r8
        cmp     rdx, rax
        je      .xs

        mov     rdx, rax
        and     rdx, r9
        cmp     rdx, rax
        je      .os

        jmp     .read_line

.xs:
        mov     r10, 1                  ; line formed by X marks
        jmp     .read_line

.os:
        mov     r11, 1                  ; line formed by O marks
        jmp     .read_line

.report:
        mov     rdx, r10
        or      rdx, r11                ; has either player won?
        test    rdx, rdx
        jnz     .win

        cmp     rdi, 9
        je      .draw

        mov     rax, ONGOING
        ret

.draw:
        mov     rax, DRAW
        ret

.win:
        cmp     r10, r11                ; check if both players "won"
        je      .invalid

        mov     rax, WIN
        ret

.invalid:
        mov     rax, INVALID
        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
