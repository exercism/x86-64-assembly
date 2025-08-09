section .text
global sum
sum:
    ; rdi - limit as uint64_t
    ; rsi - input array of uint64_t, representing factors
    ; rdx - size of input array as size_t (uint64_t)
    ; return is a uint64_t in rax

    mov r8, rdi

    ; prologue
    push rbp
    mov rbp, rsp
    sub rsp, r8 ; array of bytes representing each potential multiple
                ; limit is exclusive


    lea rdi, [rsp]
    mov rcx, r8
    mov al, 0
    cld
    rep stosb ; initializes array to all "false"

    lea rdi, [rsp]
    mov rcx, -1
extract_factor:
    inc rcx
    cmp rcx, rdx
    jge end_extraction ; reached end of input array

    lodsq
    cmp rax, 0
    jle extract_factor ; zero has no multiple other than itself and doesn't contribute to the sum.
                       ; negative numbers are not factors

    mov r9, rax
fill_multiples:
    cmp r9, r8
    jge extract_factor ; limit is exclusive

    mov byte [rdi + r9], 1 ; sets multiple as "true"
    add r9, rax ; gets next multiple
    jmp fill_multiples

end_extraction:
    xor rax, rax ; accumulator
    mov rcx, r8
accumulate_factors:
    mov r10b, byte [rdi + rcx]
    xor r11, r11
    cmp r10b, 1
    cmove r11, rcx ; conditional move reduces branching and makes the loop a bit more tight
                   ; it also makes using LOOP easier, reducing overall code size
    add rax, r11
    loop accumulate_factors

end_sum:
    ;epilogue
    mov rsp, rbp
    pop rbp
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
