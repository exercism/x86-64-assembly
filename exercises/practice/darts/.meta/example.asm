default rel

section .rodata
    outer_radius dq 10.0
    mid_radius dq 5.0
    inner_radius dq 1.0

section .text
global score
score:
    ; xmm0 - a double representing x
    ; xmm1 - a double representing y
    ; output is a uint8_t in al

    mulsd xmm0, xmm0 ; x^2
    mulsd xmm1, xmm1 ; y^2
    addsd xmm0, xmm1 ; x^2 + y^2
    sqrtsd xmm0, xmm0 ; square root of x^2 + y^2, or distance to the center

    xor rax, rax ; base value is 0

    movsd xmm1, qword [outer_radius]
    ucomisd xmm0, xmm1
    ja outside_target ; if distance is greater than outer circle, missed the target

    movsd xmm1, qword [mid_radius]
    ucomisd xmm0, xmm1
    ja inside_outer_circle ; if distance is greater than mid circle, it's between mid and outer

    movsd xmm1, qword [inner_radius]
    ucomisd xmm0, xmm1
    ja inside_middle_circle ; if distance is greater than inner circle, it's between inner and mid
    ; otherwise, it's inside inner circle

    ; instructions fall through, accumulating values to give the total for each case
    add al, 5
inside_middle_circle:
    add al, 4
inside_outer_circle:
    add al, 1
outside_target:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
