PRIVATE_KEY equ 0b1011_0011_0011_1100

section .text

global extract_higher_bits
global extract_lower_bits
global extract_redundant_bits
global set_message_bits
global rotate_private_key
global format_private_key
global decrypt_message

extract_higher_bits:
    shr di, 8
    mov al, dil
    ret

extract_lower_bits:
    mov al, dil
    ret

extract_redundant_bits:
    mov si, di
    call extract_higher_bits
    and al, sil
    ret

set_message_bits:
    mov si, di
    call extract_higher_bits
    or al, sil
    ret

rotate_private_key:
    mov r8w, di
    call extract_redundant_bits
    movzx ax, al
    popcnt cx, ax
    mov ax, PRIVATE_KEY
    rol ax, cl
    ret

format_private_key:
    call rotate_private_key
    mov r8w, ax
    mov di, ax
    call extract_higher_bits
    xor al, r8b
    not al
    ret

decrypt_message:
    mov r9w, di
    call format_private_key
    shl ax, 8
    mov di, r9w
    mov r9w, ax
    call set_message_bits
    movzx ax, al
    or ax, r9w
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
