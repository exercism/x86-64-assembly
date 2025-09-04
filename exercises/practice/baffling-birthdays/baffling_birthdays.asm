section .text
global shared_birthday
global random_birthdates
global estimated_probability_of_shared_birthday

shared_birthday:
    ; Provide your implementation here
    ret

random_birthdates:
    ; Provide your implementation here
    ret

estimated_probability_of_shared_birthday:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
