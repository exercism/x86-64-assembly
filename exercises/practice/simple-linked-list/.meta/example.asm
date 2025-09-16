section .text

global create_list
global push_list
global pop_list
global reverse_list
global delete_list

; System V ABI states that external calls must be made with a stack 16-byte aligned
; It didn't seem to make a difference here, things worked nonetheless
; But, for correctness and future-proofing, I've taken that in consideration in all functions

create_list:
    ; RDI - pointer to allocator
    ; RSI - pointer to deallocator
    ; return is a list_t pointer with:
    ; 1- a pointer to a node_t,
    ; 2- a pointer to a allocator,
    ; 3- a pointer to a deallocator

    ; Since we are calling malloc, registers must be saved

    push rbp
    mov rbp, rsp
    sub rsp, 16

    mov qword [rsp], rdi
    mov qword [rsp + 8], rsi

    mov rdi, 24 ; size of a list_t
    call qword [rsp] ; stack is 16-byte aligned:
                     ; 1 qword for pushing rbp
                     ; 2 qwords for subbing rsp
                     ; 1 qword for pushing RIP (in CALL)

    mov qword [rax], 0 ; head is null

    mov rdi, qword [rsp]
    mov qword [rax + 8], rdi ; allocator

    mov rsi, qword [rsp + 8]
    mov qword [rax + 16], rsi ; deallocator

    mov rsp, rbp
    pop rbp
    ret

push_list:
    ; RDI - list
    ; RSI - value to push
    ; return is void

    ; Since we are calling malloc, registers must be saved

    push rbp
    mov rbp, rsp
    sub rsp, 16

    mov qword [rsp], rdi
    mov qword [rsp + 8], rsi

    mov r10, qword [rdi + 8]
    mov rdi, 16 ; size of node_t
    call r10             ; stack is 16-byte aligned:
                         ; 1 qword for pushing rbp
                         ; 2 qwords for subbing rsp
                         ; 1 qword for pushing RIP (in CALL)

    mov r10, qword [rsp + 8]
    mov qword [rax], r10

    mov r10, qword [rsp] ; list_t pointer
    mov r11, qword [r10] ; head

    mov qword [rax + 8], r11 ; node->next = head
    mov qword [r10], rax ; list->head = node

    mov rsp, rbp
    pop rbp
    ret

pop_list:
    ; RDI - list_t
    ; return is value of head in RAX

    mov r10, qword [rdi]
    mov rax, qword [r10]
    mov r11, qword [r10 + 8]
    mov qword [rdi], r11

    push rax ; Since we are calling free, register must be saved

    mov r11, qword [rdi + 16]
    mov rdi, r10
    call r11 ; stack is 16-byte aligned:
             ; 1 qword for pushing rax
             ; 1 qword for pushing RIP (in CALL)

    pop rax

    ret

reverse_list:
    ; RDI - list_t
    ; return is void

    cmp qword [rdi], 0
    je .return ; list is null, can return right away

    ; prologue

    push rbp
    mov rbp, rsp

    mov r11, qword [rdi] ; current node
.find_tail:
    cmp r11, 0
    je .found_it

    sub rsp, 8
    mov qword [rsp], r11 ; stores current node in stack
    mov r11, qword [r11 + 8] ; node = node->next

    jmp .find_tail

.found_it:
    mov r11, qword [rsp]
    mov qword [rdi], r11 ; last node is new head
    lea r10, [r11 + 8] ; current node = head->next
.reverse:
    add rsp, 8

    cmp rsp, rbp
    je .end_reverse ; end of nodes

    mov r9, qword [rsp] ; next node
    mov qword [r10], r9 ; current node->next = next node
    lea r10, [r9 + 8] ; current node = next node

    jmp .reverse

.end_reverse:
    mov qword [r10], 0 ; tail node->next = NULL

    ; epilogue
    mov rsp, rbp
    pop rbp
.return:
    ret

delete_list:
    ; RDI - pointer to a list_t

    cmp rdi, 0
    je .return ; if list is null, can return right away

    ; Algorithm is:
    ;
    ; fills the stack with all nodes in reversed order
    ; frees each one
    ; frees list
    ; returns

    ; Since we are calling free, registers must be saved

    push rbp
    mov rbp, rsp

    sub rsp, 24
    mov r10, qword [rdi + 16]
    mov qword [rbp - 8], r10 ; free
    mov qword [rbp - 16], rdi ; list

    mov rdi, qword [rdi]
    xor r8, r8
    xor rcx, rcx
.fill_stack:
    cmp rdi, 0
    je .end_filling

    inc rcx
    sub rsp, 8
    mov qword [rsp], rdi ; each node pointer is stored in the stack, in reversed order
    mov rdi, qword [rdi + 8] ; head = head->next
    jmp .fill_stack

.end_filling:
    ; If number of nodes is even, stack won't be 16-byte aligned in free call
    ; so stack is reduced by a further qword

    mov qword [rbp - 24], rsp

    inc rcx
    and rcx, 1
    shl rcx, 3
    sub rsp, rcx

.free_nodes:
    lea r10, [rbp - 24]
    mov r11, qword [rbp - 24]

    cmp r11, r10
    je .free_list

    mov rdi, qword [r11]
    call qword [rbp - 8] ; stack is 16-byte aligned:
                         ; 1 qword for pushing rbp
                         ; 3 qwords for storing variables
                         ; a odd multiple of 8 bytes for storing nodes
                         ; 1 qword for pushing RIP (in CALL)

    add qword [rbp - 24], 8
    jmp .free_nodes

.free_list:
    mov rdi, qword [rbp - 16]
    call qword [rbp - 8] ; stack is 16-byte aligned:
                         ; 1 qword for pushing rbp
                         ; 3 qwords for storing variables
                         ; a odd multiple of 8 bytes for storing nodes
                         ; 1 qword for pushing RIP (in CALL)

    mov rsp, rbp
    pop rbp
.return:
    ret


%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
