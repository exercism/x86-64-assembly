section .text

global create
global move

create:
    ; edi - int32_t representing x coordinate
    ; esi - int32_t representing y coordinate
    ; edx - int32_t representing direction
    ; return is a struct of 3 int32_t

    ; Given that the return is formed of 3 int32_t
    ; the first two are passed in rax,
    ; being the first in the lower 32 bits
    ; and the second in the upper 32 bits
    ; the third is passed in rdx
    ; where it's already when the function is called

    mov eax, edi ; passing x coordinate
    mov ecx, esi ; passing y coordinate
    shl rcx, 32 ; shifting left 32 bit to accumulate in rax
    or rax, rcx ; accumulating, rax now holds x and y coordinate, in reverse order
    ; edx already holds the third argument by calling convention,
    ; so nothing else needs to be done

    ret

move:
    ; rdi - pointer to robot
    ; rsi - input string
    ; return is void

.main_loop:
    lodsb

    cmp al, 'R'
    je .turn_right

    cmp al, 'L'
    je .turn_left

    cmp al, 'A'
    je .advance

    cmp al, 0
    jne .main_loop

    ret

.turn_right:
    inc dword [rdi + 8] ; each turn to right moves to next value in enum
    and dword [rdi + 8], 3 ; modulus 4, to wrap around inside the enum
    jmp .main_loop

.turn_left:
    dec dword [rdi + 8] ; each turn to left moves to previous value in enum
    and dword [rdi + 8], 3 ; modulus 4, to wrap around inside the enum
    jmp .main_loop

.advance:
    cmp dword [rdi + 8], 1
    je .increase_x ; right increases x
    jl .increase_y ; north increases y

    cmp dword [rdi + 8], 3
    je .decrease_x ; left decreases x
    jl .decrease_y ; south decreases y

.increase_y:
    inc dword [rdi + 4]
    jmp .main_loop
.increase_x:
    inc dword [rdi]
    jmp .main_loop
.decrease_y:
    dec dword [rdi + 4]
    jmp .main_loop
.decrease_x:
    dec dword [rdi]
    jmp .main_loop


%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
