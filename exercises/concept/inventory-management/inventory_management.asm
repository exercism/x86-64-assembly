; Everything that comes after a semicolon (;) is a comment

WEIGHT_OF_EMPTY_BOX equ 500
TRUCK_HEIGHT equ 300
PAY_PER_BOX equ 5
PAY_PER_TRUCK_TRIP equ 220

section .text

; You should implement functions in the .text section
; A skeleton is provided for the first function

; the global directive makes a function visible to the test files
global get_box_weight
get_box_weight:
    ; This function takes the following parameters:
    ; - The number of items for the first product in the box
    ; - The weight of each item of the first product, in grams
    ; - The number of items for the second product in the box
    ; - The weight of each item of the second product, in grams
    ; The function must return the total weight of a box, in grams
    ret

global max_number_of_boxes
max_number_of_boxes:
    ; TODO: define the 'max_number_of_boxes' function
    ; This function takes the following parameter:
    ; - The height of the box, in centimeters
    ; The function must return how many boxes can be stacked vertically
    ret

global items_to_be_moved
items_to_be_moved:
    ; TODO: define the 'items_to_be_moved' function
    ; This function takes the following parameters:
    ; - The number of items still unaccounted for a product
    ; - The number of items for the product in a box
    ; The function must return how many items remain to be moved, after counting those in the box
    ret

global calculate_payment
calculate_payment:
    ; TODO: define the 'calculate_payment' function
    ; This function takes the following parameters:
    ; - The upfront payment
    ; - The total number of boxes moved
    ; - The number of truck trips made
    ; - The number of lost items
    ; - The value of each lost item
    ; - The number of other workers to split the payment/debt with you
    ; The function must return how much you should be paid, or pay, at the end
    ; Remember that you get your share and also the remainder of the division
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
