default rel

section .bss

section .text

global new
global start
global stop
global reset
global state
global lap
global current_lap
global previous_laps
global advance_time
global total

new:
    ; Provide your implementation here
    ret

start:
    ; Provide your implementation here
    ret

stop:
    ; Provide your implementation here
    ret

reset:
    ; Provide your implementation here
    ret

state:
    ; Provide your implementation here
    ret

lap:
    ; Provide your implementation here
    ret

current_lap:
    ; Provide your implementation here
    ret

previous_laps:
    ; Provide your implementation here
    ret

advance_time:
    ; Provide your implementation here
    ret

total:
    ; Provide your implementation here
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
