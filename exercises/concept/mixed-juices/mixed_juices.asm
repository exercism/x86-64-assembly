; Everything that comes after a semicolon (;) is a comment

section .text

; You should implement functions in the .text section
; A skeleton is provided for the first function

; the global directive makes a function visible to the test files
global time_to_make_juice
time_to_make_juice:
    ; This function has one argument, the ID for a juice as a 32-bit number
    ; It returns the time to prepare this juice, as a 32-bit number
    ret

; TODO: define the 'time_to_prepare' function
; This function has two arguments:
; - An array with the IDs for ordered juices, each ID a 32-bit number
; - The number of ordered juices, also a 32-bit number.
; It returns the total time to prepare all ordered juices, as a 32-bit number

; TODO: define the 'limes_to_cut' function
; This function takes three arguments:
; - The number of wedges needed, as a 32-bit number.
; - An array with the current supply of limes, each represented by a 8-bit number.
; - The number of limes in the supply, as a 32-bit number.
; It returns the number of limes that need to be cut, as a 32-bit number

; TODO: define the 'remaining_orders' function
; This function takes two arguments:
; - The time left in the shift, as a 32-bit number.
; - An array  with the IDs for ordered juices still not prepared, each ID a 32-bit number.
; It returns the number of juices made before the shift ends, as a 32-bit number.
; You may consider that:
; - The array is never empty.
; - The time left in the shift at the beginning is always greater than 0.
; - There are more orders in the array than that which can be prepared before the shift ends.

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
