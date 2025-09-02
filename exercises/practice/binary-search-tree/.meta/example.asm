NODE_SIZE equ 24

section .text

global build_tree
global sorted_data
global delete_tree

build_tree:
    ; rdi - allocator pointer
    ; rsi - input array of int64_t
    ; rdx - num of elements in input array
    ; return is node pointer

    ; A node_t has 24 bytes:
    ; 8 bytes -> data value (int64_t)
    ; 8 bytes -> pointer to left node
    ; 8 bytes -> pointer to right node

    ; Algorithm is:
    ;
    ; If size of input array == 0, returns
    ; If not, creates root node and adds first element to it
    ; Then iterates over remaining input elements in main loop
    ;
    ; Main loop continues until end of input array
    ;
    ; Moves root node to r10, to represent current node
    ; decreases counter for elements in input array
    ; And starts check loop
    ;
    ; If element greater than current node's data, checks if right node is NULL
    ;
    ; If it is, allocs memory for a new node,
    ; adds pointer to right node and adds element to it
    ; Then continue main loop
    ;
    ; If it's not, moves right node to current node and continues check loop
    ;
    ; If element not greater than current node's data, checks if left node is NULL
    ;
    ; If it is, allocs memory for a new node,
    ; adds pointer to left node and adds element to it
    ; The continue main loop
    ;
    ; If it's not, moves left node to current node and continues check loop

    ; Since we are calling malloc multiple times, there's no guarantee that
    ; any of the usual registers (RAX, RCX, RDX and R8 to R11) are preserved
    ; So all important values are saved in the stack to be reused after external calls

    ; prologue
    push rbp
    mov rbp, rsp
    sub rsp, 48

    mov qword [rsp], rdi ; saves malloc pointer
    mov qword [rsp + 8], rsi ; saves input array
    mov qword [rsp + 16], rdx ; saves counter for input array

    xor rax, rax
    cmp rdx, 0
    je null_tree ; if counter is 0, tree is NULL
    ; otherwise, allocates first node

    mov rdi, NODE_SIZE
    call qword [rsp] ; rax now holds pointer to a new node

    mov qword [rsp + 24], rax ; root node is now saved in rsp + 24

    ; Input array pointer is moved to RSI (register may be modified by malloc)
    ; First input value is loaded
    ; Updated value for input array pointer is moved to stack

    mov rsi, qword [rsp + 8]
    lodsq
    mov qword [rsp + 8], rsi

    mov r9, qword [rsp + 24] ; root node is now saved in r9
    mov qword [r9], rax ; first element is saved in root node data field
    mov qword [r9 + 8], 0 ; NULL
    mov qword [r9 + 16], 0 ; NULL

    dec qword [rsp + 16] ; counter--
main_loop:
    cmp qword [rsp + 16], 0
    je end_function ; counter == 0 -> end of input aray

    dec qword [rsp + 16] ; counter--

    mov r10, qword [rsp + 24] ; current node = parent node;

    ; Input array pointer is moved to RSI (register may be modified by malloc)
    ; First input value is loaded
    ; Updated value for input array pointer is moved to stack

    mov rsi, qword [rsp + 8]
    lodsq
    mov qword [rsp + 8], rsi
consume_input:
    cmp rax, qword [r10]
    jg to_right ; current element > current node data -> checks right node
    ; otherwise, checks left node

to_left:
    cmp qword [r10 + 8], 0
    jne fork_left ; if left node is not NULL, moves to left node
    ; otherwise, creates a new left node and adds element to it

    mov qword [rsp + 32], rax ; saves element value (may be modified by malloc)
    mov qword [rsp + 40], r10 ; saves current node (may be modified by malloc)

    mov rdi, NODE_SIZE
    call qword [rsp] ; calls malloc

    mov r10, qword [rsp + 40] ; restores current node
    mov rsi, qword [rsp + 8] ; restores current input pointer

    mov qword [r10 + 8], rax ; moves new node to current_node.left
    jmp add_data ; moves to add data to new node

to_right:
    cmp qword [r10 + 16], 0
    jne fork_right ; if right node is not NULL, moves to right node
    ; otherwise, creates a new right node and adds element to it

    mov qword [rsp + 32], rax ; saves element value (may be modified by malloc)
    mov qword [rsp + 40], r10 ; saves current node (may be modified by malloc)

    mov rdi, 24
    call qword [rsp] ; calls malloc

    mov r10, qword [rsp + 40] ; restores current node
    mov rsi, qword [rsp + 8] ; restores current input pointer

    mov qword [r10 + 16], rax  ; moves new node to current_node.right
    ; fallthroughs to add data to new node

add_data:
    mov rdx, qword [rsp + 32] ; element value (saved before malloc)
    mov qword [rax], rdx ; moves value to new_node.data
    mov qword [rax + 8], 0 ; new_node.left = NULL
    mov qword [rax + 16], 0 ; new_node.right = NULL

    jmp main_loop  ; continues loop

end_function:
    mov rax, qword [rsp + 24] ; moves root node to RAX, for returning

null_tree:
    ; epilogue

    mov rsp, rbp
    pop rbp
    ret

fork_right:
    mov r10, qword [r10 + 16]
    jmp consume_input

fork_left:
    mov r10, qword [r10 + 8]
    jmp consume_input

sorted_data:
    ; rdi - output buffer of int64_t
    ; rsi - input tree
    ; size of output buffer is returned in rax

    ; Recursive algorithm:
    ;
    ; function recur(node):
    ; if (!node) return;
    ; if (node->left) { node = node->left; recur(node); }
    ; *output = node->data;
    ; output++;
    ; if (node->right) { node = node->right; recur(node); }
    ; return;

    xor rax, rax

    cmp qword [rsi], 0
    je end_sort ; if (!node) return;

sort_helper:
    ; LEFT PATH

    cmp qword [rsi + 8], 0
    je add_sorted_data ; if (!node->left) add_sorted_data

    push rsi ; saves node

    mov rsi, qword [rsi + 8] ; node = node->left;
    call sort_helper ; recur(node)

    pop rsi ; restores node

add_sorted_data:

    inc rax ; increases size counter for output buffer
    movsq ; moves node data to output buffer and increments rsi by 8
    ; rsi now points to left node

    ; RIGHT PATH

    cmp qword [rsi + 8], 0 ; right node is 8 bytes after left node
    je end_sort ; if (!node->right) return;

    push rsi ; saves node

    mov rsi, qword [rsi + 8] ; node = node->right;
    call sort_helper ; recur(node)

    pop rsi ; restores node

end_sort:
    ret

delete_tree:
    ; rdi - pointer to node
    ; rsi - deallocator pointer
    ; return is void

    ; Recursive Algorithm
    ; deletes left node, recursively
    ; deletes right node, recursively
    ; deletes node

    ; prologue
    push rbp
    mov rbp, rsp
    sub rsp, 16

    mov qword [rsp], rdi ; saves node
    mov qword [rsp + 8], rsi ; saves free

    cmp rdi, 0
    je .end ; node is NULL, can return

    mov rdi, qword [rsp]
    mov rdi, qword [rdi + 8]
    mov rsi, qword [rsp + 8]

    call delete_tree ; deletes left node

    mov rdi, qword [rsp]
    mov rdi, qword [rdi + 16]
    mov rsi, qword [rsp + 8]

    call delete_tree ; deletes right node

    mov rdi, qword [rsp] ; moves current node to rdi
    call qword [rsp + 8] ; free current node
.end:
    ; epilogue
    mov rsp, rbp
    pop rbp
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
