; Everything that comes after a semicolon (;) is a comment

section .text

; This function is already pre-defined and matches the example in the concept
factorial:
    ; This function takes a 64-bit non-negative integer as argument
    ; It computes the factorial of this argument
    ; and returns it as a 64-bit non-negative integer
    mov rax, 1
factorial_helper:
    cmp rdi, 1
    jle .base_case

    imul rax, rdi
    dec rdi
    jmp factorial_helper
.base_case:
    ret

global largest_portion
largest_portion:
    ; TODO: Define the `largest_portion`
    ; This function takes two 64-bit non-negative integers as arguments
    ; It calculates the greatest common divisor (gcd) of both numbers
    ; and returns it as a 64-bit non-negative integer
    ret


global double_factorial
double_factorial:
    ; TODO: Define the `double_factorial` function
    ; This function takes one 32-bit non-negative integer as argument
    ; It calculates its double factorial
    ; and returns it as a 64-bit non-negative integer
    ;
    ; The double factorial (!!) is defined as:
    ;
    ; 0!! = 1
    ; n!! = 1 * 3 * 5 * ... * n if n is odd
    ; n!! = 2 * 4 * 6 * ... * n if n is even
    ret

global pipers_pi
pipers_pi:
    ; TODO: Define the `pipers_pi` function
    ; This function takes a 32-bit non-negative integer as argument
    ; It calculates an approximation of π using the Newton/Euler Convergence Transformation
    ; and returns it as a 64-bit floating-point number
    ;
    ; The Newton/Euler Convergence Transformation is defined as a sum:
    ;
    ; π / 2 = sum for k from 0 to infinity of ( k! ) / ( 2 * k + 1 )!!
    ; (where ! designates the factorial and !!, the double factorial)
    ;
    ; Your approximation should sum n + 1 terms, where n is the argument
    ; This means the argument is the upper limit of the sum
    ;
    ; You can reuse `factorial` and `double_factorial`, defined above
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
