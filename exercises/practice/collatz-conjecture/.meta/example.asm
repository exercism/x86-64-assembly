section .text
;
; Find the number of steps to reach 1 using the Collatz conjecture
;
; Parameters:
;   rdi - number
; Returns:
;   rax - number of steps
;
global steps
steps:
    test    edi, edi                       ; check if arg is 0
    jle     .fail
    xor     eax, eax                       ; initialize step count
    cmp     edi, 1                         ; return 0 if 1
    je      .ret
.loop:
    add     eax, 1                         ; increment step count
    test    dil, 1                         ; check if odd/even
    jne     .odd
    mov     edx, edi                       ; even : divide by 2
    ; shr     edx, 31
    ; add     edi, edx
    sar     edi, 1
    cmp     edi, 1                         ; check if loop ends
    jne     .loop
    ret
.odd:
    lea     edi, [rdi+1+rdi*2]            ; odd : number = (number * 3) + 1;
    cmp     edi, 1                        ; check if loop ends
    jne     .loop
    ret
.fail:
    mov     eax, -1                       ; return ERROR_VALUE on failure
.ret:
    ret