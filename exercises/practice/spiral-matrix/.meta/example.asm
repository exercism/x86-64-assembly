section .text
global spiral_matrix

%macro hash_cell 0
    mov rcx, r8
    imul rcx, rsi
    add rcx, r9
%endmacro

%macro check_right_square 0
    xor rdx, rdx
    inc r9

    cmp r9, rsi
    jge %%end

    hash_cell

    cmp dword [rdi + 4*rcx], 0
    jne %%end

    mov rdx, 1
%%end:
    dec r9
%endmacro

%macro check_down_square 0
    xor rdx, rdx
    inc r8

    cmp r8, rsi
    jge %%end

    hash_cell

    cmp dword [rdi + 4*rcx], 0
    jne %%end

    mov rdx, 1
%%end:
    dec r8
%endmacro

%macro check_left_square 0
    xor rdx, rdx
    dec r9

    cmp r9, 0
    jl %%end

    hash_cell

    cmp dword [rdi + 4*rcx], 0
    jne %%end

    mov rdx, 1
%%end:
    inc r9
%endmacro

%macro check_up_square 0
    xor rdx, rdx
    dec r8

    cmp r8, 0
    jl %%end

    hash_cell

    cmp dword [rdi + 4*rcx], 0
    jne %%end

    mov rdx, 1
%%end:
    inc r8
%endmacro

spiral_matrix:
    ; rdi - output buffer is an array of uint32_t
    ; rsi - n for the matrix, as a uint64_t
    ; return is the size of output buffer, as a uint64_t in rax

    ; Algorithm is a loop with a simple dispatch that keeps track of array bounds
    ;
    ; Unvisited cells are tracked by a NULL value.
    ; In order to do that, output array is cleared at the beginning.
    ;
    ; There's a macro which hashes abstract row and col positions from a two-dimensional array
    ; to corresponding offset in a unidimensional array
    ;
    ; This is done to reuse code I've already written for this exercise for the C++ track
    ;
    ; In every dispatch, there's a check for valid cell (empty cell within array bounds).
    ; The corresponding boolean is stored in RDX, its value is used to update row, col and direction flag

    mov rax, rsi
    imul rax, rax ; size of the output array

    xor rcx, rcx ; index
.clear_output_array:
    cmp rcx, rax
    jge .end_clearing

    mov dword [rdi + 4*rcx], 0
    inc rcx
    jmp .clear_output_array

.end_clearing:
    xor r11, r11 ; direction flag
                 ; 0 -> RIGHT
                 ; 1 -> DOWN
                 ; 2 -> LEFT
                 ; 3 -> UP

    xor r8, r8 ; row
    xor r9, r9 ; col
    mov r10, 1 ; value
.fill:
    cmp r10, rax
    jg .end_spiral_matrix ; loops until reaches end

    hash_cell
    mov dword [rdi + 4*rcx], r10d ; inserts value into correct position

    inc r10 ; moves to next value

    ; transition state for the problem according to current direction

    cmp r11, 1
    je .move_down
    jl .move_right

    cmp r11, 3
    je .move_up
    jl .move_left

.move_right:
    check_right_square

    add r9, rdx ; if cell is valid, col is increased by 1
                ; it stays the same otherwise

    inc rdx ; if cell is valid, RDX becomes 2
    ; otherwise it becomes 1

    and rdx, 1 ; takes modulus 2,
               ; so a valid cell would become 0
               ; and a invalid one would remain 1

    add r11, rdx ; if invalid cell, direction moves to next value (DOWN)
                 ; it stays the same otherwise

    add r8, rdx ; if direction changed to DOWN, row is increased by 1
                ; it stays the same otherwise

    jmp .fill

.move_down:
    check_down_square

    add r8, rdx ; if cell is valid, row is increased by 1
                ; it stays the same otherwise

    inc rdx ; if cell is valid, RDX becomes 2
    ; otherwise it becomes 1

    and rdx, 1 ; takes modulus 2,
               ; so a valid cell would become 0
               ; and a invalid one would remain 1

    add r11, rdx ; if invalid cell, direction moves to next value (LEFT)
                 ; it stays the same otherwise

    sub r9, rdx ; if direction changed to LEFT, col is decreased by 1
                ; it stays the same otherwise

    jmp .fill

.move_left:
    check_left_square

    sub r9, rdx ; if cell is valid, col is reduced by 1
                ; it stays the same otherwise

    inc rdx ; if cell is valid, RDX becomes 2
    ; otherwise it becomes 1

    and rdx, 1 ; takes modulus 2,
               ; so a valid cell would become 0
               ; and a invalid one would remain 1

    add r11, rdx ; if invalid cell, direction moves to next value (UP)
                 ; it stays the same otherwise

    sub r8, rdx ; if direction changed to UP, row is decreased by 1
                ; it stays the same otherwise

    jmp .fill

.move_up:
    check_up_square

    sub r8, rdx ; if cell is valid, row is reduced by 1
                ; it stays the same otherwise

    inc rdx ; if cell is valid, RDX becomes 2
    ; otherwise it becomes 1

    and rdx, 1 ; takes modulus 2,
               ; so a valid cell would become 0
               ; and a invalid one would remain 1

    add r11, rdx ; if invalid cell, direction moves to next value (RIGHT)
                 ; it stays the same otherwise

    and r11, 3 ; next value in direction flag would be 4,
               ; taking AND 3 maintains enum in modulus 4

    add r9, rdx ; if direction changed to RIGHT, col is increased by 1
                ; it stays the same otherwise

    jmp .fill

.end_spiral_matrix:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
