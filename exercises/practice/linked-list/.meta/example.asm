default rel
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
global list_count
global list_push
global list_pop
global list_unshift
global list_shift
global list_delete
global list_destroy

get_list:
        ; reset current node index to 0
        mov     dword [currnodeidx], 0
        ; return pointer to list
        lea     rax, [list]
        ret
get_node:
        movsx   rax, dword [currnodeidx]
        lea     edx, [rax+1]
        imul    rax, rax, Node_size
        mov     dword [currnodeidx], edx
        lea     rdx, [nodes]
        add     rax, rdx
        ret

list_node_create:
        mov     ecx, edx
        call    get_node
        test    rax, rax
        je      .err
        mov     qword [rax+Node.Prev], rdi
        mov     qword [rax+Node.Next], rsi
        mov     dword [rax+Node.Data], ecx
.err:
        ret
list_create:
        call    get_list
        test    rax, rax
        je      .err
        mov     qword [rax+List.First], 0
        mov     qword [rax+List.Last], 0
.err:
        ret
list_count:
        mov     rdx, qword [rdi+List.First]
        xor     eax, eax
.loop_count:
        test    rdx, rdx
        je      .fin_loop_count
        mov     rdx, qword [rdx+Node.Next]
        inc     rax
        jmp     .loop_count
.fin_loop_count:
        ret
list_push:
        mov     r8, rdi
        mov     rdi, qword [rdi+List.Last]
        mov     edx, esi
        xor     esi, esi
        call    list_node_create
        test    rax, rax
        je      .err
        cmp     qword [r8+List.First], 0
        mov     qword [r8+List.Last], rax
        jne     .first_set
        mov     qword [r8+List.First], rax
        ret
.first_set:
        mov     rdx, qword [rax+Node.Prev]
        mov     qword [rdx+Node.Next], rax
.err:
        ret
list_pop:
        mov     rax, qword [rdi+List.Last]
        mov     rdx, qword [rax+Node.Prev]
        mov     r8d, dword [rax+Node.Data]
        mov     qword [rdi+List.Last], rdx
        cmp     qword [rdi+List.First], rax
        jne     .set_prev_next
        mov     qword [rdi+List.First], 0
        jmp     .empty
.set_prev_next:
        mov     qword [rdx+Node.Next], 0
.empty:
        mov     qword [rax+Node.Prev], 0
        mov     qword [rax+Node.Next], 0
        mov     dword [rax+Node.Data], 0
        mov     eax, r8d
        ret
list_unshift:
        mov     edx, esi
        mov     rsi, qword [rdi+List.First]
        mov     r8, rdi
        xor     edi, edi
        call    list_node_create
        test    rax, rax
        je      .err
        cmp     qword [r8+List.Last], 0
        mov     qword [r8+List.First], rax
        jne     .set_next_prev
        mov     qword [r8+List.Last], rax
        ret
.set_next_prev:
        mov     rdx, qword [rax+Node.Next]
        mov     qword [rdx+Node.Prev], rax
.err:
        ret
list_shift:
        mov     rax, qword [rdi+List.First]
        mov     rdx, qword [rax+Node.Next]
        mov     r8d, dword [rax+Node.Data]
        mov     qword [rdi+List.First], rdx
        cmp     qword [rdi+List.Last], rax
        jne     .set_next_prev
        mov     qword [rdi+List.Last], 0
        jmp     .zero
.set_next_prev:
        mov     qword [rdx+Node.Prev], 0
.zero:
        mov     qword [rax+Node.Prev], 0
        mov     qword [rax+Node.Next], 0
        mov     dword [rax+Node.Data], 0
        mov     eax, r8d
        ret
list_delete:
        mov     r8, qword [rdi+List.First]
        mov     rax, r8
.search_loop:
        test    rax, rax
        je      .err
        mov     rdx, qword [rax+Node.Next]
        cmp     dword [rax+Node.Data], esi
        jne     .Next
        mov     rcx, qword [rax+Node.Prev]
        cmp     rax, r8
        jne     .set_prev_next
        mov     qword [rdi+List.First], rdx
        jmp     .last_compare
.set_prev_next:
        mov     qword [rcx+Node.Next], rdx
.last_compare:
        cmp     qword [rdi+List.Last], rax
        jne     .set_next_prev
        mov     qword [rdi+List.Last], rcx
        jmp     .zero
.set_next_prev:
        mov     rdx, qword [rax+Node.Next]
        mov     qword [rdx+Node.Prev], rcx
.zero:
        mov     qword [rax+Node.Prev], 0
        mov     qword [rax+Node.Next], 0
        mov     dword [rax+Node.Data], 0
        ret
.Next:
        mov     rax, rdx
        jmp     .search_loop
.err:
        ret
list_destroy:
        test    rdi, rdi
        je      .err
        mov     rax, qword [rdi+List.First]
.loop:
        test    rax, rax
        je      .zero
        mov     rdx, qword [rax+Node.Next]
        mov     qword [rax+Node.Prev], 0
        mov     qword [rax+Node.Next], 0
        mov     dword [rax+Node.Data], 0
        mov     rax, rdx
        jmp     .loop
.zero:
        mov     qword [rdi+List.First], 0
        mov     qword [rdi+List.Last], 0
.err:
        ret
