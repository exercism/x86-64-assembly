default rel

INVALID_NUMBER equ -1

section .text
global prime

prime:
    ; rdi - number as a uint64_t
    ; return is an int64_t in rax

    cmp rdi, 1
    jl invalid_number ; there's no zeroth prime

    ; Rosser and Schoenfeld’s explicit bounds for primes:
    ; p(n) < n * (log(n) + log(log(n))), for n >= 6
    ; where log is the natural logarithm
    ;
    ; since log2(x) = ln(x) / ln(2)
    ; this is equivalent to:
    ; p(n) < n * (ln(2) * log2(n) + ln(2) * log2(ln(2) * log2(n))) = n * ln(2) *(log2(n) + log2(ln(2) * log2(n)))
    ;
    ; But, since:
    ; 1- ln(2) < 1;
    ; 2- all numbers are positive; and
    ; 3- log is strictly increasing with n
    ; then:
    ; p(n) < n * (log2(n) + log2(log2(n)))
    ;
    ; This is the upper bound used here
    ;
    ; The advantage of using logarithms in base 2 is that its floor can be approximated with
    ; the index of the leading bit of a number in binary form
    ; which can be found with a simple instruction in x86-64 (lzcnt or bsr)
    ;
    ; Since this is the floor(log2(x)) and since we are dealing with a upper bound,
    ; increasing it by 1 is enough to ensure consistency
    ;
    ; Those transformations also make Rosser and Schoenfeld’s bounds valid for all n > 1

    lzcnt r11, rdi ; floor(log2n)
    inc r11

    lzcnt r10, r11 ; floor(log2(log2n))
    inc r10

    add r10, r11 ; >= log2n + log2(log2n)
    imul r10, rdi ; >= n*(log2n + log2(log2n)) ; r10 is now a safe upper bound for a prime table

    push rbp
    mov rsp, rbp
    sub rsp, r10

    ; from now, it's a simple sieve with a counter

    mov rcx, r10
    mov r10, rdi
    mov rdi, rsp
    mov rax, 1

    rep stosb ; initialize table with true

    xor r11, r11 ; counter for nth prime
    mov r9, 1 ; current prime

.find_nth_prime:
    inc r9

    cmp byte [rsp + r9], 1
    jne .find_nth_prime

    inc r11
    cmp r11, r10
    je .return

.clear_composites:
    lea r8, [rsp + r9]
.clear_loop:
    add r8, r9

    cmp r8, rbp
    jge .find_nth_prime

    mov byte [r8], 0
    jmp .clear_loop

.return:
    mov rax, r11

    mov rsp, rbp
    pop rbp
    ret

invalid_number:
    ; no need for epilogue, because the check for valid input occurs before prologue
    mov rax, INVALID_NUMBER
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
