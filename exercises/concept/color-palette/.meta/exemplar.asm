default rel

section .rodata
    global RED
    global GREEN
    global BLUE
    RED dd 0xFF000000
    GREEN dd 0x00FF0000
    BLUE dd 0x0000FF00

section .data
    global base_color
    base_color dd 0xFFFFFF00
    combined_color_address dq 0
    secondary_color dd 0

section .text

global get_color_value
global add_base_color
global make_color_combination

extern combining_function

get_color_value:
    mov eax, dword [rdi]
    ret

add_base_color:
    call get_color_value
    lea rdi, [base_color]
    mov dword [rdi], eax
    ret

make_color_combination:
    mov qword [combined_color_address], rdi
    mov rdi, rsi
    call get_color_value
    mov dword [secondary_color], eax
    mov edi, dword [base_color]
    mov esi, dword [secondary_color]
    call combining_function
    mov rdi, qword [combined_color_address]
    mov dword [rdi], eax
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
