default rel

section .rodata

for_want:
        db "For want of a ", 0
the:    db " the ", 0
was_lost:
        db " was lost.", 10, 0
and_all:
        db "And all for the want of a ", 0
stop:   db ".", 10, 0

section .text
global recite

append:
        lodsb
        stosb
        test    al, al
        jnz     append

        dec     rdi
        ret

; extern void recite(char *buffer, const char **strings);
recite:
        cld
        mov     rdx, rsi
        mov     r8, [rdx]               ; first string
        add     rdx, 8
        test    r8, r8
        jz      .empty

        mov     r10, r8                 ; current string
        jmp     .next_line

.for_want:
        lea     rsi, [for_want]
        call    append

        mov     rsi, r10
        call    append

        lea     rsi, [the]
        call    append

        mov     rsi, r11
        call    append

        lea     rsi, [was_lost]
        call    append

        mov     r10, r11                ; current string

.next_line:
        mov     r11, [rdx]              ; next string
        add     rdx, 8
        test    r11, r11
        jnz     .for_want

        lea     rsi, [and_all]
        call    append

        mov     rsi, r8
        call    append

        lea     rsi, [stop]
        call    append

.empty:
        xor     al, al
        stosb
        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
