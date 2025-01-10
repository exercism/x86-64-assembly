default rel

section .rodata

green_bottle:
        db " green bottle", 0
green_bottles:
        db " green bottles", 0
hanging_on:
        db " hanging on the wall", 0
and_if:
        db "And if one green bottle should accidentally fall,", 10, "There'll be ", 0
comma:  db ",", 10, 0
stop:   db ".", 10, 10, 0

no:     db "No", 0
one:    db "One", 0
two:    db "Two", 0
three:  db "Three", 0
four:   db "Four", 0
five:   db "Five", 0
six:    db "Six", 0
seven:  db "Seven", 0
eight:  db "Eight", 0
nine:   db "Nine", 0
ten:    db "Ten", 0

section .data

number_array:
        dq no
        dq one
        dq two
        dq three
        dq four
        dq five
        dq six
        dq seven
        dq eight
        dq nine
        dq ten

section .text
global recite

append:
        lodsb
        test    al, al
        jz      .return

        stosb
        jmp     append

.return:
        ret

; extern void recite(char *buffer, int start_bottles, int take_down);
recite:
        cld
        mov     rcx, 2
        lea     r8, [number_array]
        lea     r9, [green_bottle]
        mov     r10, rsi
        mov     r11, rsi
        sub     r11, rdx
        shl     r10, 3                  ; offset into number_array for start_bottles
        shl     r11, 3                  ; final offset into number_array

.verse:
        mov     rsi, [r8 + r10]
        call    append

        lea     rsi, [green_bottles]
        cmp     r10, 8
        cmove   rsi, r9                 ; conditionally green_bottle instead of green_bottles
        call    append

        lea     rsi, [hanging_on]
        call    append

        lea     rsi, [comma]
        call    append

        loop    .verse

        mov     rcx, 2
        sub     r10, 8

        lea     rsi, [and_if]
        call    append

        mov     rsi, [r8 + r10]

        lodsb
        or      al, 32                  ; force lower case
        stosb

        call    append

        lea     rsi, [green_bottles]
        cmp     r10, 8
        cmove   rsi, r9
        call    append

        lea     rsi, [hanging_on]
        call    append

        lea     rsi, [stop]
        call    append

        cmp     r10, r11
        jg      .verse

        xor     al, al
        mov     [rdi - 1], al           ; overwrite second newline
        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
