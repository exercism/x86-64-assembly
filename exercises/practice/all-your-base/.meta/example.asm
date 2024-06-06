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
    xor rbx, rbx

    ; Return
    ; %rax - number of digits in output array

    ; First, check the bases
    ; remember - ints are 32 bits!
    cmp edx, 2
    jl .bad_base

    cmp r8d, 2
    jl .bad_base

    ; Part 1 - Parse the input digits
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

    cmp r9d, esi
    je .convert

    test r10d, r10d
    js .bad_digit

    cmp r10d, edx
    jge .bad_digit

    imul eax, edx
    add rax, r10

    inc r9d
    jmp .parse_digits

.convert:
    ; Part 2 - Convert the number back to a list of digits
    ; %rbx - number of output digits
    ; %edx - will have the next digit
    xor rbx, rbx

.get_digits_loop:
    xor rdx, rdx

    div r8d
    push rdx

    inc rbx
    cmp eax, 0
    jg .get_digits_loop

    ; Copy the number of digits to return
    mov eax, ebx

    cmp ebx, 0
    je .return

    xor rbx, rbx

.add_to_list:
    pop r10
    mov dword [rcx + (rbx* 4)], r10d
    inc rbx
    cmp rbx, rax
    jne .add_to_list

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
