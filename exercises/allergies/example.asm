;
; Given a person's allergy score, determine whether or not they're allergic to
; a given item.
;
; Parameters:
;   rdi - item
;   rsi - score
;
; Returns:
;   rax - 1 if allergic, else 0
;
section .text
global allergic_to
allergic_to:
    bt esi, edi                     ; Test if item bit is set in score
    setc al                         ; Set return value
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
    mov rdx, rsi                    ; Save list
    mov esi, edi                    ; Set score argument

    xor edi, edi                    ; Set item argument
    xor ecx, ecx                    ; Set current list index
.loop_start:
    call allergic_to
    test al, al                     ; Allergic to item?
    je .skip                        ; No => skip item
    mov [rdx + rcx * 4 + 4], edi    ; Add item to list
    inc ecx                         ; Increment current list index
.skip:
    inc edi                         ; Next item
    cmp edi, 8                      ; Last item?
    jne .loop_start                 ; No => next iteration

    mov [rdx], ecx                  ; Set list size
    ret
