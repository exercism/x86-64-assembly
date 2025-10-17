; Everything that comes after a semicolon (;) is a comment.

section .text

; the global directive makes a function visible to the test files.

; You should implement functions in the .text section.
; A skeleton is provided for the first function.

global front_door_response

front_door_response:
    ; This function takes the address in memory for a line of the poem as an argument.
    ; It returns the first letter of that line, as a ASCII-encoded character.
    ret

; TODO: define the 'front_door_password' function.
; This function takes as argument the address in memory for a string containing the combined letters you found in task 1.
; It must modify this string in-place, making it correctly capitalized.
; The function has no return value.

; TODO: define the 'back_door_response' function.
; This function takes as argument the address in memory for a line of the poem.
; It returns the last letter of that line that is not a whitespace character, as a ASCII-encoded character.

; TODO: define the 'back_door_password' function
; This function takes as arguments, in this order:
; 1. The address in memory for a buffer where the resulting string will be stored.
; 2. The address in memory for a string containing the combined letters you found in task 3.
; It should store the polite version of the capitalized password in the buffer.
; A polite version is correctly capitalized and has ", please." added at the end.
; The function has no return value.

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
