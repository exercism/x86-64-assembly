; Everything that comes after a semicolon (;) is a comment

C2 equ 2
C3 equ 3
C4 equ 4
C5 equ 5
C6 equ 6
C7 equ 7
C8 equ 8
C9 equ 9
C10 equ 10
CJ equ 11
CQ equ 12
CK equ 13
CA equ 14

TRUE equ 1
FALSE equ 2

section .text

; the global directive makes a function visible to the test files
; You should implement functions in the .text section
; A skeleton is provided for the first function

global value_of_card

value_of_card:
    ; This function takes as parameter a number representing a card
    ; The function should return the numerical value of the passed-in card
    ret

; TODO: define the 'higher_card' function
; This function takes as parameters two numbers each representing a card
; The function should return which card has the higher value
; If both have the same value, both should be returned
; If one is higher, the second one should be 0

; TODO: define the 'value_of_ace' function
; This function takes as parameters two numbers each representing a card
; The function should return the value of an upcoming ace

; TODO: define the 'is_blackjack' function
; This function takes as parameters two numbers each representing a card
; The function should return TRUE if the two cards form a blackjack, and FALSE otherwise

; TODO: define the 'can_split_pairs' function
; This function takes as parameters two numbers each representing a card
; The function should return TRUE if the two cards can be split into two pairs, and FALSE otherwise

; TODO: define the 'can_double_down' function
; This function takes as parameters two numbers each representing a card
; The function should return TRUE if the two cards form a hand that can be doubled down, and FALSE otherwise

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
