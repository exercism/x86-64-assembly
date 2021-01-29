default rel

section .rodata
msg: db "", 0

section .text
global hello
hello:
    lea rax, [msg]
    ret
