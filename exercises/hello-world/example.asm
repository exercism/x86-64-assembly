section .data
msg: db "Hello, World!", 0

;
; The classical introductory exercise. Just say "Hello, World!".
;
; Returns:
;   rax - msg
;
section .text
global hello
hello:
    mov rax, msg    ; Set return value
    ret
