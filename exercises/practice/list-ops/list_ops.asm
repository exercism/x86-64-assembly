section .text
global append
append:
    ; Provide your implementation here
    ret

global filter
filter:
    ; Provide your implementation here
    ret

global map
map:
    ; Provide your implementation here
    ret

global foldl
foldl:
    ; Provide your implementation here
    ret

global foldr
foldr:
    ; Provide your implementation here
    ret

global reverse
reverse:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
