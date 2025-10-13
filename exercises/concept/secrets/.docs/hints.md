# Hints

## General

- 8-bit integers are returned in `al`.
- 16-bit integers are returned in `ax` and passed in `di`.
- If a called function modifies a register, you need to save any value in that register that will be used later.

## 1. Extract the mask

- There is an instruction that can be used to shift bits to the left a number of positions.

## 2. Extract the message

- 8-bit integers are returned in `al`.

## 3. Extract redundant bits

- You may use the previously defined `extract_higher_bits` and `extract_lower_bits`.
- There is an instruction that sets bits if they are set in both of two values.

## 4. Set bits

- You may use the previously defined `extract_higher_bits` and `extract_lower_bits`.
- There is an instruction that sets bits if they are set in either of two values, including both.

## 5. Rotate private key

- You may use the previously defined `extract_higher_bits` and `extract_lower_bits`.
- A constant integer can be defined at the top of the file using `equ`.
- There is an instruction that can be used to get the number of bits set in a 16-bit number.
- The [movzx][movzx] instruction can be used to convert a 8-bit number in a 16-bit number, clearing all extra bits.
- There is an instruction that can be used to rotate bits to the left by a number of positions given by a 8-bit value in `cl`.

## 6. Format private key

- You may use the previously defined `rotate_private_key`, `extract_higher_bits` and `extract_lower_bits`.
- There is an instruction that sets a bit if it is set in only one of two values, not in both.
- There is an instruction to flip all bits in a number.

## 7. Finish decryption

- You may use the previously defined `set_bits` and `format_private_key`.
- The [movzx][movzx] instruction can be used to convert a 8-bit number in a 16-bit number, clearing all extra bits.
- There is an instruction that can be used to shift bits to the left a number of positions.
- There is an instruction that sets bits if they are set in either of two values, including both.

[movzx]: https://www.felixcloutier.com/x86/movzx
