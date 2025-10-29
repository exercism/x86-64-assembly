; Everything that comes after a semicolon (;) is a comment

; Assembler-time constants may be defined using 'equ'

section .text

; You should implement functions in the .text section
; A skeleton is provided for the first function

; the global directive makes a function visible to the test files
global expected_minutes_in_oven
expected_minutes_in_oven:
    ; This function has no arguments
    ; and must return a number
    ret

global remaining_minutes_in_oven
; TODO: define the 'remaining_minutes_in_oven' function
; This function takes one number as argument and must return a number

global preparation_time_in_minutes
; TODO: define the 'preparation_time_in_minutes' function
; This function takes one number as argument and must return a number

; TODO: define the 'elapsed_time_in_minutes' function
; This function takes two numbers as arguments and must return a number

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
