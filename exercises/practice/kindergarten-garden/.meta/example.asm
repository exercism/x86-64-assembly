default rel

section .rodata
clover: db "clover", 0
grass: db "grass", 0
radishes: db "radishes", 0
violets: db "violets", 0
comma: db ", ", 0

section .data
plant_array:
dq 0
dq 0
dq clover
dq 0
dq 0
dq 0
dq grass
dq 0
dq 0
dq 0
dq 0
dq 0
dq 0
dq 0
dq 0
dq 0
dq 0
dq radishes
dq 0
dq 0
dq 0
dq violets
dq 0
dq 0
dq 0
dq 0

section .text
global plants

; Outputs the student's plants as a null-terminated string, using a comma and a space as separators.
; rdi - output buffer
; rsi - garden diagram
; rdx - student's name
; r8 - start of garden diagram
; r9 - length of garden diagram, halved
; r10 - plant array
; rbx - offset into garden diagram
; rcx - current plant
plants:
    cld ; each lodsb will increase rsi
    push rbx
    xor rcx, rcx
    mov r8, rsi
    lea r10, [plant_array]

.scan:
    lodsb
    test al, al
    jnz .scan

    mov r9, rsi
    sub r9, r8
    inc r9
    shr r9, 1

    xor rbx, rbx
    mov bl, byte [rdx]
    sub bl, 'A'
    shl bl, 1 ; index into diagram for first plant: 2 * (student[0] - `A`)
    call .output_plant
    call .output_comma

    inc bl ; index into diagram for second plant
    call .output_plant
    call .output_comma

    dec bl
    add rbx, r9 ; index into diagram for third plant
    call .output_plant
    call .output_comma

    inc bl ; index into diagram for fourth plant
    call .output_plant
    pop rbx
    ret

.output_plant:
    mov cl, byte [r8 + rbx]
    sub cl, 'A'
    mov rsi, qword [r10 + 8 * rcx]

.copy_string:
    lodsb
    stosb
    test al, al
    jnz .copy_string

    dec rdi
    ret

.output_comma:
    lea rsi, [comma]
    jmp .copy_string

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
