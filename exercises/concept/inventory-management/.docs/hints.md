# Hints

## 1. Define `get_box_weight`

- There is an [instruction][movzx] for zero-extending values.

## 2. Define `max_number_of_boxes`

- There is an [instruction][div] for unsigned division.

## 3. Define `items_to_be_moved`

- Subtraction works the same way for unsigned and signed numbers.

## 4. Define `calculate_payment`

- There is an [instruction][cqo] for sign-extending values from `rax` into `rdx`.
- There is an [instruction][idiv] for signed division.

[movzx]: https://www.felixcloutier.com/x86/movzx
[cqo]: https://www.felixcloutier.com/x86/cwd:cdq:cqo
[div]: https://www.felixcloutier.com/x86/div
[idiv]: https://www.felixcloutier.com/x86/idiv
