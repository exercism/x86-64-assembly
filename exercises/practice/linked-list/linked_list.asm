section .text
; simple node struct for linked list
struc node
        .prev:  resq    1
        .next:  resq    1
        .data:  resd    1
endstruc

; simple struct to store first and last nodes
struc list
        .first  resq    1
        .last   resq    1
endstruc

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