section .text

global admit_group
admit_group:
    lock add qword [rdi], rsi
    ret

global change_reel
change_reel:
    mov rax, rsi
    xchg qword [rdi], rax
    ret

global sell_ticket
sell_ticket:
    mov rax, 1
    lock xadd qword [rdi], rax
    inc rax
    ret

global claim_seat
claim_seat:
    mov rax, qword [rdi] ; current count
.retry:
    cmp rax, rsi
    jge .full            ; reached full capacity

    lea rcx, [rax + 1]
    lock cmpxchg qword [rdi], rcx ; try incrementing
    jnz .retry           ; seat changed, retry
    ; otherwise increment was successful

    mov rax, rcx
    ret

.full:
    xor eax, eax
    ret

global visit_booth
visit_booth:
    push rbx      ; stack 16-byte aligned
    mov rbx, rdi  ; save rdi for after the call
.acquire:
    lock bts qword [rbx], 0
    jc .wait      ; lock was already acquired, wait

    call rsi      ; rsi is not reused, it may be clobbered

    mov qword [rbx], 0 ; release lock
    pop rbx
    ret

.wait:
    pause
    jmp .acquire ; retry

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
