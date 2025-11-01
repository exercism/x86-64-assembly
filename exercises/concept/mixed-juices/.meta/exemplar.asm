default rel

SMALL_WEDGES equ 6
MEDIUM_WEDGES equ 8
LARGE_WEDGES equ 10

section .rodata
    juice_time dd 1, 3, 3, 4, 5, 4, 7, 10

section .text

global time_to_make_juice
global time_to_prepare
global limes_to_cut
global remaining_orders

time_to_make_juice:
    lea rax, [juice_time]
    mov dword eax, [rax + 4*rdi - 4]
    ret

time_to_prepare:
    mov ecx, esi
    mov rdx, rdi
    mov r8d, 0 ; accumulator
.loop:
    mov edi, dword [rdx + 4*rcx - 4]
    call time_to_make_juice
    add r8d, eax
    loop .loop

    mov eax, r8d
    ret

limes_to_cut:
    mov eax, 0 ; counter for limes
.loop:
    cmp edi, 0
    jle .exit

    cmp edx, 0
    je .exit

    dec edx
    mov rcx, rsi
    inc rsi

    cmp byte [rcx], 'S'
    je .small

    cmp byte [rcx], 'M'
    je .medium

    cmp byte [rcx], 'L'
    je .large

    jmp .loop

.small:
    inc eax
    sub edi, SMALL_WEDGES
    jmp .loop

.medium:
    inc eax
    sub edi, MEDIUM_WEDGES
    jmp .loop

.large:
    inc eax
    sub edi, LARGE_WEDGES
    jmp .loop

.exit:
    ret

remaining_orders:
    mov edx, 0
    mov ecx, edi
.loop:
    mov edi, dword [rsi]
    add rsi, 4
    inc edx

    call time_to_make_juice

    sub ecx, eax
    cmp ecx, 0
    jg .loop

    mov eax, edx
    ret


%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
