default rel

INVALID_NUMBER equ -1

section .text
global prime

prime:
    ; rdi - number as a uint64_t
    ; return is an int64_t in rax

    cmp rdi, 1
    jl invalid_number ; there's no zeroth prime

    ; According to https://t5k.org/howmany.html:
    ;
    ; If n >= 13:
    ; p(n) <= n (ln n + ln (ln n) - 1 + 1.8 * ln (ln n) / ln n)
    ; and, for all n:
    ; n (ln n + ln ln n - 1) < p(n)
    ; where log is the natural logarithm
    ;
    ; since log2(x) = ln(x) / ln(2)
    ; this upper bound is equivalent to:
    ; p(n) <= n * (ln(2) * (log2(n) + log2(ln(2) * log2(n))) - 1 + 1.8 * log2(ln(2) * log2(n)) / log2(n) )
    ;
    ; But, since:
    ; 1- ln(2) ~ 0.69;
    ; 2- all numbers are positive;
    ; 3- log is strictly increasing with n;
    ; 4- for n >= 2, log2(n) >= 1 and log2(n) <<< n;
    ; then:
    ; log2(ln(2) * log2(n)) / log2(n) < 1 -> 1.8 * log2(ln(2) * log2(n)) / log2(n) < 2
    ; so:
    ; p(n) <= n * (log2(n) + log2(log2(n))) + 1, for n >= 13
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
    ; Those transformations also make the upper bound valid for all n >= 1 (checked manually)

    lzcnt r11, rdi ; floor(log2n)
    inc r11 ; floor(log2(n)) + 1

    lzcnt r10, r11 ; floor(log2(log2n))
    inc r10 ; ; floor(log2(log2n)) + 1

    add r10, r11 ; >= log2n + log2(log2n)
    imul r10, rdi ; >= n*(log2n + log2(log2n))
    inc r10 ; r10 is now a safe upper bound for a prime table

    push rbp
    mov rsp, rbp
    sub rsp, r10

    ; from now, it's a simple sieve with a counter

    mov rdx, r10
    mov rcx, r10

    mov r10, rdi
    mov rdi, rsp
    mov rax, 1

    rep stosb ; initialize table with true

    xor r11, r11 ; counter for nth prime
    mov r9, 1 ; current prime

.find_nth_prime:
    inc r9

    cmp r9, rdx
    jge .return

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
