section .text

extern exit
extern malloc
extern free

assert:
        test    rdi, rdi
        jne     .L1
        push    rax
        or      edi, -1
        call    exit
.L1:
        ret

global list_create
list_create:
        push    rcx
        mov     edi, 16
        call    malloc
        test    rax, rax
        je      .L7
        mov     qword [rax], 0
        mov     qword [rax+8], 0
.L7:
        pop     rdx
        ret

global list_count
list_count:
        push    rbx
        mov     rbx, rdi
        call    assert
        mov     rdx, qword [rbx]
        xor     eax, eax
.L15:
        test    rdx, rdx
        je      .L13
        mov     rdx, qword [rdx+8]
        inc     rax
        jmp     .L15
.L13:
        pop     rbx
        ret

global list_push
list_push:
        push    r12
        push    rbp
        mov     ebp, esi
        push    rbx
        mov     rbx, rdi
        call    assert
        mov     edi, 24
        mov     r12, qword [rbx+8]
        call    malloc
        test    rax, rax
        je      .L17
        cmp     qword [rbx], 0
        mov     qword [rax], r12
        mov     qword [rax+8], 0
        mov     DWORD [rax+16], ebp
        mov     qword [rbx+8], rax
        jne     .L19
        mov     qword [rbx], rax
        jmp     .L17
.L19:
        mov     qword [r12+8], rax
.L17:
        pop     rbx
        pop     rbp
        pop     r12
        ret

global list_pop
list_pop:
        push    r12
        push    rbp
        push    rbx
        mov     rbx, rdi
        call    assert
        mov     rbp, qword [rbx+8]
        mov     rdi, rbp
        call    assert
        mov     rax, qword [rbp+0]
        mov     r12d, DWORD [rbp+16]
        mov     qword [rbx+8], rax
        cmp     rbp, qword [rbx]
        jne     .L25
        mov     qword [rbx], 0
        jmp     .L26
.L25:
        mov     qword [rax+8], 0
.L26:
        mov     rdi, rbp
        call    free
        mov     eax, r12d
        pop     rbx
        pop     rbp
        pop     r12
        ret

global list_unshift
list_unshift:
        push    r12
        push    rbp
        mov     ebp, esi
        push    rbx
        mov     rbx, rdi
        call    assert
        mov     edi, 24
        mov     r12, qword [rbx]
        call    malloc
        test    rax, rax
        je      .L28
        cmp     qword [rbx+8], 0
        mov     qword [rax], 0
        mov     qword [rax+8], r12
        mov     DWORD [rax+16], ebp
        mov     qword [rbx], rax
        jne     .L30
        mov     qword [rbx+8], rax
        jmp     .L28
.L30:
        mov     qword [r12], rax
.L28:
        pop     rbx
        pop     rbp
        pop     r12
        ret

global list_shift
list_shift:
        push    r12
        push    rbp
        push    rbx
        mov     rbx, rdi
        call    assert
        mov     rbp, qword [rbx]
        mov     rdi, rbp
        call    assert
        mov     rax, qword [rbp+8]
        mov     r12d, DWORD [rbp+16]
        mov     qword [rbx], rax
        cmp     rbp, qword [rbx+8]
        jne     .L36
        mov     qword [rbx+8], 0
        jmp     .L37
.L36:
        mov     qword [rax], 0
.L37:
        mov     rdi, rbp
        call    free
        mov     eax, r12d
        pop     rbx
        pop     rbp
        pop     r12
        ret

global list_delete
list_delete:
        push    rbp
        mov     ebp, esi
        push    rbx
        mov     rbx, rdi
        push    rcx
        call    assert
        mov     rcx, qword [rbx]
        mov     rdi, rcx
.L41:
        test    rdi, rdi
        je      .L39
        mov     rdx, qword [rdi+8]
        cmp     DWORD [rdi+16], ebp
        je      .L48
        mov     rdi, rdx
        jmp     .L41
.L48:
        mov     rax, qword [rdi]
        cmp     rdi, rcx
        jne     .L42
        mov     qword [rbx], rdx
        jmp     .L43
.L42:
        mov     qword [rax+8], rdx
.L43:
        cmp     qword [rbx+8], rdi
        jne     .L44
        mov     qword [rbx+8], rax
        jmp     .L45
.L44:
        mov     rdx, qword [rdi+8]
        mov     qword [rdx], rax
.L45:
        pop     rdx
        pop     rbx
        pop     rbp
        jmp     free
.L39:
        pop     rax
        pop     rbx
        pop     rbp
        ret

global list_destroy
list_destroy:
        test    rdi, rdi
        je      .L49
        push    rbp
        mov     rbp, rdi
        push    rbx
        push    rdx
        mov     rdi, qword [rdi]
.L52:
        test    rdi, rdi
        je      .L51
        mov     rbx, qword [rdi+8]
        call    free
        mov     rdi, rbx
        jmp     .L52
.L51:
        pop     rax
        mov     rdi, rbp
        pop     rbx
        pop     rbp
        jmp     free
.L49:
        ret
