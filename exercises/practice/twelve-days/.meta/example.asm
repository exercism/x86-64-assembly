default rel

section .rodata

on_the: db "On the ", 0
day_of: db " day of Christmas my true love gave to me: ", 0
gifts: db "twelve Drummers Drumming, eleven Pipers Piping, ten Lords-a-Leaping, nine Ladies Dancing, eight Maids-a-Milking, seven Swans-a-Swimming, six Geese-a-Laying, five Gold Rings, four Calling Birds, three French Hens, two Turtle Doves, and a Partridge in a Pear Tree.", 10, 0

offsets:
        dq 0
        dq 235
        dq 213
        dq 194
        dq 174
        dq 157
        dq 137
        dq 113
        dq 90
        dq 69
        dq 48
        dq 26
        dq 0

first:  db "first", 0
second: db "second", 0
third:  db "third", 0
fourth: db "fourth", 0
fifth:  db "fifth", 0
sixth:  db "sixth", 0
seventh:
        db "seventh", 0
eighth: db "eighth", 0
ninth:  db "ninth", 0
tenth:  db "tenth", 0
eleventh:
        db "eleventh", 0
twelfth:
        db "twelfth", 0

section .data

ordinals:
        dq 0
        dq first
        dq second
        dq third
        dq fourth
        dq fifth
        dq sixth
        dq seventh
        dq eighth
        dq ninth
        dq tenth
        dq eleventh
        dq twelfth

section .text
global recite

append:
        lodsb
        stosb
        test    al, al
        jnz     append

        dec     rdi
        ret

; extern void recite(char *buffer, int start_verse, int end_verse);
recite:
        cld
        lea     r8, [ordinals]
        lea     r9, [offsets]
        mov     r10, rsi                ; current verse

.next_verse:
        lea     rsi, [on_the]
        call    append

        mov     rsi, [r8 + r10 * 8]     ; lookup ordinals
        call    append

        lea     rsi, [day_of]
        call    append

        mov     r11, [r9 + r10 * 8]     ; lookup offsets
        lea     rsi, [gifts]
        add     rsi, r11
        call    append

        inc     r10
        cmp     r10, rdx
        jle     .next_verse

        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
