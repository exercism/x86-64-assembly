;
; Compute the prime factors of a given natural number.
;
; Parameters:
;   rdi - destination
;   rsi - number to be factored
; Returns:
;   rax - factor count
;
section .text
global factors
factors:
    cld ; each stosq will increase rdi
    mov r8, 2 ; candidate factor is 2 3 5 7 9 11 etc.
    mov r9, 1 ; step is 1, then 2
    mov rcx, rdi
    jmp .square

.next_candidate:
    add r8, r9
    mov r9, 2

.square:
    mov rax, r8
    mul r8
    cmp rsi, rax
    jl .break ; exit loop when candidate squared exceeds number

    mov rax, rsi
    xor rdx, rdx
    div r8
    test rdx, rdx
    jnz .next_candidate ; advance to next candidate if remainder is non-zero

    mov rsi, rax ; replace number with quotient
    mov rax, r8
    stosq ; output factor
    jmp .square

.break:
    cmp rsi, 1
    je .report

    mov rax, rsi
    stosq ; output number

.report:
    mov rax, rdi
    sub rax, rcx
    shr rax, 3
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
