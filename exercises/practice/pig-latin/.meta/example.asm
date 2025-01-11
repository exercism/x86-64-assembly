VOWELS equ 0x1104111                    ; lowest set bit is for A, highest set bit is for Y

section .text
global translate

; extern void translate(char *buffer, const char *phrase);
translate:
        cld
        mov     r8, VOWELS

check_rule_1:
        mov     r9, rsi                 ; start of word
        mov     dl, byte [rsi]          ; dl is first letter of word
        mov     al, byte [rsi + 1]      ; al is second letter of word

        mov     cl, dl
        sub     cl, 'a'
        mov     r11, 1
        shl     r11, cl
        test    r11, r8
        jz      check_xr                ; word does not start with {a,e,i,o,u,y}

        cmp     dl, 'y'
        jne     write

        cmp     al, 't'
        je      write                   ; word starts with yt

check_xr:
        cmp     dl, 'x'
        jne     check_rule_2

        cmp     al, 'r'
        je      write                   ; word starts with xr

check_rule_2:
                                        ; Rule 1 does not apply
        inc     rsi
        mov     al, byte [rsi]
        test    al, al
        jz      write

        cmp     al, ' '
        je      write

        mov     cl, al
        sub     cl, 'a'
        mov     r11, 1
        shl     r11, cl
        test    r11, r8
        jz      check_rule_2

check_rule_3:
                                        ; we have found {a,e,i,o,u,y}
        mov     dl, byte [rsi - 1]
        mov     al, byte [rsi]

        cmp     dl, 'q'
        jne     write

        cmp     al, 'u'
        jne     write

        inc     rsi                     ; we have found qu

write:
        mov     r10, rsi                ; end of prefix

copy_body:
        lodsb
        test    al, al
        jz      end_body

        cmp     al, ' '
        je      end_body

        stosb
        jmp     copy_body

end_body:
        mov     r11, rsi
        mov     rsi, r9

copy_prefix:
        cmp     rsi, r10
        je      end_prefix

        lodsb
        stosb
        jmp     copy_prefix

end_prefix:
        mov     al, 'a'
        stosb

        mov     al, 'y'
        stosb

        mov     rsi, r11
        dec     rsi                     ; address of ' ' or '\0' at end of word
        lodsb
        stosb
        test    al, al
        jnz     check_rule_1

        ret


%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
