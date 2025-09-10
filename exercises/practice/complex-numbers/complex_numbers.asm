section .text

global complex_real
global complex_imaginary
global complex_mul
global complex_add
global complex_sub
global complex_div
global complex_abs
global complex_conjugate
global complex_exp
global complex_real_add
global real_complex_add
global complex_real_sub
global real_complex_sub
global complex_real_mul
global real_complex_mul
global complex_real_div
global real_complex_div

complex_real:
    ; Provide your implementation here
    ret

complex_imaginary:
    ; Provide your implementation here
    ret

complex_mul:
    ; Provide your implementation here
    ret

complex_add:
    ; Provide your implementation here
    ret

complex_sub:
    ; Provide your implementation here
    ret

complex_div:
    ; Provide your implementation here
    ret

complex_abs:
    ; Provide your implementation here
    ret

complex_conjugate:
    ; Provide your implementation here
    ret

complex_exp:
    ; Provide your implementation here
    ret

complex_real_add:
    ; Provide your implementation here
    ret

real_complex_add:
    ; Provide your implementation here
    ret

complex_real_sub:
    ; Provide your implementation here
    ret

real_complex_sub:
    ; Provide your implementation here
    ret

complex_real_mul:
    ; Provide your implementation here
    ret

real_complex_mul:
    ; Provide your implementation here
    ret

complex_real_div:
    ; Provide your implementation here
    ret

real_complex_div:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
