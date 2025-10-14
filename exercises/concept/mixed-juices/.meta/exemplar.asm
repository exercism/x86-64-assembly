section .text

global time_to_make_juice
global time_to_prepare
global limes_to_cut
global remaining_orders

time_to_make_juice:
    cmp edi, 2
    jl .pure_strawberry_joy
    je .energizer

    cmp edi, 4
    jl .green_garden
    je .tropical_island

    cmp edi, 6
    jl .all_or_nothing
    je .feel_good

    cmp edi, 8
    jl .todays_special

    mov eax, 10
    ret

.pure_strawberry_joy:
    mov eax, 1
    ret

.energizer:
    mov eax, 3
    ret

.green_garden:
    mov eax, 3
    ret

.tropical_island:
    mov eax, 4
    ret

.all_or_nothing:
    mov eax, 5
    ret

.feel_good:
    mov eax, 4
    ret

.todays_special:
    mov eax, 7
    ret

time_to_prepare:
    mov ecx, esi
    mov rdx, rdi
    mov r8d, 0
.loop:
    mov edi, dword [rdx + 4*rcx - 4]
    call time_to_make_juice
    add r8d, eax
    loop .loop
    mov eax, r8d
    ret

limes_to_cut:
    mov eax, 0
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
    sub edi, 6
    jmp .loop

.medium:
    inc eax
    sub edi, 8
    jmp .loop

.large:
    inc eax
    sub edi, 10
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
