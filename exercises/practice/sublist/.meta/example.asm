UNEQUAL equ 0
EQUAL equ 1
SUBLIST equ 2
SUPERLIST equ 3

section .text
global sublist

sublist:
    ; rdi - array of int64_t (first list)
    ; rsi - size of first array as uint64_t
    ; rdx - array of int64_t (second list)
    ; rcx - size of second array as uint64_t
    ; return is an enum in eax

    xchg rsi, rdx ; for using cmpsq

    cmp rdx, rcx
    je .check_equality ; if lengths are the same, lists must be equal or unequal
    jg .check_superlist ; if first list is larger, it must be a superlist or unequal
    ; otherwise, second list is larger and first must be sublist or unequal

.check_sublist:
    cmp rdx, 0
    je .sublist ; empty list is sublist of any list
                ; except of other empty list, which is equal (but this is covered in .check_equality)

.sublist_loop:
    cmp rcx, rdx
    jl .unequal ; if at any point of the loop, the first list is greater, then the lists are unequal

    mov r8, qword [rdi]
    cmp r8, qword [rsi]
    jne .check_next_sublist ; if elements are different, no sublist starts here
    ; otherwise we check if a sublist starts here

    ; saves variables to use cmpsq
    mov r8, rdi
    mov r9, rsi
    mov r10, rcx

    mov rcx, rdx ; repe uses rcx as counter, it must be instantiated with the lesser length

    repe cmpsq
    je .sublist ; if the comparison exhausts the first list returning equal, then it's a sublist
    ; otherwise, the variables are restored to check next element

    mov rdi, r8
    mov rsi, r9
    mov rcx, r10

.check_next_sublist:
    ; moves to next element of the second list to check if a sublist starts there
    dec rcx
    add rsi, 8

    jmp .sublist_loop

.sublist:
    mov rax, SUBLIST
    ret

.check_superlist:
    cmp rcx, 0
    je .superlist ; any list is superlist of an empty list
                  ; except another empty list, which is equal (but this is covered in .check_equality)

.superlist_loop:
    cmp rdx, rcx
    jl .unequal ; if at any point of the loop, the first list's size is lesser, then the lists are unequal

    mov r8, qword [rdi]
    cmp r8, qword [rsi]
    jne .check_next_superlist ; if elements are different, no superlist starts here
    ; otherwise we check if a superlist starts here

    ; saves variables to use cmpsq
    mov r8, rdi
    mov r9, rsi
    mov r10, rcx

    ; repe uses rcx as counter, it must be instantiated with the lesser length
    ; but in this case rcx is already the lesser length

    repe cmpsq
    je .superlist ; if the comparison exhausts the second list returning equal, then the first is a superlist
    ; otherwise, the variables are restored to check next element

    mov rdi, r8
    mov rsi, r9
    mov rcx, r10

.check_next_superlist:
    ; moves to next element of the first list to check if a superlist starts there
    dec rdx
    add rdi, 8

    jmp .superlist_loop

.superlist:
    mov rax, SUPERLIST
    ret

.check_equality:
    ; sizes are equal, there's no need to change rcx for repe
    repe cmpsq
    jne .unequal

    mov rax, EQUAL
    ret

.unequal:
    mov rax, UNEQUAL
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
