; Everything that comes after a semicolon (;) is a comment

section .text

; the global directive makes a function visible to the test files

; You should implement functions in the .text section
; A skeleton is provided for the first function

extract_higher_bits:
    ; This function has a 16-bit integer as argument
    ; it returns the higher 8-bit value of the argument
    ret

; TODO: define the 'extract_lower_bits' function
; This function takes one 16-bit integer as argument and must return the lower 8-bit value of it

; TODO: define the 'extract_redundant_bits' function
; This function takes one 16-bit integer as argument
; It returns a 8-bit integer with all bits set in both the lower and the higher 8 bits of the argument

; TODO: define the 'set_bits' function
; This function takes one 16-bit integer as argument
; It returns a 8-bit integer with all bits set if they are set in the higher 8 bits of the argument, the others unchanged

; TODO: define the 'rotate_private_key' function
; This function takes one 16-bit integer as argument
; It returns a 16-bit integer with bits of a private key rotated to the left a number of positions equal to the redundant bits

; TODO: define the 'format_private_key' function
; This function takes one 16-bit integer as argument
; It returns a 8-bit integer with the private key fully formatted after rotation

; TODO: define the 'decrypt_message' function
; This function takes one 16-bit integer as argument
; It returns a 16-bit signed integer, of which:
; - The higher 8 bits are the formatted private key.
; - The lower 8 bits are the message with all bits set

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
