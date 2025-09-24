# About

In a previous concept, it was explored how an `integer` in assembly is essentially a sequence of bytes interpreted in a specific way.

As there is no built-in data structure and very few abstractions in assembly, the ability to manipulate bits and bytes is essential.

This is why x86-64 offers a variety of different instructions for bit manipulations.

## Single bit manipulation

These instructions work on single bits in a operand.

### Bt

The instruction `bt` selects the bit in the first operand at the bit-position designated by the second operand.
This bit is then stored in the `carry flag`.

### Bts

The instruction `bts` selects the bit in the destination operand at the bit-position designated by the second operand, storing it in the `carry flag`.
This bit is not only selected, but also set in the destination operand.

### Btr

The instruction `btr` selects the bit in the destination operand at the bit-position designated by the second operand, storing it in the `carry flag`.
This bit is not only selected, but also cleared in the destination operand.

### Btc

The instruction `btc` selects the bit in the destination operand at the bit-position designated by the second operand, storing it in the `carry flag`.
This bit is not only selected, but also complemented in the destination operand, so that if it was set before, it is now cleared, and if it was cleared, it is now set.

## Bitwise operations

[Bitwise operations][bitwise] are performed in all bits of an operand.

## Not

The instruction [not][not] flips all the bits in the destination operand.
Every set bit is cleared, and every cleared bit is set.

## Or

The instruction [or][or] sets in the destination operand all bits which are set in either the destination operand or the source operand.
Any other bit is cleared.

## And

The instruction [and][and] sets in the destination operand all bits which are set in both the destination operand and the source operand.
Any other bit is cleared.

## Xor

The instruction [xor][xor] sets in the destination operand all bits which are set in only one of the destination operand or the source operand.
If a bit is set in both or cleared in both, it is cleared.

## Shl

The instruction [shl][shift] moves all bits in the destination operand a number of positions to the left equal to the source operand.

For instance, this shifts the contents of the `rax` register 2 positions to the left:

```nasm
shl rax, 2
```

The source operand must be a constant number (an `immediate`) or the register `cl` (the 8-bit lowest portion of `rcx`).

Whenever a shift left is made, bits closer to the end of the sequence than the length of the shift are first moved to the `carry flag` and then discarded.
On the other hand, a number of new cleared bits equal to the length of the shift is added to the beginning.

For instance, consider the number `23`, represented as a single byte, being shifted 3 positions to the left:

```
Before shift (Number 23):
+--------+---+---+---+---+---+---+---+---+
| index  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+
|  bits  | 0 | 0 | 0 | 1 | 0 | 1 | 1 | 1 |
+--------+---+---+---+---+---+---+---+---+

After shifting 3 positions (Number 184):
+--------+---+---+---+---+---+---+---+---+
| index  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+
|  bits  | 1 | 0 | 1 | 1 | 1 | 0 | 0 | 0 |
+--------+---+---+---+---+---+---+---+---+
```

Notice that `184` is equal to `23 * 2³`.
Since each bit in an integer represents a power of 2, a shift to the left by n positions has the effect of multiplying the integer by 2ⁿ.

## Shr/Sar

The operation opposite to shifting left is shifting right.

There are two instructions to move all bits in the destination operand a number of positions to the right equal to the source operand: [shr][shift] and [sar][shift].

For instance, these both shift the contents of the `rax` register 2 positions to the right:

```nasm
shr rax, 2
sar rax, 2
```

In both cases, the source operand must be a constant number (an `immediate`) or the register `cl` (the 8-bit lowest portion of `rcx`).

Whenever any of the two instructions is used, bits closer to the start of the sequence than the length of the shift are first moved to the `carry flag` and then discarded.
On the other hand, a number of new bits equal to the length of the shift is added to the end.

The difference between them is that `shr` moves cleared bits to the end, while `sar` moves `1` if the most significant was set and `0` otherwise.
This means that `sar` preserves the sign in the shift of a signed integer.

For instance, consider the number `23`, represented as a single byte, being shifted 3 positions to the right:

```
Before shift (Number 23):
+--------+---+---+---+---+---+---+---+---+
| index  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+
|  bits  | 0 | 0 | 0 | 1 | 0 | 1 | 1 | 1 |
+--------+---+---+---+---+---+---+---+---+

After shifting 3 positions (Number 2):
+--------+---+---+---+---+---+---+---+---+
| index  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+
|  bits  | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+
```

Since `23` is not negative, both `sar` and `shr` would give the same result in this case.

On the other hand, consider the number `-42`, represented as a single byte, being shifted 3 positions to the right:

```
Before shift (Number -42):
+--------+---+---+---+---+---+---+---+---+
| index  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+
|  bits  | 1 | 1 | 0 | 1 | 0 | 1 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+

After shifting 3 positions with shr (Number 26):
+--------+---+---+---+---+---+---+---+---+
| index  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+
|  bits  | 0 | 0 | 0 | 1 | 1 | 0 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+

After shifting 3 positions with sar (Number -6):
+--------+---+---+---+---+---+---+---+---+
| index  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+
|  bits  | 1 | 1 | 1 | 1 | 1 | 0 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+
```

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

## Rol

The instruction [rol][rotate] moves all bits in the destination operand a number of positions to the left equal to the source operand.

While `shl` discards bits closer to the end of the sequence than the length of the shift, `rol` moves those bits to the start of the sequence.
So, no new bits are added, they all change places.

For instance, consider the number `71`, represented as a single byte, being rotated 3 positions to the left:

```
Before shift (Number 71):
+--------+---+---+---+---+---+---+---+---+
| index  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+
|  bits  | 0 | 1 | 0 | 0 | 0 | 1 | 1 | 1 |
+--------+---+---+---+---+---+---+---+---+

After rotating 3 positions to the left (Number 58):
+--------+---+---+---+---+---+---+---+---+
| index  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+
|  bits  | 0 | 0 | 1 | 1 | 1 | 0 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+
```

There's a similar instruction called `rcl` that uses the `carry flag` as an extra bit in the rotation.

This means that a bit at the end of the sequence is first moved to the flag before going to the start of the sequence.
At the same time, the previous value in the flag is moved to the bit at the start of the sequence.

In both cases, the source operand must be a constant number (an `immediate`) or the register `cl` (the 8-bit lowest portion of `rcx`).

## Ror

The instruction [ror][rotate] does the opposite of `rol`, rotating bits to the right without adding or discarding bits.

There's also a similar instruction called `rcr` that uses the `carry flag` as an extra bit.

In both cases, the source operand must be a constant number (an `immediate`) or the register `cl` (the 8-bit lowest portion of `rcx`).

## Other bit manipulation instructions

### Popcnt

The instruction [popcnt][popcnt] counts the number of bits set in the source operand and stores this count in the destination operand.

It can't be used with 8-bit operands, only with 16-bits, 32-bits or 64-bits.

### Lzcnt

The instruction [lzcnt][lzcnt] counts the number of leading zeros in the source operand and stores this count in the destination operand.
A leading zero is any bit cleared before the first set bit in a sequence of bytes.

It can't be used with 8-bit operands, only with 16-bits, 32-bits or 64-bits.

### BSR

The instruction [bsr][bsr] stores in the destination operand the index of the most significant bit set in the source operand.
If the source operand has no set bit (it's equivalent to the number `0`), the result is undefined.

It can't be used with 8-bit operands, only with 16-bits, 32-bits or 64-bits.

### BSF

The instruction [bsf][bsf] stores in the destination operand the index of the least significant bit set in the source operand.
If the source operand has no set bit (it's equivalent to the number `0`), the result is undefined.

It can't be used with 8-bit operands, only with 16-bits, 32-bits or 64-bits.

[bt]: https://www.felixcloutier.com/x86/bt
[bts]: https://www.felixcloutier.com/x86/bts
[btr]: https://www.felixcloutier.com/x86/btr
[btc]: https://www.felixcloutier.com/x86/btc
[not]: https://www.felixcloutier.com/x86/not
[and]: https://www.felixcloutier.com/x86/and
[or]: https://www.felixcloutier.com/x86/or
[xor]: https://www.felixcloutier.com/x86/xor
[shift]: https://www.felixcloutier.com/x86/sal:sar:shl:shr
[popcnt]: https://www.felixcloutier.com/x86/popcnt
[lzcnt]: https://www.felixcloutier.com/x86/lzcnt
[bsr]: https://www.felixcloutier.com/x86/bsr
[bsf]: https://www.felixcloutier.com/x86/bsf
[bitwise]: https://en.wikipedia.org/wiki/Bitwise_operation
