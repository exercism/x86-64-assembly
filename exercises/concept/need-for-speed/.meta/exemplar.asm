default rel

TRUE equ 1
FALSE equ 0

CAR_T_SIZE equ 16
TRACK_T_SIZE equ 16
RACE_T_SIZE equ 120

MAX_PARTICIPATING_CARS equ 6
MAX_RACES_IN_TOURNAMENT equ 20

section .rodata
    START_BATTERY dd 100.0

section .text

global new_car
new_car:
    lodsq
    mov edx, dword [START_BATTERY]
    shl rdx, 16
    mov dx, di
    shl rdx, 16
    mov dx, word [rsi]
    ret

global new_track
new_track:
    mov eax, edi
    mov rdx, rsi
    ret

global new_race
new_race:
    mov qword [rdi], rsi
    mov qword [rdi + 8], rdx
    mov byte [rdi + TRACK_T_SIZE], cl
    mov byte [rdi + 20 + MAX_PARTICIPATING_CARS*CAR_T_SIZE], 0
    mov rax, rdi
    ret

global add_participant
add_participant:
    movzx rcx, byte [rdi + 20 + MAX_PARTICIPATING_CARS*CAR_T_SIZE]
    cmp rcx, MAX_PARTICIPATING_CARS
    je .false

    inc byte [rdi + 20 + MAX_PARTICIPATING_CARS*CAR_T_SIZE] ; increase counter
    shl rcx, 4 ; index in bytes is index in elements multiplied by 16
    mov qword [rdi + 20 + rcx], rsi
    mov qword [rdi + 28 + rcx], rdx
    mov al, TRUE
    ret

.false:
    mov al, FALSE
    ret

global add_race
add_race:
    mov rcx, qword [rdi + MAX_RACES_IN_TOURNAMENT*RACE_T_SIZE] ; current length
    inc qword [rdi + MAX_RACES_IN_TOURNAMENT*RACE_T_SIZE] ; increase length counter
    imul rcx, rcx, RACE_T_SIZE ; index in bytes is index in elements multiplied by RACE_T_SIZE
    lea rdi, [rdi + rcx]
    lea rsi, [rsp + 8]
    mov rcx, RACE_T_SIZE
    rep movsb
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
