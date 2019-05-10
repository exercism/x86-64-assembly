section .text
global leap_year
leap_year:
    ; Check if year is divisible by 4
    mov eax, edi
    cdq
    mov ecx, 4
    idiv ecx
    cmp edx, 0
    jne .or

    ; Check if year is divisible by 100
    mov eax, edi
    cdq
    mov ecx, 100
    idiv ecx
    cmp edx, 0
    jne .return_true

.or:
    ; Check if year is divisible by 400
    mov eax, edi
    cdq
    mov ecx, 400
    idiv ecx
    cmp edx, 0
    jne .return_false

.return_true:
    mov eax, 1
    jmp .return

.return_false:
    mov eax, 0

.return:
    ret
