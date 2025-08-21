NEGATIVE_TARGET equ -1
UNREACHABLE_TARGET equ -2

section .text
global find_fewest_coins

%macro swap 2
    push r12
    mov r12, qword %1
    xchg r12, qword %2
    xchg qword %1, r12
    pop r12
%endmacro

find_fewest_coins:
    ; rdi - output uint64_t buffer
    ; rsi - input uint64_t array representing coins
    ; rdx - size of input array
    ; rcx - target value
    ; return is the size of the output buffer as a int64_t, in rax

    ; The algorithm is:
    ;
    ; First, check for invalid target n
    ;
    ; Then, create a map in the stack between keys 1..n to a node
    ; This node has 8 bytes:
    ; -> 4 for previous value in the path (parent)
    ; -> 2 for the last coin added to get to key
    ; -> 2 for the current length of the path
    ;
    ; Once created the map, it is initialized such that the first 6 bytes are NULL
    ; and the last 2 bytes (the length) is set to MAX WORD
    ;
    ; Then, initial values, corresponding to coins present in the input array, are added
    ; Each coin has NULL for parent, itself as coin and 1 for length
    ;
    ; Then, there's a main loop which continues as long as a flag is set or the target is not found in the map.
    ; This flag is cleared at the beginning of the loop and set only when a new key/val is added to the map
    ;
    ; Inside the main loop, there's a map loop, which iterates over all keys in the map
    ;
    ; For each key with non NULL length (possible parent), there's an inner loop
    ; which iterates over coins in input array and sums current key with current coin.
    ;
    ; If sum is valid (lesser than or equal to target), checks if the length for the corresponding node
    ; in the map is greater than 1 + len(parent node). If it's not, continue.
    ;
    ; Otherwise, substitutes the current node with the new one formed by the parent key,
    ; the current coin and the new length (1 + len(parent node)), and sets the insert flag.
    ;
    ; After the main loop, the length in the node corresponding to the target is passed to rax
    ; And the path is walked from child to parent, adding the corresponding coins in the node,
    ; until the leaf is reached.
    ;
    ; At this point, the only thing remaining is sorting the output array, which is done with a quicksort

    xchg rdx, rcx

    cmp rdx, 0
    jl .negative_target
    je .zero_target

    ; prologue
    push r12
    push r13
    push r14
    push rbp
    mov rbp, rsp

    mov r11, rdx
    inc r11
    shl r11, 3 ; 4 byte for parent
               ; 2 byte for added coin
               ; 2 byte for length

    sub rsp, r11
    shr r11, 3

    xor r8, r8
.initialize_map:
    mov dword [rsp + 8*r8], 0
    mov word [rsp + 8*r8 + 4], 0
    mov word [rsp + 8*r8 + 6], 0xFFFF
    inc r8
    cmp r8, r11
    jne .initialize_map

    mov r8, -1
.fill_map:
    inc r8

    cmp r8, rcx
    jge .end_fill_map

    mov r9, qword [rsi + 8*r8]
    cmp r9, rdx
    jg .fill_map

    mov word [rsp + 8*r9 + 4], r9w ; coin is itself
    mov word [rsp + 8*r9 + 6], 1 ; length is 1

    jmp .fill_map

.end_fill_map:

    mov r10, 1 ; flag
.main_loop:
    cmp r10, 1
    jne .unreachable   ; if flag is not set, no key/val was added in last iteration
                       ; which means all possible new sums are beyond target
                       ; So the target is unreachable

    cmp word [rsp + 8*rdx + 6], 0xFFFF
    jne .found_target ; if length is not default, target was found
                      ; it's important to wait until the end of the last iteration
                      ; as another more efficient path might be found after the first
                      ; but as the length is increase continuously each iteration
                      ; no optimal path can be found in following iterations

    xor r8, r8
    xor r10, r10
    xor r12, r12
    xor r13, r13
.map_loop:
    inc r8

    cmp r8, r11
    jge .main_loop

    cmp word [rsp + 8*r8 + 6], 0xFFFF
    je .map_loop ; value not set -> continue

    mov r9, -1
.inner_loop:
    inc r9

    cmp r9, rcx
    jge .map_loop

    mov r14, qword [rsi + 8*r9] ; current coin

    mov rax, r8
    add rax, r14 ; coin + parent

    cmp rax, rdx
    jg .map_loop

    mov r12w, word [rsp + 8*r8 + 6]
    inc r12w ; new len

    mov r13w, word [rsp + 8*rax + 6] ; current len

    cmp r13w, r12w
    jbe .inner_loop ; if current len is lesser than, or equal to, new len -> continue
    ; Otherwise exchange nodes

    mov dword [rsp + 8*rax], r8d ; parent
    mov word [rsp + 8*rax + 4], r14w ; added coin
    mov word [rsp + 8*rax + 6], r12w ; new len

    mov r10, 1 ; set flag

    jmp .inner_loop

.unreachable:
    mov rax, UNREACHABLE_TARGET

    ; epilogue
    mov rsp, rbp
    pop rbp
    pop r14
    pop r13
    pop r12

    ret

.found_target:
    xor rax, rax
    mov ax, word [rsp + 8*rdx + 6] ; moves final length to rax

    xor r10, r10
    mov r10, rdx
    mov r9, -1
.insert:
    cmp dword [rsp + 8*r10], 0
    je .end_insert ; continue while parent is not NULL

    inc r9

    xor r8, r8
    mov r8w, word [rsp + 8*r10 + 4] ; current coin

    mov qword [rdi + 8*r9], r8

    mov r10d, dword [rsp + 8*r10] ; current node = parent

    jmp .insert

.end_insert:
    ; leaf node's coin must be inserted
    inc r9
    mov qword [rdi + 8*r9], r10

    ; the stack isn't needed anymore, after inserting to output
    ; epilogue
    mov rsp, rbp
    pop rbp
    pop r14
    pop r13
    pop r12

    ; Last thing is a sort of elements in the output
    ; Algorithm chosen was quicksort, mainly because it's usually easier to setup
    ; and has a time complexity of O(log2n)

    xor r8, r8 ; low
    mov r9, rax
    dec r9 ; high
.quicksort:
    cmp r8, r9
    jge .end_sort ; while (low < high)

    jmp .partition ; do a partition
                   ; index - 1 is stored in r11
.sort:
    push r9
    push r11

    mov r9, r11
    call .quicksort ; quicksort(arr, low, index - 1)

    pop r11
    pop r9

    mov r8, r11
    add r8, 2
    call .quicksort ; quicksort(arr, index + 1, high)

.end_sort:
    ret

.partition:
    mov r10, qword [rdi + 8*r9] ; pivot
    mov r11, r8
    dec r11 ; i = low - 1

    mov rcx, r8
    dec rcx
.partition_loop:
    inc rcx ; j

    cmp rcx, r9
    jge .end_partition_loop

    cmp qword [rdi + 8*rcx], r10
    jge .partition_loop

    inc r11
    swap [rdi + 8*r11], [rdi + 8*rcx]
    jmp .partition_loop

.end_partition_loop:
    swap [rdi + 8*r11 + 8], [rdi + 8*r9]
    jmp .sort

.negative_target:
    mov rax, NEGATIVE_TARGET
    ret

.zero_target:
    mov rax, 0
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
