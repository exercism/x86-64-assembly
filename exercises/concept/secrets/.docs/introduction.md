# Introduction

## Bit Manipulation

Each bit of an integer can be used to store a binary value.
Because many situations involve binary information, such as true or false, inclusion or exclusion, on or off, the binary representation of an N-bit integer provides a compact way to encode the binary state of N items.
This makes the ability to manipulate bits and bytes essential in assembly.
The x86-64 instruction set offers a wide variety of bitwise manipulation instructions.

### Single Bit Manipulation

These instructions work on single bits in an operand.

They all take two operands, the second indicates the index of the bit being operated in the first operand.
All of them copy the selected bit into the **carry flag (CF)**.

| Name  | Description                                                                   |
|-------|-------------------------------------------------------------------------------|
| `bt`  |copies the bit into `CF` without modifying any operand                         |
| `bts` |copies the bit into `CF` and sets it in the destination operand                |
| `btr` |copies the bit into `CF` and clears it in the destination operand              |
| `btc` |copies the bit into `CF` and complements (flips) it in the destination operand |

### Bitwise Operations

Bitwise operations are performed on all bits of an operand.

They all have an instruction with the same name as the performed bitwise operation:

| Name   | Description                                  |
|--------|----------------------------------------------|
| `and`  |1 if both bits are 1                          |
| `or`   |1 if at least one of the bits is 1            |
| `xor`  |1 if the bits differ                          |
| `not`  |1 if bit was 0; 0 if bit was 1                |

Most of them take two operands, perform a bitwise operation on both and store the result in the destination operand.
The exception is `not`, which takes just one destination operand.

### Masks

When we interpret one and zero as inclusion and exclusion, respectively, an integer is called a _bitmask_ (or simply a _mask_).

A bitmask "masks out" items because a zero in the `i`-th bit excludes the `i`-th item, while a one includes it.
We also commonly use a bitmask to include certain bits of an integer while excluding others.

For example, let `A` be an integer whose binary representation is:

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 1 | 0 | 0 | 1 | 0 | 1 | 0 | 1 |

Also, let `M` be an integer whose binary representation is:

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 1 |

Both are `8`-bit integers.
In this case, we can say that `M` selects bits `0`, `2` and `3` of `A`, and excludes the rest.

The bitwise instructions discussed earlier are useful in manipulating integers with masks.
For example:

- To *clear* the bits of `A` that are not selected by `M`, take the bitwise AND: `A AND M`.
- To *set* the bits of `A` selected by `M`, take the bitwise OR: `A OR M`.

### TEST Instruction

The `test` instruction makes a bitwise AND between both operands and sets flags according to the result.

If A is the first operand and B, the second:

| flag | set when                   |
|:----:|:---------------------------|
| `CF` | always cleared             |
| `ZF` | A AND B == 0               |
| `SF` | sign bit of A AND B is set |
| `OF` | always cleared             |

This instruction takes two operands and updates the flags, but **does not modify its operands**.

### Shift Operations

These instructions move the bits in the destination operand by a number of positions specified by the second operand.
The second operand must be a constant number (an `immediate`) or the register `cl` (the lowest `8` bits of `rcx`).

| Name        | Description              |
|-------------|--------------------------|
| `shl`/`sal` | Shifts bits to the left  |
| `shr`/`sar` | Shifts bits to the right |

Note that the count in the second operand is masked to `5` bits, or `6` bits with a `64`-bit destination operand.
Any bit after that is effectively ignored.
This means the maximum shift is `31`, or `63` with a `64`-bit operand.

#### Shl / Sal

Both `shl` and `sal` perform the exact same operation, one is an alias of the other.

Whenever a shift left is made, bits closer to the end of the sequence than the length of the shift are first moved to `CF` and then discarded.
On the other hand, a number of new cleared bits equal to the length of the shift is added to the beginning.

Since each bit in an integer represents a power of `2`, a shift to the left by n positions has the effect of multiplying the integer by `2ⁿ`.

#### Shr / Sar

There are two instructions to move bits to the right: `shr` and `sar`.

Whenever any of the two instructions is used, bits closer to the start of the sequence than the length of the shift are first moved to `CF` and then discarded.
On the other hand, a number of new bits equal to the length of the shift is added to the end.

The difference between them is that `shr` moves `0` bits to the left end, while `sar` moves `1` if the most significant was set and `0` otherwise.
This means that `sar` preserves the sign in the shift of a signed integer.

Since each bit in an integer represents a power of `2`, a shift to the right by n positions using `shr` has the effect of making an *unsigned* division by `2ⁿ`.

Similarly, a shift to the right by n positions using `sar` has the effect of making a *signed* division by `2ⁿ`.

### Rotation Operations

These instructions move the bits in the destination operand by a number of positions specified by the second operand.
The second operand must be a constant number (an `immediate`) or the register `cl` (the lowest `8` bits of `rcx`).

The difference between a rotation and a shift is that a rotation does not discard or add any bits.
Bits that would be discarded by a shift are instead moved to the opposite end.
So, all bits remain, they all change places.

| Name    | Description                |
|---------|----------------------------|
| `rol`   | Rotates bits to the left   |
| `ror`   | Rotates bits to the right  |

Note that the count in the second operand is masked to `5` bits, or `6` bits with a `64`-bit destination operand.
Any bit after that is effectively ignored.
This means the maximum rotation is `31`, or `63` with a `64`-bit operand.

### Other Bit Manipulation Instructions

There are other useful bit manipulation instructions:

| Name       | Description                                                                                          |
|------------|------------------------------------------------------------------------------------------------------|
| `popcnt`   | Counts the number of bits set                                                                        |
| `bsr`      | Gets the index of the most significant set bit. If no bit is set, result is undefined                |
| `bsf`      | Gets the index of the least significant set bit. If no bit is set, result is undefined               |

These instructions all work with two `16`-bit, `32`-bit or `64`-bit operands.
They can not be used with `8`-bit operands.
