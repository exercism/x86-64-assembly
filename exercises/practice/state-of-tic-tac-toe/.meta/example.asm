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
        push    r12
        push    r13
        cld
        xor     r8, r8                  ; found win for X?
        xor     r9, r9                  ; found win for O?
        xor     r10, r10                ; number of X marks on board
        xor     r11, r11                ; number of O marks on board
        xor     r12, r12                ; bitset representing X marks on board
        xor     r13, r13                ; bitset representing O marks on board

.read_row:
        mov     rsi, [rdi]              ; read address of next row
        add     rdi, 8
        test    rsi, rsi
        jz      .match

        shl     r12, 1
        shl     r13, 1
        jmp     .read_mark

.x:
        inc     r12
        inc     r10                     ; update number of X marks on board

.read_mark:
        lodsb                           ; read mark, post-increment
        test    al, al
        jz      .read_row

        shl     r12, 1
        shl     r13, 1
        cmp     al, 'X'
        je      .x

        cmp     al, 'O'
        jne     .read_mark

.o:
        inc     r13
        inc     r11                     ; update number of O marks on board
        jmp     .read_mark

.match:
        lea     rsi, [lines]
        xor     rax, rax
        jmp     .read_line

.xs:
        mov     r8, 1                   ; line formed by X marks

.read_line:
        lodsw                           ; read from lines, post-increment
        test    ax, ax
        jz      .report

        mov     rdx, rax
        and     rdx, r12
        cmp     rdx, rax
        je      .xs

        mov     rdx, rax
        and     rdx, r13
        cmp     rdx, rax
        jne     .read_line

.os:
        mov     r9, 1                   ; line formed by O marks
        jmp     .read_line

.report:
        pop     r13
        pop     r12

        mov     rdi, r10
        add     rdi, r11                ; total number of marks on board

        sub     r10, r11
        cmp     r8, r10
        jg      .invalid                ; number of O marks > number of X marks, or equality after X win

        neg     r10
        inc     r10
        cmp     r9, r10
        jg      .invalid                ; number of X marks > 1 + number of O marks, or equality after O win

        test    r8, r9                  ; check if both players "won"
        jnz     .invalid

        or      r8, r9                  ; has either player won?
        jnz     .win

        cmp     rdi, 9
        je      .draw

.ongoing:
        mov     rax, ONGOING
        ret

.draw:
        mov     rax, DRAW
        ret

.win:
        mov     rax, WIN
        ret

.invalid:
        mov     rax, INVALID
        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
