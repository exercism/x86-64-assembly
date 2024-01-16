; a Node in the doubly linked-list
struc Node
        ; pointer to previous node
        .Prev:  resq    1
        ; pointer to next node
        .Next:  resq    1
        ; int data
        .Data:  resd    1
endstruc

; references to start and end of a list
struc List
        ; pointer to First node in the List
        .First  resq    1
        ; pointer to Last node in the list
        .Last   resq    1
endstruc

; this code can be run across different OS
; don't rely on libc or syscalls for memory
; instead rely on the OS to provide
; an arena like allocation in the .bss
section .bss
; store the single instance of List to store pointers to First and Last nodes
list:
        resb List_size
; space for 16 nodes which will be "allocated" sequentially
nodes:
        resb 0x10*Node_size
; an integer that has the next available node from nodes to "allocate"
currnodeidx:
        resq 1

section .text

global list_create
list_create:
        ; Provide your implementation here
        ret

global list_count
list_count:
        ; Provide your implementation here
        ret

global list_push
list_push:
        ; Provide your implementation here
        ret

global list_pop
list_pop:
        ; Provide your implementation here
        ret

global list_unshift
list_unshift:
        ; Provide your implementation here
        ret

global list_shift
list_shift:
        ; Provide your implementation here
        ret

global list_delete
list_delete:
        ; Provide your implementation here
        ret

global list_destroy
list_destroy:
        ; Provide your implementation here
        ret