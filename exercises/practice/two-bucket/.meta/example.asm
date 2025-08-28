SUCCESS equ 0
UNREACHABLE_GOAL equ 1

section .text
global measure

%macro check_visited_and_add_node 0
    mov r12, r9 ; queue rear is next to visited frontier
%%loop:
    add r12, 24

    cmp r12, rbp
    je %%add_state ; reached end of visited nodes and current node wasn't found, so it's valid

    cmp r10, qword [r12]
    sete r13b ; sets if visited node first bucket is equal to current node first bucket

    cmp r11, qword [r12 + 8]
    sete r14b ; sets if visited node second bucket is equal to current node second bucket

    and r13b, r14b
    jnz %%end ; if both conditions are true, visited node is equal to current node and it's invalid
    ; otherwise moves to next iteration

    jmp %%loop

%%add_state:
    ; node is valid, add it to queue

    sub rsp, 24
    mov qword [rsp], r10
    mov qword [rsp + 8], r11

    mov r10, qword [r9 + 16]
    inc r10 ; number of steps of child node is one more than number of steps of parent node

    mov qword [rsp + 16], r10
%%end:
%endmacro

%macro pour_first_into_second 0
    mov r11, rdx
    sub r11, qword [r9 + 8] ; difference between max capacity for second bucket and its current volume

    cmp r11, qword [r9]
    cmovg r11, qword [r9]  ; if difference is greater than current volume in first bucket
                           ; then pouring volume is current volume

    mov r10, qword [r9]
    sub r10, r11 ; first bucket's volume is reduced by pouring volume

    add r11, qword [r9 + 8] ; second bucket's volume is increased by pouring volume

    cmp r8d, 1
    jne %%check_visited ; second bucket's volume was increased by pouring volume,
                        ; so it can only be empty if first bucket is also empty
                        ; so if start bucket is the second, either both are empty or start bucket is non-empty
                        ; both are valid states

    ; otherwise, start bucket is the first and if second bucket is full and first bucket is empty, node is invalid
    cmp r10, 0
    sete r12b ; sets if first bucket is empty

    cmp r11, rdx
    sete r13b ; sets if second bucket is full

    and r12b, r13b
    jnz %%end ; if both conditions are true, node is invalid
    ; otherwise, check if it was visited

%%check_visited:
    check_visited_and_add_node
%%end:
%endmacro

%macro pour_second_into_first 0
    mov r10, rsi
    sub r10, qword [r9] ; difference between max capacity for first bucket and its current volume

    cmp r10, qword [r9 + 8]
    cmovg r10, qword [r9 + 8] ; if difference is greater than current volume in second bucket
                              ; then pouring volume is current volume

    mov r11, qword [r9 + 8]
    sub r11, r10 ; second bucket's volume is reduced by pouring volume

    add r10, qword [r9] ; first bucket's volume is increased by pouring volume

    cmp r8d, 1
    je %%check_visited ; first bucket's volume was increased by pouring volume,
                       ; so it can only be empty if second bucket is also empty
                       ; so if start bucket is the first, either both are empty or start bucket is non-empty
                       ; both are valid states

    ; otherwise, start bucket is the second and if first bucket is full and second bucket is empty, node is invalid
    cmp r10, rsi
    sete r12b ; sets if first bucket is full

    cmp r11, 0
    sete r13b ; sets if second bucket is empty

    and r12b, r13b
    jnz %%end ; if both conditions are true, node is invalid
    ; otherwise, check if it was visited

%%check_visited:
    check_visited_and_add_node
%%end:
%endmacro

%macro empty_first 0
    xor r10, r10 ; first bucket is empty
    mov r11, qword [r9 + 8] ; second bucket remains with same volume

    cmp r8d, 1
    jne %%check_visited ; first bucket is empty, so constraint can only be violated
                        ; if start bucket is the first
                        ; since, if it's the second, then either both are empty (which is not invalid)
                        ; or the start bucket is non-empty

    cmp r11, rdx
    je %%end ; if start bucket is the first and second bucket is full, this node is invalid
    ; otherwise, check if it was visited

%%check_visited:
    check_visited_and_add_node
%%end:
%endmacro

%macro empty_second 0
    mov r10, qword [r9] ; first bucket remains with same volume
    xor r11, r11 ; second bucket is empty

    cmp r8d, 1
    je %%check_visited ; second bucket is empty, so constraint can only be violated
                       ; if start bucket is the second
                       ; since, if it's the first, then either both are empty (which is not invalid)
                       ; or the start bucket is non-empty

    cmp r10, rsi
    je %%end ; if start bucket is the second and first bucket is full, this node is invalid
    ; otherwise, check if it was visited

%%check_visited:
    check_visited_and_add_node
%%end:
%endmacro

%macro fill_first 0
    mov r10, rsi ; first bucket is at max capacity
    mov r11, qword [r9 + 8] ; second bucket remains with same volume

    cmp r8d, 1
    je %%check_visited ; first bucket is full, so constraint can only be violated
                       ; if start bucket is the second

    cmp r11, 0
    je %%end ; if start bucket is the second and it's empty, this node is invalid
    ; otherwise, check if it was visited

%%check_visited:
    check_visited_and_add_node
%%end:
%endmacro

%macro fill_second 0
    mov r10, qword [r9] ; first bucket remains with same volume
    mov r11, rdx ; second bucket is at max capacity

    cmp r8d, 1
    jne %%check_visited ; second bucket is full, so constraint can only be violated
                        ; if start bucket is the first

    cmp r10, 0
    je %%end ; if start bucket is the first and it's empty, this node is invalid
    ; otherwise, check if it was visited

%%check_visited:
    check_visited_and_add_node
%%end:
%endmacro

%macro epilogue 0
    mov rsp, rbp
    pop rbp
    pop r14
    pop r13
    pop r12
%endmacro

measure:
    ; rdi - pointer to a struct bucket_result_t, formed of a uint64_t, an int and a uint64_t
    ; rsi - uint64_t representing capacity of the first bucket
    ; rdx - uint64_t representing capacity of the second bucket
    ; rcx - uint64_t representing the goal
    ; r8d - enum (int32_t) representing the start bucket, which should be filled first
    ; return is a success flag in eax

    ; I've chosen to solve this problem using a queue to keep track of nodes representing state of the system
    ; Each node has 24 bytes:
    ; -> 8 bytes for the volume of the first bucket as a uint64_t
    ; -> 8 bytes for the volume of the second bucket as a uint64_t
    ; -> 8 bytes for the number of steps needed to reach the node as a uint64_t
    ;
    ; The initial node is determined by the starting bucket. The first step is filling this bucket, per the instructions
    ;
    ; On how to implement the queue
    ; I decided this could be done using the stack, since I could simply sub RSP to add new nodes
    ; The problem was the other end of the queue, which should be reduced by each consumed node
    ;
    ; However, after some thought, I concluded that these consumed nodes should be remembered
    ; Since I needed to keep track of visited nodes, to avoid repetitions and circular paths in the graph
    ;
    ; So in the end, the entire structure is determined by 3 pointers:
    ; -> The "frontier" of the queue, where new nodes should be added
    ; -> The "rear" of the queue, where new nodes should be consumed (considering it's a FIFO data structure)
    ; -> Since the rear of the queue is also the frontier of the visited nodes,
    ; there's only need for a third pointer, which marks the end of the visited nodes
    ;
    ; The algorithm is then:
    ; 1- Add first node, corresponding to initial state (the filling of the starting bucket);
    ; 2- Proceed to the loop, comparing current the node at the rear of the queue with the goal
    ; 3- If the goal is not reached, proceed to add nodes according to valid state transitions
    ; 4- There are 6 possible state transitions:
    ; 4.1- Pour from first bucket into the second
    ; 4.2- Pour from second bucket into the first
    ; 4.3- Empty first bucket
    ; 4.4- Empty second bucket
    ; 4.5- Fill first bucket
    ; 4.6- Fill second bucket
    ; Those state transitions were implemented as macros
    ; 5- Each state transition must check for the constraints:
    ; 5.1- No node is valid where starting bucket is empty and non-starting bucket is full
    ; 5.2- No node already visited is valid
    ; 6- Checking for visited nodes is done with a linear search between current queue rear and RBP, which marks the end of the stack
    ; 7- If a node is valid, add it to the queue, reducing RSP by node size (24 bytes)
    ; 8- Once all state transitions are checked, if current rear is equal to current frontier of the queue, then queue is empty and the goal is unreachable
    ; 9- Otherwise moves to next iteration of the loop

    ; prologue
    push r12
    push r13
    push r14
    push rbp
    mov rbp, rsp

    xor r9, r9
    xor r10, r10

    cmp r8d, 1
    cmove r9, rsi ; if start bucket is the first, moves max capacity for first bucket into r9
    cmovne r10, rdx ; if start bucket is the second, moves max capacity for second bucket into r10

    sub rsp, 24
    mov qword [rsp], r9 ; starting volume for first bucket is 0 or max capacity for first bucket
    mov qword [rsp + 8], r10 ; starting volume for second bucket is 0 or max capacity for second bucket
    mov qword [rsp + 16], 1 ; initial step is 1

    mov r9, rsp ; r9 holds rear of the queue
.main_loop:
    cmp qword [r9], rcx
    je .goal_first ; first bucket is goal bucket

    cmp qword [r9 + 8], rcx
    je .goal_second ; second bucket is goal bucket

    ; checks each of the six state transitions
    pour_first_into_second
    pour_second_into_first
    empty_first
    empty_second
    fill_first
    fill_second

    cmp r9, rsp
    je .unreachable ; if rear of the queue is equal to its frontier, queue is empty
                    ; since there won't be no more nodes to check, the goal is unreachable

    ; otherwise, the current node was consumed and the rear is moved to next node in the queue
    sub r9, 24
    jmp .main_loop ; repeats until found goal or queue empty

.goal_first:
    mov r10, qword [r9 + 16] ; num of steps in the node corresponding to goal bucket
    mov qword [rdi], r10 ; first member of bucket_result_t is num of moves as a qword

    mov dword [rdi + 8], 1 ; second member of bucket_result_t is id of goal_bucket as an enum (int32_t)

    mov r10, qword [r9 + 8]
    mov qword [rdi + 16], r10 ; third member of bucket_result_t is the volume in the non-goal bucket
                              ; due to padding, the offset is 16 bytes (not 12)

    mov rax, SUCCESS ; signals success
    epilogue
    ret

.goal_second:
    mov r10, qword [r9 + 16] ; num of steps in the node corresponding to goal bucket
    mov qword [rdi], r10 ; first member of bucket_result_t is num of moves as a qword

    mov dword [rdi + 8], 2 ; second member of bucket_result_t is id of goal_bucket as an enum (int32_t)

    mov r10, qword [r9]
    mov qword [rdi + 16], r10 ; third member of bucket_result_t is the volume in the non-goal bucket
                              ; due to padding, the offset is 16 bytes (not 12)

    mov rax, SUCCESS ; signals success
    epilogue
    ret

.unreachable:
    mov rax, UNREACHABLE_GOAL ; signals error
    epilogue
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
