;
; Implement a binary search algorithm.
;
; Parameters:
;   rdi - array
;   rsi - size
;   rdx - value
;
; Returns:
;   rax - the position of value
;
section .text
global find
find:
    mov eax, -1                ; Set return value
    test esi, esi              ; Is array NULL?
    je .loop_end               ; Yes => skip loop

    xor ecx, ecx               ; Set left boundary to 0
    lea r8d, [rsi - 1]         ; Set right boundary to n - 1
    cmp ecx, r8d               ; Is left greater than right?
    jg .loop_end               ; Yes => skip loop
.loop_start:
    lea r9d, [ecx + r8d]       ; Set middle to left + right
    sar r9d, 1                 ; Divide middle by 2
    cmp [rdi + r9 * 4], edx    ; Is the middle array element less than value?
    jl .less                   ; Yes => go to .less
    cmp [rdi + r9 * 4], edx    ; Is the middle array element greater than value?
    jg .greater                ; Yes => go to .greater
    mov eax, r9d               ; Return middle
    ret
.less:
    lea ecx, [r9 + 1]          ; Set left boundary to middle + 1
    jmp .next
.greater:
    lea r8d, [r9 - 1]          ; Set right boundary to middle - 1
.next:
    cmp ecx, r8d               ; Is left less or equal to right?
    jle .loop_start            ; Yes => next iteration

.loop_end:
   ret
