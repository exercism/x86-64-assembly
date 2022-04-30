default rel
section .text

global list_create
global list_count
global list_push
global list_pop
global list_unshift
global list_shift
global list_delete
global list_destroy

struc node
        .prev:  resq    1
        .next:  resq    1
        .data:  resd    1
endstruc

struc list
        .first  resq    1
        .last   resq    1
endstruc

get_list:
        mov     dword [curridx], 0
        lea     rax, [m]
        ret
get_node:
        movsx   rax, dword [curridx]
        lea     edx, [rax+1]
        imul    rax, rax, node_size
        mov     dword [curridx], edx
        lea     rdx, [glob]
        add     rax, rdx
        ret
zero_list:
        mov     qword [rdi+list.first], 0
        mov     qword [rdi+list.last], 0
        ret

list_node_create:
        mov     ecx, edx
        call    get_node
        test    rax, rax
        je      .err
        mov     qword [rax+node.prev], rdi
        mov     qword [rax+node.next], rsi
        mov     dword [rax+node.data], ecx
.err:
        ret
list_create:
        call    get_list
        test    rax, rax
        je      .err
        mov     qword [rax+list.first], 0
        mov     qword [rax+list.last], 0
.err:
        ret
list_count:
        mov     rdx, qword [rdi+list.first]
        xor     eax, eax
.loop_count:
        test    rdx, rdx
        je      .fin_loop_count
        mov     rdx, qword [rdx+node.next]
        inc     rax
        jmp     .loop_count
.fin_loop_count:
        ret
list_push:
        mov     r8, rdi
        mov     rdi, qword [rdi+list.last]
        mov     edx, esi
        xor     esi, esi
        call    list_node_create
        test    rax, rax
        je      .err
        cmp     qword [r8+list.first], 0
        mov     qword [r8+list.last], rax
        jne     .first_set
        mov     qword [r8+list.first], rax
        ret
.first_set:
        mov     rdx, qword [rax+node.prev]
        mov     qword [rdx+node.next], rax
.err:
        ret
list_pop:
        mov     rax, qword [rdi+list.last]
        mov     rdx, qword [rax+node.prev]
        mov     r8d, dword [rax+node.data]
        mov     qword [rdi+list.last], rdx
        cmp     qword [rdi+list.first], rax
        jne     .set_prev_next
        mov     qword [rdi+list.first], 0
        jmp     .empty
.set_prev_next:
        mov     qword [rdx+node.next], 0
.empty:
        mov     qword [rax+node.prev], 0
        mov     qword [rax+node.next], 0
        mov     dword [rax+node.data], 0
        mov     eax, r8d
        ret
list_unshift:
        mov     edx, esi
        mov     rsi, qword [rdi+list.first]
        mov     r8, rdi
        xor     edi, edi
        call    list_node_create
        test    rax, rax
        je      .err
        cmp     qword [r8+list.last], 0
        mov     qword [r8+list.first], rax
        jne     .set_next_prev
        mov     qword [r8+list.last], rax
        ret
.set_next_prev:
        mov     rdx, qword [rax+node.next]
        mov     qword [rdx+node.prev], rax
.err:
        ret
list_shift:
        mov     rax, qword [rdi+list.first]
        mov     rdx, qword [rax+node.next]
        mov     r8d, dword [rax+node.data]
        mov     qword [rdi+list.first], rdx
        cmp     qword [rdi+list.last], rax
        jne     .set_next_prev
        mov     qword [rdi+list.last], 0
        jmp     .zero
.set_next_prev:
        mov     qword [rdx+node.prev], 0
.zero:
        mov     qword [rax+node.prev], 0
        mov     qword [rax+node.next], 0
        mov     dword [rax+node.data], 0
        mov     eax, r8d
        ret
list_delete:
        mov     r8, qword [rdi+list.first]
        mov     rax, r8
.search_loop:
        test    rax, rax
        je      .err
        mov     rdx, qword [rax+node.next]
        cmp     dword [rax+node.data], esi
        jne     .next
        mov     rcx, qword [rax+node.prev]
        cmp     rax, r8
        jne     .set_prev_next
        mov     qword [rdi+list.first], rdx
        jmp     .last_compare
.set_prev_next:
        mov     qword [rcx+node.next], rdx
.last_compare:
        cmp     qword [rdi+list.last], rax
        jne     .set_next_prev
        mov     qword [rdi+list.last], rcx
        jmp     .zero
.set_next_prev:
        mov     rdx, qword [rax+node.next]
        mov     qword [rdx+node.prev], rcx
.zero:
        mov     qword [rax+node.prev], 0
        mov     qword [rax+node.next], 0
        mov     dword [rax+node.data], 0
        ret
.next:
        mov     rax, rdx
        jmp     .search_loop
.err:
        ret
list_destroy:
        test    rdi, rdi
        je      .err
        mov     rax, qword [rdi+list.first]
.loop:
        test    rax, rax
        je      .zero
        mov     rdx, qword [rax+node.next]
        mov     qword [rax+node.prev], 0
        mov     qword [rax+node.next], 0
        mov     dword [rax+node.data], 0
        mov     rax, rdx
        jmp     .loop
.zero:
        mov     qword [rdi+list.first], 0
        mov     qword [rdi+list.last], 0
.err:
        ret
section .data
currm:
        dq 0
m:
        times list_size db 0
curridx:
        dq 0
glob:
        times node_size*0x10 db 0