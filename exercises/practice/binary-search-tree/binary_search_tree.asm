section .text

global build_tree
global sorted_data
global delete_tree

build_tree:
    ; Provide your implementation here
    ret

sorted_data:
    ; Provide your implementation here
    ret

delete_tree:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
