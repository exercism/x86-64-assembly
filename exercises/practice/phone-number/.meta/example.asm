;
; Clean up user-entered phone number.
;
; Parameters:
;   rdi - output buffer address
;   rsi - input phrase address
; Locals:
;   al - the current character
;   rcx - number of digits read
;   r9 - start of output buffer
;   r10 - expected end of output
;
section .text
global clean
clean:
    cld                                 ; rsi/rdi will be incremented with each lodsb/stosb
    xor     rcx, rcx                    ; zero digits read
    mov     r9, rdi                     ; start of output buffer
    mov     r10, r9
    add     r10, 10                     ; expected end of output
    jmp     .read_digit

.process_digit:
    cmp     rdi, r10
    je      .reject                     ; too many digits

    cmp     rdi, r9
    je      .leading_digit

.store_digit:
    stosb                               ; write digit

.count_digit:
    inc rcx

.read_digit:
    lodsb                               ; read from input
    cmp     al, '9'
    jg      .reject                     ; reject letters and some punctuation like @

    cmp     al, '0'
    jge     .process_digit

    test    al, al
    jnz     .read_digit                 ; ignore punctuation like space + - ( )

    cmp     rdi, r10
    jne     .reject                     ; insufficient digits

    mov     dl, byte [r9 + 3]
    cmp     dl, '2'
    jb      .reject                     ; invalid exchange code

    stosb                               ; write '\0'
    ret

.leading_digit:
    cmp     al, '1'
    jg      .store_digit

    cmp     al, '0'
    je      .reject                     ; invalid area code

    jrcxz   .count_digit                ; consume NANP country code, once only

.reject:
    mov     rdi, r9                     ; start of output buffer
    xor     al, al
    stosb                               ; write '\0'
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
