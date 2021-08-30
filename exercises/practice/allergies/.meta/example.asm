;
; Given a person's allergy score, determine whether or not they're allergic to
; a given item.
;
; Parameters:
;   rdi - item
;   rsi - score
; Returns:
;   rax - true if allergic, else false
;
section .text
global allergic_to
allergic_to:
    xor eax, eax ; Set return value
    bt esi, edi  ; Select the bit in score at the bit-position represented by the item
    setc al      ; Return true if the bit is set, else false
    ret

;
; Given a person's allergy score, determine their full list of allergies.
;
; Parameters:
;   rdi - score
;   rsi - list
;
global list
list:
    mov rcx, rsi                  ; Save list
    mov esi, edi                  ; Set score
    xor edx, edx                  ; Set current list index

    xor edi, edi                  ; Set current item
.loop_start:
    call allergic_to
    test al, al                   ; Check if allergic to item
    je .next                      ; If not, process next item
    mov [rcx + rdx * 4 + 4], edi  ; Add item to list
    inc edx                       ; Increment current list index
.next:
    inc edi                       ; Advance to next item
    cmp edi, 8                    ; See if we reached the last item
    jne .loop_start               ; If items remain, loop back

    mov [rcx], edx                ; Set list size
    ret
