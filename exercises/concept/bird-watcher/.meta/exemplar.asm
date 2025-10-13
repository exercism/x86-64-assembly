default rel

section .data
    last_week db 0, 2, 5, 3, 7, 8, 4, 0

section .bss
    current_week resb 8
    current_count resq 1

section .text

global last_week_counts
global current_week_counts
global save_count
global today_count
global update_today_count
global update_week_counts

last_week_counts:
    mov rax, qword [last_week]
    ret

current_week_counts:
    mov rax, qword [current_week]
    mov rdx, qword [current_count]
    ret

save_count:
    cmp qword [current_count], 7
    jl .insert_in_week

    mov rax, qword [current_week]
    mov qword [last_week], rax
    mov qword [current_week], 0
    mov qword [current_count], 0

.insert_in_week:
    mov rcx, qword [current_count]
    lea rdx, [current_week]
    mov byte [rdx + rcx], dil
    inc qword [current_count]
    ret

today_count:
    mov rcx, qword [current_count]
    dec rcx
    lea rsi, [current_week]
    mov al, byte [rsi + rcx]
    ret

update_today_count:
    mov rcx, qword [current_count]
    dec rcx
    lea rsi, [current_week]
    add byte [rsi + rcx], dil
    ret

update_week_counts:
    mov rsi, qword [current_week]
    mov qword [last_week], rsi
    mov qword [current_week], rdi
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
