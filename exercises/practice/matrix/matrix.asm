section .text
global row
global column

row:
	; Provide your implementation here
	ret

column:
	; Provide your implementation here
	ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
