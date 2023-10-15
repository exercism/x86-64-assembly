section .text
global can_create
; rdi - row
; rsi - column
; rax - result
; rdx - 7
can_create:
    xor rax, rax
    mov rdx, 7
    cmp rdi, rdx
    ja .return
    cmp rsi, rdx
    ja .return
    inc rax
.return:
    ret

; rdi - white row
; rsi - white column
; rdx - black row
; rcx - black column
global can_attack
can_attack:
    xor rax, rax
    sub rdi, rdx      ; row difference
    jz .attacks
    sub rsi, rcx      ; column difference
    jz .attacks
    cmp rdi, rsi
    jz .attacks
    add rdi, rsi
    jz .attacks
    ret

.attacks:
    inc rax
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
