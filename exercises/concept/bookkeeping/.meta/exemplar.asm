section .bss
    transaction resq 1

section .text
global remember_transaction
remember_transaction:
    mov qword [rel transaction], rdi
    ret

global apply_remembered
apply_remembered:
    jmp [rel transaction]

global register_transaction
register_transaction:
    mov qword [rdi + 8*rsi], rdx
    ret

global select_transaction
select_transaction:
    mov rax, qword [rdi + 8*rsi]
    mov rdi, rdx
    jmp rax

global process_statement
process_statement:
    push r12
    push r13
    push r14 ; stack 16-byte aligned

    mov r12, rsi
    xor r13d, r13d
    mov r14, rdx
.loop:
    cmp r13, r14
    jae .end

    mov rax, qword [r12 + 8*r13]
    inc r13

    call rax
    mov rdi, rax

    jmp .loop
.end:
    mov rax, rdi

    pop r14
    pop r13
    pop r12
    ret

global process_with_guard
process_with_guard:
    push rbp
    push rbx
    push r12
    push r13
    push r14
    push r15
    sub rsp, 8   ; stack 16-byte aligned

    mov rbp, rdi ; balance
    xor ebx, ebx ; approved

    mov r12, rsi
    lea r13, [rsi + 8*rdx]
    mov r15, rcx ; guard
.loop:
    cmp r12, r13
    jae .end

    mov rdi, rbp
    mov rax, qword [r12]
    add r12, 8

    call rax

    mov r14, rax   ; partial result
    mov rdi, rax
    call r15       ; check if valid

    test al, al
    jz .loop       ; not valid, approved and balance unchanged
    ; otherwise

    inc rbx        ; increase approved
    mov rbp, r14   ; balance is last result

    jmp .loop
.end:
    mov rax, rbp
    mov rdx, rbx

    add rsp, 8
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
