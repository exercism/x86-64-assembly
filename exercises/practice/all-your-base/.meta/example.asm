section .text
global rebase

rebase:
    ; Argument registers
    ; %rdi - input digits array
    ; %esi - number of input digits
    ; %edx - input base
    ; %rcx - output array
    ; %r8d - output base

    xor rax, rax

    ; First, check the bases
    ; remember - ints are 32 bits!
    cmp edx, 2
    jl .bad_base

    cmp r8d, 2
    jl .bad_base

    ; Part 1 - Parse the number from the input
    ; %r9d - digit's index
    ; %eax - sum & result
    ; %r10 - next digit
    xor r9, r9
    xor rax, rax

.parse_digits:
    xor r10, r10

    cmp r9d, esi
    je .convert

    ; Load next digit to add
    mov r10d, dword [rdi + (r9 * 4)]

    test r10d, r10d
    js .bad_digit

    cmp r10d, edx
    jge .bad_digit

    imul eax, edx
    add rax, r10

    inc r9d
    jmp .parse_digits

.convert:
    ; Part 2 - Convert the number back to a list of digits. Note, this
    ;          algorithm will produce the digits in reverse order.
    ; %r9 - number of output digits
    ; %edx - will have the next digit
    xor r9, r9

.get_digits_loop:
    xor rdx, rdx

    div r8d

    ; Copy remainder to array
    mov [rcx + 4 * r9], rdx

    inc r9
    cmp eax, 0
    jg .get_digits_loop

    ; Copy the number of digits to return
    mov rax, r9

    ; Reverse the digits to get the final result.
    ; %rcx track the address from the beginning of list
    ; %r9 track the address from the end
    lea r9, [rcx + 4*(rax - 1)]

.reverse_list:
    cmp rcx, r9
    jge .return

    mov r10d, dword [rcx]
    mov r11d, dword [r9]

    mov dword [r9], r10d
    mov dword [rcx], r11d

    add rcx, 4
    sub r9, 4
    jmp .reverse_list

.return:
    ret

.bad_base:
    mov rax, -1
    ret

.bad_digit:
    mov rax, -2
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
