default rel

section .rodata

lyrics:
        db "This is the horse and the hound and the horn that belonged to the farmer sowing his corn that kept the rooster that crowed in the morn that woke the priest all shaven and shorn that married the man all tattered and torn that kissed the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.", 10, 0

table:
        dq -1, 381, 360, 343, 323, 302, 259, 224, 182, 137, 91, 54, 0


section .text
global recite

; extern void recite(char *buffer, int start_verse, int end_verse);
recite:
        cld
        mov     r8, rsi
        mov     r9, rdx
        lea     rdx, [table]
        shl     r8, 3
        shl     r9, 3
        add     r8, rdx                 ; address of offset for current verse
        add     r9, rdx                 ; address of offset for end verse

.loop:
        lea     rsi, [lyrics]
        mov     rcx, 7
        rep     movsb

        mov     rdx, [r8]               ; offset for current verse
        add     rsi, rdx

.append:
        lodsb
        stosb
        test    al, al
        jnz     .append

        dec     rdi
        add     r8, 8                 ; address of offset for next verse
        cmp     r8, r9
        jle     .loop

        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
