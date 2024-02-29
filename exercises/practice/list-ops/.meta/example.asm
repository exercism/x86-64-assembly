;
; Add all items in the second array to the end of the first array.
;
; Parameters:
;   rdi - first array
;   rsi - number of items in the first array
;   rdx - second array
;   rcx - number of items in the second array
;   r8  - result array
; Returns:
;   rax - the number of items in the result array
;
section .text
global append
append:
    mov rax, rsi
    add rax, rcx                ; Set return value

    mov r9, rcx                 ; Save number of items in second array

    mov rcx, rsi                ; Set first array length
    mov rsi, rdi                ; Set source to first array
    mov rdi, r8                 ; Set destination to result array
    rep movsd                   ; Append items from first array

    mov rsi, rdx                ; Set source to second array
    mov rcx, r9                 ; Set second array length
    rep movsd                   ; Append items from second array

    ret

;
; Return all items for which the predicate is true.
;
; Parameters:
;   rdi - array
;   rsi - number of items in the array
;   rdx - predicate
;   rcx - result array
; Returns:
;   rax - the number of items in the result array
;
global filter
filter:
    push rbx                    ; Save caller's registers
    push r12
    push r13
    push r14
    push r15

    xor rbx, rbx                ; Initialize number of filtered items

    cmp rsi, 0                  ; Check if input array is empty
    je .loop_end                ; If empty, skip loop

    mov r12, rdi                ; Save input array
    mov r13, rsi                ; Save input array length
    mov r14, rdx                ; Save predicate
    mov r15, rcx                ; Save result array
.loop_start:
    mov edi, dword [r12]        ; Read value from array
    call r14                    ; Call predicate
    test al, al                 ; Check if predicate is true
    jz .next                    ; If not, process next item

    inc rbx                     ; Increment number of filtered items
    mov eax, dword [r12]
    mov dword [r15], eax        ; Copy filtered item to result array
    add r15, 4                  ; Advance result array to next item
.next:
    add r12, 4                  ; Advance input array to next item
    dec r13                     ; Decrement remaining number of items
    cmp r13, 0                  ; See if we reached the end
    jne .loop_start             ; If items remain, loop back

.loop_end:
    mov rax, rbx                ; Set return value

    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx                     ; Restore caller's registers

    ret

;
; Return the results of applying the transform function on all items.
;
; Parameters:
;   rdi - array
;   rsi - number of items in the array
;   rdx - transform function
;   rcx - result array
; Returns:
;   rax - the number of items in the result array
;
global map
map:
    push rbx                    ; Save caller's registers
    push r12
    push r13
    push r14
    push r15

    mov rbx, rsi                ; Set return value

    cmp rsi, 0                  ; Check if input array is empty
    je .loop_end                ; If empty, skip loop

    mov r12, rdi                ; Save input array
    mov r13, rsi                ; Save input array length
    mov r14, rdx                ; Save transform function
    mov r15, rcx                ; Save result array
.loop_start:
    mov edi, dword [r12]        ; Read value from array
    call r14                    ; Call transform function
    mov dword [r15], eax        ; Copy transformed item to result array

    add r12, 4                  ; Advance input array to next item
    add r15, 4                  ; Advance result array to next item
    dec r13                     ; Decrement remaining number of items
    cmp r13, 0                  ; See if we reached the end
    jne .loop_start             ; If items remain, loop back

.loop_end:
    mov rax, rbx                ; Set return value

    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx                     ; Restore caller's registers

    ret

;
; Fold (reduce) each item into the accumulator from the left.
;
; Parameters:
;   rdi - array
;   rsi - number of items in the array
;   rdx - initial value
;   rcx - accumulator function
; Returns:
;   rax - the folded (reduced) value
;
global foldl
foldl:
    push rbx                    ; Save caller's registers
    push r12
    push r13
    push r14

    mov rbx, rdx                ; Initialize return value

    cmp rsi, 0                  ; Check if input array is empty
    je .loop_end                ; If empty, skip loop

    mov r12, rdi                ; Save input array
    mov r13, rsi                ; Save input array length
    mov r14, rcx                ; Save accumulator function
.loop_start:
    mov rdi, rbx
    mov esi, dword [r12]        ; Read value from array
    call r14                    ; Call accumulator function
    mov rbx, rax                ; Update return value

    add r12, 4                  ; Advance input array to next item
    dec r13                     ; Decrement remaining number of items
    cmp r13, 0                  ; See if we reached the end
    jne .loop_start             ; If items remain, loop back

.loop_end:
    mov rax, rbx                ; Set return value

    pop r14
    pop r13
    pop r12
    pop rbx                     ; Restore caller's registers

    ret

;
; Fold (reduce) each item into the accumulator from the right.
;
; Parameters:
;   rdi - array
;   rsi - number of items in the array
;   rdx - initial value
;   rcx - accumulator function
; Returns:
;   rax - the folded (reduced) value
;
global foldr
foldr:
    push rbx                    ; Save caller's registers
    push r12
    push r13
    push r14

    mov rbx, rdx                ; Initialize return value

    cmp rsi, 0                  ; Check if input array is empty
    je .loop_end                ; If empty, skip loop

    lea r12, [rdi + 4*rsi - 4]  ; Save end of input array
    mov r13, rsi                ; Save input array length
    mov r14, rcx                ; Save accumulator function
.loop_start:
    mov rdi, rbx
    mov esi, dword [r12]        ; Read value from array
    call r14                    ; Call accumulator function
    mov rbx, rax                ; Update return value

    sub r12, 4                  ; Advance input array to previous item
    dec r13                     ; Decrement remaining number of items
    cmp r13, 0                  ; See if we reached the end
    jne .loop_start             ; If items remain, loop back

.loop_end:
    mov rax, rbx                ; Set return value

    pop r14
    pop r13
    pop r12
    pop rbx                     ; Restore caller's registers

    ret

;
; Reverses the order of items in the array.
;
; Parameters:
;   rdi - array
;   rsi - number of items in the array
;   rdx - result array
; Returns:
;   rax - the number of items in the result array
;
global reverse
reverse:
    mov rax, rsi                ; Set return value

    cmp rsi, 0                  ; Check if input array is empty
    je .loop_end                ; If empty, skip loop

    lea rcx, [rdx + 4*rsi - 4]  ; Set end of the result array
.loop_start:
    mov edx, dword [rdi]        ; Read value from array
    mov dword [rcx], edx        ; Write value to result array

    add rdi, 4                  ; Advance input array to next item
    sub rcx, 4                  ; Advance result array to previous item
    dec rsi                     ; Decrement remaining number of items
    cmp rsi, 0                  ; See if we reached the end
    jne .loop_start             ; If items remain, loop back

.loop_end:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
