# Introduction

As there is no built-in data structure and very few abstractions in assembly, the ability to manipulate bits and bytes is essential.

This is why x86-64 offers a variety of different instructions for bit manipulations.

## Single bit manipulation

These instructions work on single bits in a operand.

They all take two operands, the second indicates the index of the bit being operated in the first operand.
All of them copy the selected bit into the `carry flag (CF)`.

| Name | Description                                                                   |
|------|-------------------------------------------------------------------------------|
|bt    |copies the bit into `CF` without modifying any operand                         |
|bts   |copies the bit into `CF` and sets it in the destination operand                |
|btr   |copies the bit into `CF` and clears it in the destination operand              |
|btc   |copies the bit into `CF` and complements (flips) it in the destination operand |

## Bitwise operations

Bitwise operations are performed in all bits of an operand.

They all have an instruction with the same name as the performed bitwise operation:

| Name   | Description                                  |
|--------|----------------------------------------------|
|and     |1 if both bits are 1                          |
|or      |1 if at least one of the bits is 1            |
|xor     |1 if the bits differ                          |
|not     |1 if bit was 0; 0 if bit was 1                |

Most of them take two operands, perform a bitwise operation on both and store the result in the destination operand.
The exception is `not`, which takes just one destination operand.

## Shift operations

These instructions move the bits in the destination operand by a number of positions specified by the second operand.
The second operand must be a constant number (an `immediate`) or the register `cl` (the lowest 8 bits of `rcx`).

| Name    | Description             |
|---------|-------------------------|
|shl/sal  |Shifts bits to the left  |
|shr/sar  |Shifts bits to the right |

### Shl / Sal

Both `shl` and `sal` perform the exact same operation, one is an alias of the other.

Whenever a shift left is made, bits closer to the end of the sequence than the length of the shift are first moved to the `carry flag (CF)` and then discarded.
On the other hand, a number of new cleared bits equal to the length of the shift is added to the beginning.

Since each bit in an integer represents a power of 2, a shift to the left by n positions has the effect of multiplying the integer by 2ⁿ.

### Shr/Sar

There are two instructions to move bits to the right: `shr` and `sar`.

Whenever any of the two instructions is used, bits closer to the start of the sequence than the length of the shift are first moved to the `carry flag (CF)` and then discarded.
On the other hand, a number of new bits equal to the length of the shift is added to the end.

The difference between them is that `shr` moves `0` bits to the left end, while `sar` moves `1` if the most significant was set and `0` otherwise.
This means that `sar` preserves the sign in the shift of a signed integer.

Since each bit in an integer represents a power of 2, a shift to the right by n positions using `shr` has the effect of making an *unsigned* division by 2ⁿ.

Similarly, a shift to the right by n positions using `sar` has the effect of making a *signed* division by 2ⁿ.

## Rotation Operations

These instructions move the bits in the destination operand by a number of positions specified by the second operand.
The second operand must be a constant number (an `immediate`) or the register `cl` (the lowest 8 bits of `rcx`).

The difference between a rotation and a shift is that a rotation does not discard or add any bits.
Bits that would be discarded by a shift are instead moved to the opposite end.
So, all bits remain, they all change places.

| Name    | Description               |
|---------|---------------------------|
|rol      |Rotates bits to the left   |
|ror      |Rotates bits to the right  |

There are variants for both of those instructions that use the `carry flag (CF)` as an extra bit in the rotation:

| Name    | Description                                   |
|---------|-----------------------------------------------|
|rcl      |Rotates bits to the left, including the `CF`   |
|rcr      |Rotates bits to the right, including the `CF`  |

This means that a bit at one end of the sequence is first moved to the flag before going to the other end of the sequence.
At the same time, the previous value in the flag is moved to the bit that would receive the one moved to the flag.

So, the `CF` works as an extra bit to the left in the case of `rcr` and as an extra bit to the right in the case of `rcl`.

## Other bit manipulation instructions

There are other useful bit manipulation instructions:

| Name     | Description                                                                            |
|----------|----------------------------------------------------------------------------------------|
| popcnt   | Counts the number of bits set                                                          |
| lzcnt    | Counts the number of leading zeros (a bit cleared before the first set bit)            |
| bsr      | Gets the index of the most significant set bit. If no bit is set, result is undefined  |
| bsf      | Gets the index of the least significant set bit. If no bit is set, result is undefined |

These instructions all work with two 16-bit, 32-bit or 64-bit operands.
They can not be used with 8-bit operands.
