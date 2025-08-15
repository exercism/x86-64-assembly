default rel

INVALID_NUMBER equ -1

section .text
global prime

prime:
    ; rdi - number as a uint64_t
    ; return is an int64_t in rax

    ; The algorithm is a naive approach with brute force
    ; It uses the stack by reducing the rsp pointer to store last computed prime
    ; Until a counter reaches the desired n
    ; This "dynamic array" on the stack starts with 2 and then it only needs to check for odd primes
    ; The check consists of iterating over the array, dividing the factor for each pre-computed prime
    ; and checking for non-zero remainder
    ;
    ; This approach was chosen primarily to check the speed of assembly even with an inefficient algorithm
    ; and considering the presence of an additional test case for a very big prime (the 65537th)
    ;
    ; A possible more efficient algorithm would estimate upper bound for the nth-prime and use sieve
    ; There's a FYL2X which computes log2 (x) and can be used to convert between bases to ln (x)
    ; TODO on a second iteration

    cmp rdi, 1
    jl invalid_number ; there's no zeroth prime

    ; prologue
    push rbp
    mov rbp, rsp
    sub rsp, 8 
    mov qword [rsp], 2 ; stack array starts with one element: 2

    mov r8, 1 ; counter for size of array
    mov r9, 1 ; last factor (loops starts by adding 2, so the first factor to be examined is 3)
main_loop:
    cmp r8, rdi
    je return ; found the nth-prime

get_factor:
    add r9, 2 ; current factor
    mov rcx, r8 ; for using LOOP
check_prime:
    mov r10, qword [rsp + 8*rcx - 8] ; iteratively gets all previous primes
    
    mov rax, r9 ; for dividing
    xor rdx, rdx ; for dividing
    div r10

    cmp rdx, 0
    je get_factor ; if remainder is 0, factors is not prime

    loop check_prime ; if remainder is non-zero, loops over to next prime in array
    ; if all primes were checked, factor is not divisible by any and therefore must be prime

store_prime:
    sub rsp, 8
    mov qword [rsp], r9 ; adds factor to prime array
    inc r8 ; increments size counter

    jmp main_loop ; iterates until the nth-prime is found
return:
    mov rax, qword [rsp] ; the nth-prime is the last in the array

    ; epilogue
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
