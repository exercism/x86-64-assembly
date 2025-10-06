; Everything that comes after a semicolon (;) is a comment

section .text

; the global directive makes a function visible to the test files

global get_box_weight
global max_number_of_boxes
global items_to_be_moved
global calculate_payment

; You should implement functions in the .text section
; A skeleton is provided for the first function

get_box_weight:
    ; This function takes the following parameters:
    ; 1 - The number of items for the first product in the box;
    ; 2 - The weight of each item of the first product, in grams;
    ; 3 - The number of items for the second product in the box;
    ; 4 - The weight of each item of the second product, in grams.
    ; The function must return the total weight of a box, in grams.
    ret

; TODO: define the 'max_number_of_boxes' function
; This function takes the height of the box, in centimeters, as parameter
; It must return how many boxes can be stacked vertically

; TODO: define the 'items_to_be_moved' function
; This function takes the following parameters:
; 1 - The number of items still unaccounted for a product;
; 2 - The number of items for the product in a box.
; The function must return how many items remain to be moved, after counting those in the box

; TODO: define the 'calculate_payment' function
; This function takes the following parameters:
; 1 - The total number of boxes moved;
; 2 - The number of truck trips made;
; 3 - The number of lost items;
; 4 - The value of each lost item; and
; 5 - The upfront payment.
; The function must return how much you should be paid at the end

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
