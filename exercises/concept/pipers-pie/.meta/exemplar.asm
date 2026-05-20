section .text

factorial:
    mov rax, 1
factorial_helper:
    cmp rdi, 1
    jle .base_case

    imul rax, rdi
    dec rdi
    jmp factorial_helper
.base_case:
    ret

global largest_portion
largest_portion:
    test rsi, rsi
    jz .base_case

    mov rax, rdi
    xor edx, edx
    div rsi
    mov rdi, rsi
    mov rsi, rdx
    jmp largest_portion
.base_case:
    mov rax, rdi
    ret

global double_factorial
double_factorial:
    mov edi, edi
    mov rax, 1
.helper:
    cmp edi, 1
    jbe .base_case

    imul rax, rdi
    sub edi, 2
    jmp .helper
.base_case:
    ret

global pipers_pi
pipers_pi:
    push r12
    push r13
    sub rsp, 8 ; stack 16-byte aligned

    xor r12d, r12d
    cvtsi2sd xmm0, r12
    mov r13d, edi
.helper:
    cmp r12d, r13d
    ja .base_case

    mov edi, r12d
    call factorial

    cvtsi2sd xmm1, rax

    lea edi, [r12d + r12d + 1]
    call double_factorial

    cvtsi2sd xmm2, rax

    divsd xmm1, xmm2
    addsd xmm0, xmm1

    inc r12
    jmp .helper
.base_case:
    addsd xmm0, xmm0

    add rsp, 8
    pop r13
    pop r12
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
