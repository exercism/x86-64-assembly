section .text

global add_bonus
add_bonus:
    lea rax, [rdi + rsi]
    mov rdi, 999999
    cmp rax, rdi
    cmovg rax, rdi
    ret

global compare_scores
compare_scores:
    cmp rdi, rsi
    setg al
    setl dl
    sub al, dl
    movsx rax, al
    ret

global validate_score
validate_score:
    mov rax, rdi
    cmp rax, rsi
    cmovl rax, rsi
    cmp rax, rdx
    cmovg rax, rdx
    ret

global top_two
top_two:
    xor r8d, r8d                   ; first  = 0
    xor r9d, r9d                   ; second = 0
    xor ecx, ecx                   ; index = 0
    test rdx, rdx
    jz .done

.loop:
    mov rax, qword [rsi + 8*rcx]   ; candidate
    inc rcx
    cmp rax, r9
    cmovg r9, rax                  ; if candidate > second, second = candidate
    cmp rax, r8
    cmovg r9, r8                   ; if candidate > first, second = first
    cmovg r8, rax                  ; if candidate > first, first = candidate
    cmp rcx, rdx
    jb .loop

.done:
    mov qword [rdi], r8            ; save first
    mov qword [rdi + 8], r9        ; save second
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
