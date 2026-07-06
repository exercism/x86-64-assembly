section .text

global admit_group
admit_group:
    ; TODO: implement the `admit_group` function
    ;
    ; This function atomically adds the size of a group to the shared admissions tally.
    ;
    ; This function takes as arguments, in order:
    ; 1. `admissions`: memory address of the shared admissions tally, a 64-bit signed integer
    ; 2. `group_size`: the number of people in the group, a 64-bit signed integer, always greater than 0
    ;
    ; The function has no return value.
    ; The tests call this function from several threads at the same time; no admission may be lost.
    ret

global change_reel
change_reel:
    ; TODO: implement the `change_reel` function
    ;
    ; This function atomically mounts the next reel and returns the one that was mounted.
    ;
    ; This function takes as arguments, in order:
    ; 1. `mounted`: memory address of the identifier of the mounted reel, a 64-bit signed integer
    ; 2. `next_reel`: the identifier of the reel to mount, a 64-bit signed integer
    ;
    ; The function returns the identifier of the previously mounted reel as a 64-bit signed integer.
    ; The tests call this function from several threads at the same time; no reel may be lost or duplicated.
    ret

global sell_ticket
sell_ticket:
    ; TODO: implement the `sell_ticket` function
    ;
    ; This function atomically adds one to the shared count of tickets sold and returns the number of the ticket just sold.
    ; The ticket number is the count after this sale.
    ;
    ; This function takes as an argument:
    ; 1. `tickets_sold`: memory address of the shared count of tickets sold, a 64-bit signed integer
    ;
    ; The function returns the ticket number as a 64-bit signed integer.
    ; The tests call this function from several threads at the same time.
    ret

global claim_seat
claim_seat:
    ; TODO: implement the `claim_seat` function
    ;
    ; This function atomically claims the next seat when one is still free, and returns the seat's number,
    ; which is the count of taken seats after this claim.
    ; When the screening is sold out, it returns 0 and leaves the count unchanged.
    ;
    ; This function takes as arguments, in order:
    ; 1. `seats_taken`: memory address of the count of seats already taken, a 64-bit signed integer, never above `capacity`
    ; 2. `capacity`: the number of seats in the screening, a 64-bit signed integer, always greater than 0
    ;
    ; The function returns the seat number, or 0 when the screening is sold out, as a 64-bit signed integer.
    ; The tests call this function from several threads at the same time; the screening must never oversell.
    ret

global visit_booth
visit_booth:
    ; TODO: implement the `visit_booth` function
    ;
    ; This function waits until the booth is free, claims it, runs the visitor's task,
    ; and reopens the booth before returning.
    ; The booth word is 0 when the booth is free and 1 when it is occupied.
    ; While the booth is held by someone else, wait politely with `pause`.
    ;
    ; This function takes as arguments, in order:
    ; 1. `booth`: memory address of the occupancy word, a 64-bit signed integer that is either 0 or 1
    ; 2. `task`: the visitor's task, a function that takes no parameters and has no return value
    ;
    ; The function has no return value.
    ; The tests call this function from several threads at the same time; the booth must be
    ; occupied for the whole task, and no visit or task may be lost.
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
