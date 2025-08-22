## x86-64 Assembly Specific Notes

The functions in this exercise accept an array containing one or more numbers, each representing one 'game score'.

In x86-64 assembly, elements in an array are accessed as an offset in bytes from a base pointer.

This base pointer is passed in a register, according to the [System V AMD64 ABI Calling Convention](https://www.uclibc.org/docs/psABI-x86_64.pdf).

The first 3 arguments are passed in rdi, rsi, rdx, in this order.

As the player's game scores are represented as 32-bit integers, which take 4 bytes, they can be read from

| `rsi`   |
|---|
| `dword [rsi]` |
| `dword [rsi + 4]` |
| ... |
| `dword [rsi + 4*scores_count - 4]` |

`personal_top_three()` should write the player's top scores to a buffer, also passed in a register and accessed in the same way.

| `rdi`   |
|---|
| `dword [rdi]` |
| `dword [rdi + 4]` |
| ... |

Integer values, by convention, are returned in the rax register.
