DEFICIENT equ 1
PERFECT equ 2
ABUNDANT equ 3
INVALID equ -1

section .text
global classify

; extern int classify(int64_t number);
classify:
        cmp     rdi, 1
        jle     .le_one

        mov     r8, 1                   ; product of factors
        mov     r9, 1
        mov     r10, rdi
        shl     r10, 1                  ; 2 * number

.next:
        inc     r9                      ; candidate factor
        mov     r11, 1                  ; sum of powers of factor
        mov     rax, r9
        mul     r9
        cmp     rax, rdi
        jbe     .divide

        mov     r9, rdi                 ; as r9*r9 exceeded rdi, then set r9 to rdi

.divide:
        xor     rdx, rdx
        mov     rax, rdi
        div    r9
        test    rdx, rdx
        jnz     .next

.repeat:
        mov     rdi, rax

        mov     rax, r11
        mul     r9
        inc     rax
        mov     r11, rax                ; r11 * r9 + 1

        xor     rdx, rdx
        mov     rax, rdi
        div    r9
        test    rdx, rdx
        jz      .repeat

        mov     rax, r8
        mul     r11
        mov     r8, rax                 ; r11 * r8

        cmp     rdi, 1
        jne     .next

        cmp     r8, r10
        je      .perfect
        jb      .deficient

.abundant:
        mov     rax, ABUNDANT
        ret

.perfect:
        mov     rax, PERFECT
        ret

.deficient:
        mov     rax, DEFICIENT
        ret

.le_one:
        je      .deficient

        mov     rax, INVALID
        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
