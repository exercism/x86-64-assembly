section .text

%macro filter 1
    xor eax, eax

    test rdx, rdx
    jz %%exit

    push rbp
    push rbx
    push r12
    push r13
    push r14
    push r15
    sub rsp, 8 ; stack 16-byte aligned

    mov rbp, rdi ; crt input pointer
    mov rbx, rdi ; crt output pointer
    mov r12, rsi ; elem size -> stride for input and output
    mov r13, rdx ; num elements
    mov r14, rcx ; predicate function

    xor r15d, r15d ; counter for the number of elements kept/discarded
    sub rbp, r12
    sub rbx, r12
%%loop:
    add rbp, r12

    mov rdi, rbp ; the current input pointer is argument for the predicate
    call r14

    test al, al
    %1 %%next    ; keep and discard differ only in this jump

    ; element is kept or discarded

    inc r15      ; increase counter
    add rbx, r12 ; set output pointer to the next element
    cmp rbx, rbp
    je %%next ; no copy needed, elements are already in-place

    ; otherwise, we copy
    ; the functions accept any element size, so we proceed byte-by-byte

    mov rcx, r12
    mov rsi, rbp
    mov rdi, rbx
    rep movsb
%%next:
    dec r13
    jnz %%loop

    mov rax, r15

    add rsp, 8
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
%%exit:
%endmacro

global keep
keep:
    filter jz
    ret

global discard
discard:
    filter jnz
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
