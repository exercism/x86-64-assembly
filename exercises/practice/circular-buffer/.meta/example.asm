default rel

section .bss
    buffer resd 100
    buffer_size resq 1

    reading_index resq 1
    writing_index resq 1
    num_elems resq 1

section .text

global create_buffer
global read_buffer
global write_buffer
global clear_buffer
global overwrite_buffer
global delete_buffer

; macro to increase the index modulus buffer capacity
%macro update_index 1
    xor rdx, rdx
    inc %1
    cmp %1, qword [buffer_size]
    cmove %1, rdx ; if updated index is now equal to buffer capacity, it becomes 0
%endmacro

create_buffer:
    ; rdi - size_t (uint64_t) with buffer size
    ; return is void

    mov qword [buffer_size], rdi ; stores capacity in buffer_size
    ret

read_buffer:
    ; rdi - pointer to output (int32_t)
    ; return is a boolean indicating success in rax

    ; Instead of actually eliminating the element from the buffer
    ; The reading index is updated, so that the element is essentially disregarded

    cmp qword [num_elems], 1
    jl error ; if there's no element, function returns false

    ; num of element is decreased
    dec qword [num_elems]

    mov r8, qword [reading_index]
    lea r9, [buffer]

    mov r10d, dword [r9 + 4*r8]
    mov dword [rdi], r10d ; copies the element in the reading index into ouput

    update_index r8
    mov qword [reading_index], r8 ; updates reading_index

    mov rax, 1 ; flags success
    ret

write_buffer:
    ; edi - int32_t element to add to buffer
    ; return is a boolean indicating success in rax

    mov r8, qword [num_elems]
    cmp r8, qword [buffer_size]
    je error ; if buffer is full, function returns false
    ; otherwise, success is flagged and execution fallthroughs to make_write
    ; which marks a possible common path between write_buffer and overwrite_buffer

    mov rax, 1  ; flags success

make_write:
    inc qword [num_elems]

    mov r8, qword [writing_index]
    lea r9, [buffer]
    mov dword [r9 + 4*r8], edi ; moves element into the buffer at writing_index

    update_index r8
    mov qword [writing_index], r8 ; updates writing_index

    ret

overwrite_buffer:
    ; edi - int32_t element to add to buffer
    ; return is void

    mov r8, qword [num_elems]
    cmp r8, qword [buffer_size]
    jne make_write ; if buffer is not full, overwrite_buffer shares a common path with write_buffer
    ; otherwise, overwrite_buffer mutates element at reading_index, without changing size of the buffer

    mov r8, qword [reading_index]
    lea r9, [buffer]
    mov dword [r9 + 4*r8], edi ; copies element into the buffer at reading_index

    update_index r8
    mov qword [reading_index], r8 ; updates reading_index

    ret

delete_buffer:
    ; no arguments
    ; return is void

    ; Elements are not eliminated, but disregarded

    mov qword [buffer_size], 0

    ; execution fallthroughs to clear_buffer
clear_buffer:
    ; no arguments
    ; return is void

    ; Elements are not eliminated, but disregarded
    ; buffer size is maintained

    mov qword [reading_index], 0
    mov qword [writing_index], 0
    mov qword [num_elems], 0

    ret

error:
    xor rax, rax
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
