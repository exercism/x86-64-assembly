PAY_PER_BOX equ 5
PAY_PER_TRUCK_TRIP equ 220

section .text

global get_box_weight
global max_number_of_boxes
global items_to_be_moved
global calculate_payment

get_box_weight:
    movzx eax, dx
    movzx ecx, cx
    mul ecx
    mov ecx, eax
    movzx eax, di
    movzx esi, si
    mul esi
    add eax, 500
    add eax, ecx
    ret

max_number_of_boxes:
    mov ax, 300
    div dil
    ret

items_to_be_moved:
    sub edi, esi
    mov eax, edi
    ret

calculate_payment:
    mov esi, esi
    imul rax, rsi, PAY_PER_BOX
    mov edx, edx
    imul rdx, rdx, PAY_PER_TRUCK_TRIP
    add rax, rdx
    mov edx, ecx
    imul rdx, r8
    sub rax, rdx
    sub rax, rdi
    movzx r9, r9b
    inc r9
    cqo
    idiv r9
    add rax, rdx
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
