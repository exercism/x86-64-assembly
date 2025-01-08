default rel

section .rodata

i_know: db "I know an old lady who swallowed a ", 0
stop:   db ".", 10, 0
newline:
        db 10, 0
shes_dead:
        db "She's dead, of course!", 10, 0
i_dont: db "I don't know why she swallowed the fly. Perhaps she'll die.", 10, 0
she:    db "She swallowed the ", 0
to_catch:
        db " to catch the ", 0
that:   db " that wriggled and jiggled and tickled inside her", 0

fly:    db "fly", 0
spider: db "spider", 0
bird:   db "bird", 0
cat:    db "cat", 0
dog:    db "dog", 0
goat:   db "goat", 0
cow:    db "cow", 0
horse:  db "horse", 0

spider2:
        db "It wriggled and jiggled and tickled inside her.", 10, 0
bird2:  db "How absurd to swallow a bird!", 10, 0
cat2:   db "Imagine that, to swallow a cat!", 10, 0
dog2:   db "What a hog, to swallow a dog!", 10, 0
goat2:  db "Just opened her throat and swallowed a goat!", 10, 0
cow2:   db "I don't know how she swallowed a cow!", 10, 0

section .data

animal_array:
        dq 0
        dq fly
        dq spider
        dq bird
        dq cat
        dq dog
        dq goat
        dq cow
        dq horse

animal2_array:
        dq 0
        dq 0
        dq spider2
        dq bird2
        dq cat2
        dq dog2
        dq goat2
        dq cow2


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
        lea     r8, [animal_array]
        lea     r9, [animal2_array]
        mov     r10, rsi                ; current verse
        jmp     .start_verse

.next_verse:
        inc     r10
        lea     rsi, [newline]
        call    append

.start_verse:
        mov     r11, r10                ; current animal
        lea     rsi, [i_know]
        call    append

        mov     rsi, [r8 + r11 * 8]     ; lookup animal_array
        call    append

        lea     rsi, [stop]
        call    append

        cmp     r10, 8
        je      .shes_dead

        cmp     r10, 1
        je      .i_dont

        mov     rsi, [r9 + r11 * 8]     ; lookup animal2_array
        call    append

.she:
        lea     rsi, [she]
        call    append

        mov     rsi, [r8 + r11 * 8]     ; lookup animal_array
        call    append

        dec     r11                     ; previous animal
        lea     rsi, [to_catch]
        call    append

        mov     rsi, [r8 + r11 * 8]     ; lookup animal_array
        call    append

        cmp     r11, 2
        jne     .stop

        lea     rsi, [that]
        call    append

.stop:
        lea     rsi, [stop]
        call    append

        cmp     r11, 1
        jne     .she                    ; continue inner loop over animals

.i_dont:
        lea     rsi, [i_dont]
        call    append

        cmp     r10, rdx
        jne     .next_verse             ; continue outer loop over verses

        ret

.shes_dead:
        lea     rsi, [shes_dead]
        call    append

        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
