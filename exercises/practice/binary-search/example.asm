;
; Implement a binary search algorithm.
;
; Parameters:
;   rdi - array
;   rsi - size
;   rdx - value
; Returns:
;   rax - the position of value, or -1 if not found
;
section .text
global find
find:
    mov eax, -1              ; Initialize return value
    test esi, esi            ; Check if array is empty
    je .loop_end             ; If empty, return -1

    xor ecx, ecx             ; Set left boundary to 0
    lea r8d, [rsi - 1]       ; Set right boundary to size - 1
    cmp ecx, r8d             ; Compare left and right boundaries
    jg .loop_end             ; If left is greater than right, return -1
.loop_start:
    lea r9d, [rcx + r8]      ; Set the position of the middle element to left + right
    sar r9d, 1               ; Divide by 2
    cmp [rdi + r9 * 4], edx  ; Compare with target value
    jl .less                 ; If less, go to .less
    jg .greater              ; If greater, go to .greater
    mov eax, r9d             ; Return the position of the middle element
    ret
.less:
    lea ecx, [r9 + 1]        ; Set left boundary to middle + 1
    jmp .next
.greater:
    lea r8d, [r9 - 1]        ; Set right boundary to middle - 1
.next:
    cmp ecx, r8d             ; Compare left and right boundaries
    jle .loop_start          ; If left is less or equal to right, loop back

.loop_end:
   ret
