default rel

section .rodata
msg: db "Hello, World!", 0

;
; The classical introductory exercise. Just say "Hello, World!"
;
; Returns:
;   rax - the string "Hello, World!"
;
section .text
global hello
hello:
    lea rax, [msg]  ; Return the string "Hello, World!"
    ret
