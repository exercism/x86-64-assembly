section .text

global add_bonus
add_bonus:
    ; TODO: implement the `add_bonus` function
    ;
    ; This function takes two 64-bit signed integers as arguments, in order:
    ; 1. `total`: the current score total (always between `0` and `999999`)
    ; 2. `bonus`: the bonus to add (always non-negative)
    ;
    ; The return value is `total + bonus` if that sum is less than or equal to `999999`, and `999999` otherwise
    ; The return value is a 64-bit signed integer
    ;
    ; The code for the task should be branchless.
    ; Use `cmovcc`, `setcc`, and arithmetic instead of conditional jumps.
    ret

global compare_scores
compare_scores:
    ; TODO: implement the `compare_scores` function
    ;
    ; This function takes two 64-bit signed integers as arguments
    ;
    ; It should return
    ; - `+1` if the first score is _higher_
    ; - `-1` if the first score is _lower_
    ; - `0` if the two scores are _equal_
    ;
    ; The return value is a 64-bit signed integer
    ;
    ; The code for the task should be branchless.
    ; Use `cmovcc`, `setcc`, and arithmetic instead of conditional jumps.
    ret

global validate_score
validate_score:
    ; TODO: implement the `validate_score` function
    ;
    ; This function takes three 64-bit signed integers as arguments, in order:
    ; 1. `score`: the raw score
    ; 2. `min`: the smallest allowed score
    ; 3. `max`: the largest allowed score
    ;
    ; It should clamp `score` between `min` and `max`
    ; This means the return value is `min` if `score < min`, `max` if `score > max`, and `score` otherwise
    ; You may assume that `min <= max`.
    ;
    ; The return value is a 64-bit signed integer
    ;
    ; The code for the task should be branchless.
    ; Use `cmovcc`, `setcc`, and arithmetic instead of conditional jumps.
    ret

global top_two
top_two:
    ; TODO: refactor the commented-out code to implement a branchless loop body
    ;
    ; This function finds the top two non-negative values in the input array and stores them in the output buffer.
    ; Those values are 64-bit signed integers and must be stored in descending order
    ;
    ; The function has no return value and takes as arguments:
    ; 1. memory address for an output buffer where the top two non-negative scores will be stored in descending order
    ; 2. input array of 64-bit signed integers
    ; 3. the number of elements in the array, as a 64-bit unsigned integer
    ;
    ; This is a refactor exercise: the commented-out code below is a working branching implementation.
    ; Replace the commented-out section with branchless code.
    ; The only jump permitted in the new code is the one that jumps back to the start of the loop to check a new element in the array.

    ; Initialization
    ; Do not modify!
    xor r8d, r8d                   ; first  = 0
    xor r9d, r9d                   ; second = 0
    xor ecx, ecx                   ; index = 0
    test rdx, rdx
    jz .done

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                       BRANCHY CODE TO REFACTOR
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;.loop:
;    mov rax, qword [rsi + 8*rcx]   ; candidate
;    inc rcx
;    cmp rax, r8
;    jle .check_second              ; candidate <= first, try second
;    mov r9, r8                     ; second = first
;    mov r8, rax                    ; first  = candidate
;    cmp rcx, rdx
;    jb .loop                       ; go to next iteration
;    jmp .done                      ; otherwise, we are done
;.check_second:
;    cmp rax, r9
;    jle .loop                      ; candidate <= second, go to next iteration
;    mov r9, rax                    ; second = candidate
;    cmp rcx, rdx
;    jb .loop                       ; go to next iteration
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; Conclusion
    ; Do not modify!
.done:
    mov qword [rdi], r8            ; save first
    mov qword [rdi + 8], r9        ; save second
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
