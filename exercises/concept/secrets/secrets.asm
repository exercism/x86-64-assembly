; Everything that comes after a semicolon (;) is a comment

section .text

; You should implement functions in the .text section
; A skeleton is provided for the first function

; the global directive makes a function visible to the test files
global extract_higher_bits
extract_higher_bits:
    ; This function has a 16-bit integer as argument
    ; it returns the higher 8-bit value of the argument
    ret

; TODO: define the 'extract_lower_bits' function
; This function takes one 16-bit integer as argument and must return the lower 8-bit value of it

; TODO: define the 'extract_redundant_bits' function
; This function takes one 16-bit integer as argument
; It returns a 8-bit integer with all bits set in both the lower and the higher 8 bits of the argument

; TODO: define the 'set_message_bits' function
; This function takes one 16-bit integer as argument
; It returns a 8-bit integer with all bits set if they are set in the higher 8 bits of the argument, the others unchanged

; TODO: define the 'rotate_private_key' function
; This function takes one 16-bit integer as argument
; It returns a 16-bit integer with bits of a private key rotated to the left a number of positions equal to the redundant bits

; TODO: define the 'format_private_key' function
; This function takes one 16-bit integer as argument
; It returns a 8-bit integer with the private key fully formatted after rotation
; To format a rotated private key, you must:
; - Isolate the lowest 8-bit portion of the rotated private key, which is the base value.
; - Isolate the highest 8-bit portion of the rotated private key, which is a mask to be applied to the base value.
; - Flip set bits in the base value that are also set in the mask.
; - Flip all bits in the result.

; TODO: define the 'decrypt_message' function
; This function takes one 16-bit integer as argument
; It returns a 16-bit integer, of which:
; - The higher 8 bits are the formatted private key.
; - The lower 8 bits are the message with all bits set

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
