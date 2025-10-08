# Hints

## General

- The six first integer arguments are passed to a function in `rdi`, `rsi`, `rdx`, `rcx`, `r8` and `r9`.
- For accessing less than 64 bits on those registers, you can refer to [AMD's Manual][manual] for the appropriate name.

## 1. Define `get_box_weight`

- There is an [instruction][movzx] for zero-extending values.

## 2. Define `max_number_of_boxes`

- There is an [instruction][div] for unsigned division.

## 3. Define `items_to_be_moved`

- Subtraction works the same way for unsigned and signed numbers.

## 4. Define `calculate_payment`

- There is an [instruction][cqo] for sign-extending values from `rax` into `rdx`.
- There is an [instruction][idiv] for signed division.
- The payment is split between you and a certain number of workers and you also get the remainder.
- The remainder of a division is stored in `rdx`.

[manual]: https://docs.amd.com/v/u/en-US/24592_3.24#page=62
[movzx]: https://www.felixcloutier.com/x86/movzx
[cqo]: https://www.felixcloutier.com/x86/cwd:cdq:cqo
[div]: https://www.felixcloutier.com/x86/div
[idiv]: https://www.felixcloutier.com/x86/idiv
