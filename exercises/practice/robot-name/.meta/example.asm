default rel

MAX_NUM_OF_NAMES equ 676_000

section .bss
    hash_table resb MAX_NUM_OF_NAMES

section .data
    big_mersenne dq 18446744073709551615

section .text

global create_name
global reset_name
global release_names

%macro get_random_between 2
    rdtsc
    xor rax, rdx

    lea rdx, [big_mersenne]
    xor rax, qword [rdx]

    xor r8, r8
    mov r8, %2
    sub r8, %1 ; max - min
    inc r8 ; 1 + max - min

    xor rdx, rdx
    div r8

    mov rax, rdx ; random() % (1 + max - min)
    add rax, %1 ; min + (random() % (1 + max - min))
%endmacro

%macro hash_name 0
    xor rax, rax

    mov al, byte [rdi]
    sub al, 'A' ; 0 to 25

    xor r9, r9

    mov r9b, byte [rdi + 1]
    sub r9b, 'A' ; 0 to 25
    imul r9, r9, 26 ; 0, 26, 52, etc
    add rax, r9

    xor r9, r9

    mov r9b, byte [rdi + 2]
    sub r9b, '0'
    imul r9, r9, (26*26) ; 0,
    add rax, r9

    xor r9, r9

    mov r9b, byte [rdi + 3]
    sub r9b, '0'
    imul r9, r9, (26*26*10)
    add rax, r9

    xor r9, r9

    mov r9b, byte [rdi + 4]
    sub r9b, '0'
    imul r9, r9, (26*26*10*10)
    add rax, r9
%endmacro

reset_name:
    ; rdi - output char buffer, where the name will be reset and another written
create_name:
    ; rdi - output char buffer, where the name will be written

    lea r11, [hash_table]
    mov r10, rdi
.generate:
    get_random_between 'A', 'Z'
    stosb
    get_random_between 'A', 'Z'
    stosb

    get_random_between '0', '9'
    stosb
    get_random_between '0', '9'
    stosb
    get_random_between '0', '9'
    stosb

    mov rdi, r10
    hash_name

    cmp byte [r11 + rax], 0
    jne .generate

    mov byte [r11 + rax], 1 ; set the value in hash_table
    mov byte [rdi + 5], 0 ; append NULL
    ret

release_names:
    lea r11, [hash_table]
    mov rcx, MAX_NUM_OF_NAMES
.release_loop:
    mov byte [r11 + rcx - 1], 0
    loop .release_loop

    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
