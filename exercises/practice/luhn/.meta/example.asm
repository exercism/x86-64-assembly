section .text
global valid
valid:
    cld ; rsi will be incremented with each lodsb
    mov rsi, rdi
    dec rdi ; the address immediately before the first character
    xor rax, rax
    xor rcx, rcx ; number of digits read
    xor r8, r8 ; total
    mov r10, 10

.seek_end:
    lodsb
    test al, al
    jnz .seek_end

    sub rsi, 2 ; the address immediately before the null character
    std ; rsi will be decremented with each lodsb
    jmp .check_end

.read:
    lodsb
    cmp al, ' '
    je .check_end

    sub al, '0'
    cmp al, 10
    jae .invalid

    inc rcx
    test rcx, 1
    jnz .odd

    shl rax, 1
    cmp rax, 9
    jb .odd

    sub rax, 9

.odd:
    add r8, rax

.check_end:
    cmp rsi, rdi
    jne .read

    cmp rcx, 1
    jbe .invalid

    mov rax, r8
    xor rdx, rdx
    div r10
    test rdx, rdx
    jnz .invalid

.valid:
    cld
    mov rax, 1
    ret

.invalid:
    cld
    xor rax, rax
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
