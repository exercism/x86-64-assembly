CEILING_ROUNDING_CONTROL equ 2
FLOOR_ROUNDING_CONTROL equ 1

section .rodata
    BILLABLE_HOURS_IN_DAY dq 8.0, 0
    BILLABLE_DAYS_IN_MONTH dq 22.0, 0
    PERCENTAGE_DIVISOR dq 100.0, 0

section .text

global daily_rate
daily_rate:
    movsd xmm1, qword [rel BILLABLE_HOURS_IN_DAY]
    mulsd xmm0, xmm1
    ret

global apply_discount
apply_discount:
    movsd xmm2, qword [rel PERCENTAGE_DIVISOR]
    divsd xmm1, xmm2
    mulsd xmm1, xmm0
    subsd xmm0, xmm1
    ret

global monthly_rate
monthly_rate:
    call apply_discount
    call daily_rate
    movsd xmm1, qword [rel BILLABLE_DAYS_IN_MONTH]
    mulsd xmm0, xmm1
    roundsd xmm0, xmm0, CEILING_ROUNDING_CONTROL
    cvtsd2si rax, xmm0
    ret

global days_in_budget
days_in_budget:
    call apply_discount
    call daily_rate
    cvtsi2sd xmm1, rdi
    divsd xmm1, xmm0
    roundsd xmm0, xmm1, FLOOR_ROUNDING_CONTROL
    cvtsd2si eax, xmm0
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
