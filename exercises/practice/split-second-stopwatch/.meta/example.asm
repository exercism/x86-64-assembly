default rel

ready equ 0
running equ 1
stopped equ 2

success equ 0
already_running equ 1
not_running equ 2
not_stopped equ 3

section .bss
    crt_state resb 1
    laps resb 90
    current_lap_index resq 1
    total_time resb 9

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

%macro get_to_current_string 0
    lea rdi, [laps]
    add rdi, qword [current_lap_index]
%endmacro

%macro set_initial_timer 0
%rep 2
    mov al, '0'
    times 2 stosb

    mov al, ':'
    stosb
%endrep
    mov al, '0'
    times 2 stosb
%endmacro

%macro accumulates_time 0
    ; handle seconds

    xor rax, rax
    xor r9, r9

    ; gets destringified input seconds

    mov al, byte [r8 + 6]
    sub al, '0'
    imul rax, rax, 10
    add al, byte [r8 + 7]
    sub rax, '0'

    ; gets destringified current lap seconds

    mov r9b, byte [rdi + 6]
    sub r9, '0'
    imul r9, r9, 10
    add r9b, byte [rdi + 7]
    sub r9, '0'

    ; adds both and gets minutes to be added and remaining seconds

    add rax, r9
    xor rdx, rdx
    mov r10, 60
    div r10

    mov r11, rdx ; remaining seconds
    mov r10, rax ; extra minutes

    ; handle minutes

    xor rax, rax
    xor r9, r9

    ; gets destringified input minutes

    mov al, byte [r8 + 3]
    sub al, '0'
    imul rax, rax, 10
    add al, byte [r8 + 4]
    sub rax, '0'

    ; gets destringified current lap minutes

    mov r9b, byte [rdi + 3]
    sub r9b, '0'
    imul r9, r9, 10
    add r9b, byte [rdi + 4]
    sub r9, '0'

    ; adds both and gets hours to be added and remaining minutes

    add rax, r9
    add rax, r10
    xor rdx, rdx
    mov r9, 60
    div r9

    mov r10, rdx ; remaining minutes
    mov r9, rax ; extra hours

    ; handle hours

    xor rax, rax

    ; gets destringified input hours

    mov al, byte [r8]
    sub al, '0'
    imul rax, rax, 10
    add al, byte [r8 + 1]
    sub rax, '0'

    xor rdx, rdx

    ; gets destringified current lap hours

    mov dl, byte [rdi]
    sub dl, '0'
    imul rdx, rdx, 10
    add dl, byte [rdi + 1]
    sub rdx, '0'

    ; adds both and gets remaining hours

    add rax, rdx
    add rax, r9
    xor rdx, rdx
    mov r9, 24
    div r9

    mov r9, rdx ; remaining hours
    xor rax, rax ; discard days
%endmacro

%macro stringify 1
    mov rax, %1
    xor rdx, rdx
    mov %1, 10
    div %1

    add al, '0'
    add dl, '0'
%endmacro

%macro sum_timers 0
    accumulates_time

    stringify r11 ; stringify seconds

    mov byte [r8 + 6], al
    mov byte [r8 + 7], dl

    stringify r10 ; stringify minutes

    mov byte [r8 + 3], al
    mov byte [r8 + 4], dl

    stringify r9 ; stringify hours

    mov byte [r8], al
    mov byte [r8 + 1], dl
%endmacro

new:
    ; No arguments
    ; Return is void

    ; This function zero-initializes all variables
    ; It returns success, although it's return is void, to allow for tail-call from reset

    mov byte [crt_state], ready
    mov rcx, 90
    lea rdi, [laps]
.initialize_loop:
    mov byte [rdi + rcx - 1], 0
    loop .initialize_loop

    mov qword [current_lap_index], 0

    get_to_current_string
    set_initial_timer

    mov rax, success
    ret

start:
    ; No arguments
    ; Return is an error_t enum

    ; If timer is already running, result is an error
    ; Otherwise sets current state to running and returns success

    cmp byte [crt_state], running
    je .error

    mov rax, success
    mov byte [crt_state], running

    ret
.error:
    mov rax, already_running
    ret

stop:
    ; No arguments
    ; Return is an error_t enum

    ; If timer is not running, result is an error
    ; Otherwise sets current state to stopped and returns success

    cmp byte [crt_state], running
    jne .error

    mov rax, success
    mov byte [crt_state], stopped

    ret
.error:
    mov rax, not_running
    ret

reset:
    ; No arguments
    ; Return is an error_t enum

    ; If timer is not stopped, result is an error
    ; Otherwise zero-initializes timer by jumping to new

    cmp byte [crt_state], stopped
    jne .error

    jmp new
.error:
    mov rax, not_stopped
    ret

state:
    ; No arguments
    ; Return is a state_t enum

    ; Simply returns crt_state

    mov al, [crt_state]
    ret

lap:
    ; No arguments
    ; Return is an error_t enum

    ; If timer is not running, result is an error
    ; Otherwise increases current lap index to get a new timer position in laps array
    ; and zero-initializes this new timer
    ; Previous timers are stored in previous positions of laps array

    cmp byte [crt_state], running
    jne .error

    add qword [current_lap_index], 9 ; index increased by 9, although chars are stored on just first 8 bytes
                                     ; since laps array is zero-initialized, this makes sure all strings are NULL-ended

    get_to_current_string
    set_initial_timer

    mov rax, success
    ret
.error:
    mov rax, not_running
    ret

current_lap:
    ; No arguments
    ; Return is a string

    ; Since strings in laps array are NULL-ended
    ; it's just a matter of loading current string into rax

    lea rax, [laps]
    add rax, qword [current_lap_index]
    ret

previous_laps:
    ; RDI - output buffer of strings
    ; return is size of output buffer in RAX

    xor rax, rax

    cmp qword [current_lap_index], 0
    je .empty ; If current lap index is 0, function lap wasn't called yet
              ; So there's no previous lap and output buffer is empty

    ; Otherwise, stores all previous strings (stored in laps)
    ; And returns current lap index / 9, which is the number of previous strings

    mov rax, qword [current_lap_index]
    xor rdx, rdx
    mov r8, 9
    div r8

    xor r8, r8
    mov r10, rax
    mov rcx, rax
.fill_buffer:
    lea rax, [laps]
    add rax, r8
    add r8, 9

    stosq
    inc rax

    loop .fill_buffer

    mov rax, r10
.empty:
    ret


advance_time:
    ; RDI - input string of form "xx:xx:xx" where x is a digit
    ; Return is void

    cmp byte [crt_state], stopped
    je .end_advance ; If timer is stopped, timer is not advanced
    ; Otherwise, proceeds with algorithm

    ; Algorithm is:
    ;
    ; Gets destringified seconds from input string
    ; Accumulates seconds in RAX and divides by 60
    ; Resulting seconds is the remainder, in RDX
    ; Minutes to be added is the quotient, in RAX
    ;
    ; Gets destringified minutes from input string
    ; Accumulates minutes in RAX, adds minutes to be addded and divides by 60
    ; Resulting minutes is the remainder, in RDX
    ; Hours to be added is the quotient, in RAX
    ;
    ; Gets destringified hours from input string
    ; Accumulates hours in RAX, adds hours to be added and divides by 24
    ; Resulting hours is the remainder, in RDX
    ; Days are discarded
    ;
    ; Stringify seconds, minutes and hours and add them to the string in laps
    ; which is located in current lap index

    lea r8, [laps]
    add r8, qword [current_lap_index]

    sum_timers

.end_advance:
    ret

total:
    ; No arguments
    ; Return is a string in rax

    lea rdi, [total_time]
    set_initial_timer

    mov rcx, -9
.main_loop:
    add rcx, 9

    lea r8, [total_time]
    lea rdi, [laps]
    add rdi, rcx

    sum_timers

    cmp rcx, qword [current_lap_index]
    jl .main_loop

    lea rax, [total_time]
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
