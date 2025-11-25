# About

In a previous concept, it was explored how an `integer` in assembly is essentially a sequence of bytes interpreted in a specific way.

Each bit of an integer can be used to store a binary value. 
Because many situations involve binary information---such as true or false, inclusion or exclusion, on or off---the binary representation of an N-bit integer provides a compact way to encode the binary state of N items.
This makes the ability to manipulate bits and bytes essential in assmbly.
The x86-64 instruction set offers a wide variety of bitwise manipulation instructions.

## Single bit manipulation

These instructions work on single bits in a operand.

They all take two operands, the second indicates the index of the bit being operated in the first operand.
All of them copy the selected bit into the **carry flag (CF)**.

| Name | Description                                                                   |
|------|-------------------------------------------------------------------------------|
|bt    |copies the bit into `CF` without modifying any operand                         |
|bts   |copies the bit into `CF` and sets it in the destination operand                |
|btr   |copies the bit into `CF` and clears it in the destination operand              |
|btc   |copies the bit into `CF` and complements (flips) it in the destination operand |

## Bitwise operations

[Bitwise operations][bitwise] are performed in all bits of an operand.

They all have an instruction with the same name as the performed bitwise operation:

| Name   | Description                                  |
|--------|----------------------------------------------|
|and     |1 if both bits are 1                          |
|or      |1 if at least one of the bits is 1            |
|xor     |1 if the bits differ                          |
|not     |1 if bit was 0; 0 if bit was 1                |

Most of them take two operands, perform a bitwise operation on both and store the result in the destination operand.
The exception is `not`, which takes just one destination operand.

~~~~exercism/note
When we interpret one and zero as inclusion and exclusion, respectively, an integer is called a *bitmask* (or simply a *mask*).
A bitmask "masks out" items because a zero in the`i`th bit excludes the `i`th item, while a one includes it.
We also commonly use a bitmask to include certain bits of an integer while excluding others.

For example, suppose that
```
A = 0b10010101
M = 0b00011101
```
Both are 8-bit integers. In this case, we can say that `A` is masked by `M` at the first and the fourth through eighth bit positions.

The bitwise instructions discussed earlier are useful in manipulating integers with masks. 
For example:
- To *clear* the bits of `A`that are not selected by `M`, take the bitwise AND: `A AND M`.
- To *set* the bits of `A` selected by `M`, take the bitwise OR: `A OR M`.
~~~~

## TEST Instruction

The `test` instruction makes a bitwise AND between both operands and sets flags according to the result.

If A is the first operand and B, the second:

| flag | set when             |
|:----:|:---------------------|
| CF   | always cleared       |
| ZF   | A AND B == 0         |
| SF   | A AND B < 0 (signed) |
| OF   | always cleared       |

This instruction takes two operands and update the flags, but **do not modify its operands**.

## Shift operations

These instructions move the bits in the destination operand by a number of positions specified by the second operand.
The second operand must be a constant number (an `immediate`) or the register `cl` (the lowest 8 bits of `rcx`).

| Name    | Description             |
|---------|-------------------------|
|shl/sal  |Shifts bits to the left  |
|shr/sar  |Shifts bits to the right |

### Shl / Sal

Both `shl` and `sal` perform the exact same operation, one is an alias of the other.

Whenever a shift left is made, bits closer to the end of the sequence than the length of the shift are first moved to the carry flag (CF) and then discarded.
On the other hand, a number of new cleared bits equal to the length of the shift is added to the beginning.

For instance, consider the number `23`, represented as a single byte, being shifted 3 positions to the left:

Before shift (Number 23):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|:-----:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| bits  | 0   | 0   | 0   | 1   | 0   | 1   | 1   | 1   |

After shifting 3 positions (Number 184):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|:-----:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| bits  | 1   | 0   | 1   | 1   | 1   | 0   | 0   | 0   |

Notice that `184` is equal to `23 * 2³`.
Since each bit in an integer represents a power of 2, a shift to the left by n positions has the effect of multiplying the integer by 2ⁿ.

### Shr/Sar

There are two instructions to move bits to the right: `shr` and `sar`.

Whenever any of the two instructions is used, bits closer to the start of the sequence than the length of the shift are first moved to the carry flag (CF) and then discarded.
On the other hand, a number of new bits equal to the length of the shift is added to the end.

The difference between them is that `shr` moves `0` bits to the left end, while `sar` moves `1` if the most significant was set and `0` otherwise.
This means that `sar` preserves the sign in the shift of a signed integer.

For instance, consider the number `23`, represented as a single byte, being shifted 3 positions to the right:

Before shift (Number 23):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|:-----:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| bits  | 0   | 0   | 0   | 1   | 0   | 1   | 1   | 1   |

After shifting 3 positions (Number 2):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|:-----:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| bits  | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |

Since `23` is not negative, both `sar` and `shr` would give the same result in this case.

On the other hand, consider the number `-42`, represented as a single byte, being shifted 3 positions to the right:

Before shift (Number -42):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|:-----:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| bits  | 1   | 1   | 0   | 1   | 0   | 1   | 1   | 0   |

After shifting 3 positions with shr (Number 26):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|:-----:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| bits  | 0   | 0   | 0   | 1   | 1   | 0   | 1   | 0   |

After shifting 3 positions with sar (Number -6):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|:-----:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| bits  | 1   | 1   | 1   | 1   | 1   | 0   | 1   | 0   |

Notice that `2` is the quotient of `23 / 2³`.
Similarly, if the number `-42` is interpreted as unsigned, it would be `214` and `214 / 2³` is equal to `26`.

Since each bit in an integer represents a power of 2, a shift to the right by n positions using `shr` has the effect of making an *unsigned* division by 2ⁿ.

Notice also that `-42 / 2³` is equal to `-6` (with a remainder of 6).
So, a shift to the right by n positions using `sar` has the effect of making a *signed* division by 2ⁿ.

~~~~exercism/note

When dividing negative numbers, `idiv` and `sar` may yield different results.
This is because `idiv` rounds towards `0`, while `sar` rounds towards `infinity`.

In practice, this means that the `remainder` in a signed division with `idiv` may be negative.

So, when dividing `-9` by `4` using `idiv`, the quotient would be `-2`.
Whereas when shifting `-9` by `2` positions to the right, the result would be `-3`.

~~~~

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

[bitwise]: https://en.wikipedia.org/wiki/Bitwise_operation
