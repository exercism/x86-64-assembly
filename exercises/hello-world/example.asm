default rel

section .data
msg: db "Hello, World!", 0

;
; The classical introductory exercise. Just say "Hello, World!"
;
; Returns:
;   rax - msg
;
section .text
global hello
hello:
    lea rax, [msg]    ; Set return value
    ret
