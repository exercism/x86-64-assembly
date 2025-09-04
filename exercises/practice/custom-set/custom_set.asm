default rel

section .bss

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

create_set:
    ; Provide your implementation here
    ret

set_empty:
    ; Provide your implementation here
    ret

set_contains:
    ; Provide your implementation here
    ret

set_subset:
    ; Provide your implementation here
    ret

set_disjoint:
    ; Provide your implementation here
    ret

set_equal:
    ; Provide your implementation here
    ret

set_add:
    ; Provide your implementation here
    ret

set_intersection:
    ; Provide your implementation here
    ret

set_difference:
    ; Provide your implementation here
    ret

set_union:
    ; Provide your implementation here
    ret

delete_set:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
