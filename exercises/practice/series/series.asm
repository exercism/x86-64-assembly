EMPTY_SERIES equ -1
ZERO_LENGTH equ -2
NEGATIVE_LENGTH equ -3
EXCESSIVE_LENGTH equ -4

section .text
global slices

slices:
	; Provide your implementation here
	ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
