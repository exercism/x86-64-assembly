section .text
global can_create
; Rejects any row or column value outside the range 0..7
; rdi - row
; rsi - column
; rax - result
can_create:
    xor rax, rax
    mov rdx, 7
    cmp rdi, rdx
    ja .return        ; Unsigned comparison, so negative
                      ; values are also rejected.
    cmp rsi, rdx
    ja .return
    inc rax

.return:
    ret

; Queens can attack if they are on a common row, column or diagonal.
; rdi - white row
; rsi - white column
; rdx - black row
; rcx - black column
; rax - result
global can_attack
can_attack:
    xor rax, rax
    sub rdi, rdx      ; row difference
    jz .attacks
    sub rsi, rcx      ; column difference
    jz .attacks
    cmp rdi, rsi
    je .attacks
    add rdi, rsi
    jz .attacks
    ret

.attacks:
    inc rax
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
