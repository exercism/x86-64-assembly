section .text
global primes
primes:
    ; rdi - output array of uint32_t
    ; esi - limit
    ; output array should be modified in place
    ; the size of array is returned in eax

    xor rax, rax
    cmp esi, 2
    jl sieve_end ; if limit is less than 2 returns right away

    ; prologue 
    ; creates an array of bytes on the stack to represent possible primes
    mov r8d, esi
    inc r8d ; limit is inclusive

    push rbp
    mov rbp, rsp
    sub rsp, r8
    lea rsi, [rsp]

    ; sets all bytes to "true"
    mov r10, rdi
    mov rdi, rsi
    mov rcx, r8
    mov al, 1 
    cld
    rep stosb

    ; loops over the array to get factors
    mov rdi, r10
    mov r11, rsi
    mov rcx, 2 ; current number to check
    xor r9, r9 ; counter for num of primes

get_primes_loop:
    lodsb
    cmp al, 1
    je store_prime

next_factor:
    inc rcx
    cmp rcx, r8
    jl get_primes_loop

    ; epilogue
    mov rax, r9
    mov rsp, rbp
    pop rbp

sieve_end:
    ret
    
store_prime:
    mov rax, rcx
    stosd
    inc r9
    
remove_composites:
    add rax, rcx
    cmp rax, r8
    jge next_factor

    mov byte [r11 + rax - 2], 0
    jmp remove_composites

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
