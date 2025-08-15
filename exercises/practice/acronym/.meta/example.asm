section .text
isalpha:
        xor     eax, eax
        and     edi, -33
        sub     edi, 65
        cmp     dil, 25
        setbe   al
        ret
toupper:
        mov     eax, edi
        and     eax, -33
        ret
global abbreviate
abbreviate:
        mov     rax, rdi
        test    rdi, rdi
        je      .null
        mov     dl, [rdi]
        test    dl, dl
        je      .empty
        mov     [rsi], dl
        push    r14
        push    r13
        push    r12
        lea     r12, [rsi+1]
        push    rbp
        mov     rbp, rsi
        push    rbx
        lea     rbx, [rdi+1]
.loop:
        mov     al, [rbx]
        test    al, al
        je      .fin
        cmp     al, 45
        je      .check_alpha
        cmp     al, 32
        jne     .next
.check_alpha:
        movsx   r13d, byte [rbx]
        mov     r14, rbx
        inc     rbx
        mov     edi, r13d
        call    isalpha
        test    eax, eax
        je      .check_alpha
        mov     edi, r13d
        inc     r12
        mov     rbx, r14
        call    toupper
        mov     [r12-1], al
.next:
        inc     rbx
        jmp     .loop
.fin:
        mov     byte [r12], 0
        mov     rax, rbp
        pop     rbx
        pop     rbp
        pop     r12
        pop     r13
        pop     r14
        ret
.empty:
        xor     eax, eax
        ret
.null:
        ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
