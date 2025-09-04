; Sets are implemented as a simple hash table
; Since the inputs are int8_t, their unsigned representation varies between 0 and 255
; So, using bitsets, 4 64-bit integers are enough to represent all values

; Using bitsets have other advantages besides low memory usage:
; There's a mapping between set operations that return another set and bitset operations:
; UNION -> OR
; INTERSECTION -> AND
; DIFFERENCE -> NAND
;
; Also, set operations that add or search for elements are simple BTS or BT instructions
; And operations such as disjoint, subset or equal are also straightforward applications of bitset instructions
;
; To store sets, there's a set_arr which can hold 1020 uin64_t, enough for 255 sets
; And to keep track of used indexes in the array, there's a used_sets array with 1020 booleans
;
; If we were to add a length function, this would be just a sum of 4 POPCNT

default rel

section .bss
    set_arr resq 1020
    used_sets resb 255

section .text

global create_set
global set_empty
global set_contains
global set_subset
global set_disjoint
global set_equal
global set_add
global set_intersection
global set_difference
global set_union
global delete_set

%macro find_empty_set 1
    lea %1, [used_sets]
    mov r11, -1
%%find_index:
    inc r11

    cmp byte [%1 + r11], 0
    jne %%find_index

    mov byte [%1 + r11], 1

    shl r11, 5
    lea %1, [set_arr]
    add %1, r11
%endmacro

%macro id_to_index 2
    lea %1, [set_arr]
    shl %2, 5
    add %1, %2
%endmacro

%macro index_to_id 2
    lea %1, [used_sets]
    shr %2, 5
    add %1, %2
%endmacro

create_set:
    ; RDI - num of elements in input array
    ; RSI - input array of int8_t
    ; result is a size_t (uint64_t) which uniquely identifies the set, in RAX

    find_empty_set r10

    xor rax, rax
    xor rcx, rcx
    mov r8, -1
.insert_loop:
    inc r8

    cmp r8, rdi
    jge .end_insert

    lodsb

    mov cl, al
    and cl, 63 ; number % 64 is the index for the bit to be set
    shr al, 6 ; number / 64 is the index for the integer to be set

    lea r11, [r10 + 8*rax]
    bts qword [r11], rcx ; bts sets the bit

    jmp .insert_loop

.end_insert:
    mov rax, r10
    lea r10, [set_arr]
    sub rax, r10
    shr rax, 5 ; identifier is the index of the set in the sets array

    ret

set_empty:
    ; RDI - identifier for the set
    ; return is a boolean in RAX

    id_to_index r10, rdi

    mov rax, 1
    mov rcx, 4
.loop:
    cmp qword [r10 + 8*rcx - 8], 0
    sete dl
    and al, dl ; remains true if all integers are NULL
    loop .loop

    ret

set_contains:
    ; RDI - identifier for the set
    ; RSI - element (as a int8_t) to be searched
    ; return is a boolean in rax

    id_to_index r10, rdi

    xor rax, rax
    xor rcx, rcx

    mov al, sil
    mov cl, al
    and cl, 63 ; number % 64 is the index for the bit to be set
    shr al, 6 ; number / 64 is the index for the integer to be set

    lea r11, [r10 + 8*rax]
    bt qword [r11], rcx ; checks if bit is set, stores result in CF
    setc al ; if CF is set, returns true, false otherwise

    ret

set_subset:
    ; RDI - identifier for first set
    ; RSI - identifier for second set
    ; return is a boolean in RAX

    id_to_index r10, rdi
    id_to_index r11, rsi

    mov rax, 1
    mov rcx, 4
.loop:
    mov r8, qword [r10 + 8*rcx - 8]
    and r8, qword [r11 + 8*rcx - 8]

    cmp r8, qword [r10 + 8*rcx - 8]
    sete dl ; true if all bits in first number are also set in second number
    and al, dl ; remains true if all integers are subset
    loop .loop

    ret

set_disjoint:
    ; RDI - identifier for first set
    ; RSI - identifier for second set
    ; return is a boolean in RAX

    id_to_index r10, rdi
    id_to_index r11, rsi

    mov rax, 1
    mov rcx, 4
.loop:
    mov r8, qword [r10 + 8*rcx - 8]
    and r8, qword [r11 + 8*rcx - 8]

    cmp r8, 0
    sete dl ; true if all bits in first number are cleared in second number
    and al, dl ; remains true if all integers are disjoint
    loop .loop

    ret

set_equal:
    ; RDI - identifier for first set
    ; RSI - identifier for second set
    ; return is a boolean in RAX

    id_to_index r10, rdi
    id_to_index r11, rsi

    mov rax, 1
    mov rcx, 4
.loop:
    mov r8, qword [r10 + 8*rcx - 8]

    cmp r8, qword [r11 + 8*rcx - 8]
    sete dl ; true if first number is equal to second number
    and al, dl ; remains true if all integers are equal
    loop .loop

    ret

set_add:
    ; RDI - identifier for the set
    ; RSI - element (as a int8_t) to be added
    ; return is void

    id_to_index r10, rdi

    xor rax, rax
    xor rcx, rcx

    mov al, sil
    mov cl, al
    and cl, 63 ; number % 64 is the index for the bit to be set
    shr al, 6 ; number / 64 is the index for the integer to be set

    lea r11, [r10 + 8*rax]
    bts qword [r11], rcx ; bts sets bit in the index

    ret

set_intersection:
    ; RDI - id for first set
    ; RSI - id for second set
    ; return is id for the intersection set in RAX

    find_empty_set r9

    id_to_index r10, rdi
    id_to_index r11, rsi

    mov rcx, 4
.loop:
    mov r8, qword [r10 + 8*rcx - 8]
    and r8, qword [r11 + 8*rcx - 8] ; AND corresponds to intersection
    mov qword [r9 + 8*rcx - 8], r8
    loop .loop

    mov rax, r9
    lea r9, [set_arr]
    sub rax, r9
    shr rax, 5

    ret

set_difference:
    ; RDI - id for first set
    ; RSI - id for second set
    ; return is id for the intersection set in RAX

    find_empty_set r9

    id_to_index r10, rdi
    id_to_index r11, rsi

    mov rcx, 4
.loop:
    mov r8, qword [r11 + 8*rcx - 8]
    not r8
    and r8, qword [r10 + 8*rcx - 8] ; NAND corresponds to difference
    mov qword [r9 + 8*rcx - 8], r8
    loop .loop

    mov rax, r9
    lea r9, [set_arr]
    sub rax, r9
    shr rax, 5

    ret

set_union:
    ; RDI - id for first set
    ; RSI - id for second set
    ; return is id for the intersection set in RAX

    find_empty_set r9

    id_to_index r10, rdi
    id_to_index r11, rsi

    mov rcx, 4
.loop:
    mov r8, qword [r10 + 8*rcx - 8]
    or r8, qword [r11 + 8*rcx - 8] ; OR corresponds to difference
    mov qword [r9 + 8*rcx - 8], r8
    loop .loop

    mov rax, r9
    lea r9, [set_arr]
    sub rax, r9
    shr rax, 5

    ret

delete_set:
    ; RDI - set id
    ; return is void

    id_to_index r10, rdi

    ; clears all bits in set
%rep 4
    %assign i 0
    mov qword [r10 + 8*i], 0
    %assign i i+1
%endrep

    index_to_id r10, rdi
    mov byte [r10], 0

    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
