; Everything that comes after a semicolon (;) is a comment.

section .text

; You should implement functions in the .text section.
; A skeleton is provided for the first function.

; The global directive makes a function visible to the test files.
global daily_rate

daily_rate:
    ; This function takes an hourly_rate, as a 64-bit floating-point number.
    ; It returns the daily rate, also as a 64-bit floating-point number.
    ; A day has 8 billable hours.
    ret

; TODO: define the 'apply_discount' function.
; It takes as parameters a price and a discount in percent, both as 64-bit floating-point number.
; It returns the price with discount applied, as a 64-bit floating-point number.

; TODO: define the 'monthly_rate' function.
; It takes as parameters an hourly_rate and a discount in percent, both as a 64-bit floating-point number.
; It returns the discounted monthly rate, as a 64-bit integer, rounded up.

; TODO: define the 'days_in_budget' function.
; It takes as parameters:
; 1. A budget as a 64-bit unsigned integer.
; 2. An hourly_rate, as a 64-bit floating-point number.
; 3. A discount in percent, as a 64-bit floating-point number.
; It returns the number of complete days of work the budget covers, as a 32-bit unsigned integer, rounded down.
; A month has 22 billable days.

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
