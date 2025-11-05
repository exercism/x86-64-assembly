; Everything that comes after a semicolon (;) is a comment

section .text

; You should implement functions in the .text section
; A skeleton is provided for the first function

; the global directive makes a function visible to the test files
global create_item_entry
create_item_entry:
    ; TODO: implement the 'create_item_entry' function.
    ; This function may take any number of parameters, of which the first 6 are:
    ;
    ; 1. The address for a location in memory where the item should be stored.
    ; 2. The ID for the item, as a 64-bit unsigned integer.
    ; 3. The address for a string with the item's description.
    ; 4. The day it was found, as a 64-bit unsigned integer.
    ; 5. The month it was found, as a 64-bit unsigned integer.
    ; 6. The number of categories for the item, as a 64-bit unsigned integer.
    ; Each subsequent parameter is the address for a string with one of the categories.
    ;
    ; Values should be stored in the provided memory location in the same order of the arguments:
    ; ID, description, day, month, number of categories, and each category in order.
    ;
    ; This function has no return value.
    ret

; TODO: implement the 'create_monthly_list' function.
; This function takes as parameters:
;
; 1. The capacity of the array in bytes, as a 64-bit unsigned integer.
; 2. An allocator function.
;
; The allocator function should be called with the capacity as argument.
; It returns the address of the allocated space.
; This space has undefined value and should be cleared.
;
; The 'create_month_list' function should return the address for the space allocated with the allocator function.


; TODO: implement the 'insert_found_item' function.
; This function takes as parameters:
;
; 1. The address for a space in memory where the monthly list is located.
; 2. The current number of entries already stored in the list, as a 64-bit unsigned integer.
; 3. A new entry to be added to the list.
;
; You may consider that the new entry always fits into the list.
; All entries in the list take up 120 bytes in space.
; This function has no return value.


; TODO: implement the 'print_item' function.
; This function takes as parameters:
; 1. The address for a buffer where an introductory ASCII NUL-terminated string may be stored.
; 2. The address for a space in memory where the monthly list is located.
; 3. The index of the entry in the array for the item that should be printed, as a 64-bit unsigned integer.
; 4. A printing function.
;
; This function must call the printing function with the following arguments:
;
; 1. The address to a memory location where the introductory string is stored; or `0` (as a 64-bit integer) if no string is passed.
; 2. The index of the entry in the array for the item that should be printed, as a 64-bit unsigned integer.
; 3. The ID for the item, as a 64-bit unsigned integer.
; 4. The address for a string with the item's description.
; 5. The day the item was found, as a 64-bit unsigned integer.
; 6. The month the item was found, as a 64-bit unsigned integer.
; 7. The number of categories for the item, as a 64-bit unsigned integer.
; 8. The address of the first category string.
;
; The introductory string is optional.
; If it is used in the printing function, this string must be NUL-terminated (ending in `0`) and have at most 50 characters, already considering the NUL terminator.
; Otherwise, the value `0` should be passed to the printing function instead.
;
; This function has no return value.


%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
