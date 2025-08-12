section .text
global triplets_with_sum
triplets_with_sum:
    ; rdi - desired sum as a uint64_t
    ; rsi - output array of uint64_t for side a
    ; rdx - output array of uint64_t for side b
    ; rcx - output array of uint64_t for side c
    ; output arrays should be modified in place and have the same side
    ; said size should be returned as a uint64_t in rax

    push r12
    push r13
    push r14
    push r15

    xor rax, rax ; size of triplet arrays
    mov r11, rdi
    dec r11
main_loop:
    dec r11 ; current c

    cmp r11, 1
    jl end_loop

    mov r8, rdi
    sub r8, r11 ; diff between sum and c

    mov r12, r8
    shr r12, 1 ; max value for a
               ; if a is greater than half the difference
               ; then b is smaller than a and repeating triplets appear
    
    xor r9, r9
second_loop:
    inc r9 ; current a

    cmp r9, r12
    jg main_loop

    mov r10, r8
    sub r10, r9 ; current b

    mov r13, r9
    imul r13, r13 ; a²

    mov r14, r10
    imul r14, r14 ; b²

    mov r15, r11
    imul r15, r15 ; c²

    add r13, r14 ; a² + b²
    cmp r13, r15
    jne second_loop

    ; a² + b² == c²

    inc rax

    mov qword [rsi], r9
    add rsi, 8

    mov qword [rdx], r10
    add rdx, 8

    mov qword [rcx], r11
    add rcx, 8

    jmp second_loop
end_loop:
    pop r15
    pop r14
    pop r13
    pop r12

    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
