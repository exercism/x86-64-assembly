default rel

section .rodata
    introductory_string db "Hi! This is an example introduction.", 0
    introductory_string_sz dq $-introductory_string

section .text

global create_item_entry
create_item_entry:
    mov qword [rdi], rsi
    mov qword [rdi + 8], rdx
    mov qword [rdi + 16], rcx
    mov qword [rdi + 24], r8
    mov qword [rdi + 32], r9
    mov rcx, r9
    lea rsi, [rsp + 8]
    lea rdi, [rdi + 40]
    rep movsq
    ret

global create_monthly_list
create_monthly_list:
    push rdi
    call rsi
    mov rdi, rax
    pop rcx
    push rax
    mov al, 0
    rep stosb
    pop rax
    ret

global insert_found_item
insert_found_item:
    imul rsi, rsi, 120
    lea rdi, [rdi + rsi]
    lea rsi, [rsp + 8]
    mov rcx, 120
    rep movsb
    ret

global print_item
print_item:
    push rbp
    mov rbp, rsp
    push rcx ; printing function
    push rdi

    imul r10, rdx, 120
    lea r10, [rsi + r10]

    lea rsi, [introductory_string]
    mov rcx, qword [introductory_string_sz]
    rep movsb

    mov rdi, qword [rsp]
    mov rsi, rdx
    mov rdx, qword [r10]
    mov rcx, qword [r10 + 8]
    mov r8, qword [r10 + 16]
    mov r9, qword [r10 + 24]

    lea rax, [r10 + 40]
    push rax
    push qword [r10 + 32]

    call qword [rbp - 8]

    mov rsp, rbp
    pop rbp
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
