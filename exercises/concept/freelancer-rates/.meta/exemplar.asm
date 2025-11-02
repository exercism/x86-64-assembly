section .text

global daily_rate
global apply_discount
global monthly_rate
global days_in_budget

daily_rate:
    mov rax, 8
    cvtsi2sd xmm1, rax
    mulsd xmm0, xmm1
    ret

apply_discount:
    mov rax, 100
    cvtsi2sd xmm2, rax
    mulsd xmm1, xmm0
    divsd xmm1, xmm2
    subsd xmm0, xmm1
    ret

monthly_rate:
    call apply_discount
    call daily_rate
    mov rax, 22
    cvtsi2sd xmm1, eax
    mulsd xmm0, xmm1
    roundsd xmm0, xmm0, 2
    cvtsd2si rax, xmm0
    ret

days_in_budget:
    call apply_discount
    call daily_rate
    cvtsi2sd xmm1, rdi
    divsd xmm1, xmm0
    roundsd xmm0, xmm1, 1
    cvtsd2si eax, xmm0
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
