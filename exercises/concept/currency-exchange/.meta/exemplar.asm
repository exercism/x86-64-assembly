default rel

section .rodata
    currencies db "GBP", 0
               db "EUR", 0
               db "JPY", 0
               db "AUD", 0
               db "BRL", 0
               db "CNY", 0
               db "CAD", 0
               db "INR", 0

    percent dq 0.01

section .text

global stringify_currency
stringify_currency:
    mov esi, esi
    lea rdx, [currencies]
    mov eax, dword [rdx + 4*rsi]
    stosd
    ret

global exchange_rate
exchange_rate:
    mov edi, edi
    mov esi, esi
    movsd xmm1, qword [rdx + 8*rdi]
    movsd xmm0, qword [rdx + 8*rsi]
    divsd xmm0, xmm1
    ret

global get_value_of_bills
get_value_of_bills:
    movzx rax, si
    mul rdi
    ret

global get_number_of_bills
get_number_of_bills:
    cvttss2si eax, xmm0
    mov eax, eax
    cqo
    div rdi
    ret

global exchangeable_value
exchangeable_value:
    movzx rdi, dil
    cvtsi2sd xmm2, rdi
    mulsd xmm2, qword [percent]
    mulsd xmm2, xmm1
    addsd xmm1, xmm2
    cvtsd2ss xmm1, xmm1
    divss xmm0, xmm1
    mov rdi, rsi
    call get_number_of_bills
    mul edi
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
