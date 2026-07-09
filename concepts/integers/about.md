# About

In an assembly language, most abstractions common in higher-level languages are not present.

Values in a register or in memory are simply a sequence of one or more [bytes][byte], each formed of eight [bits][bit].
Most, if not all, abstractions are built on top of this.

## Binary Notation

[Integers][integer] are one of the most important and fundamental abstractions.
They represent whole numbers such as `4`, `-2`, `0` or `64532`.

To represent an integer as a sequence of bytes, the [binary notation][binary] is used.
In this notation, each bit in the sequence represents a distinct power of two, with the value increasing as the index of the bit increases from right to left.

## Unsigned Numbers

If the number can only be non-negative, it's called an **unsigned** number.

Unsigned numbers are represented directly as the sum of the powers of two corresponding to all set bits in their sequence.

For instance, this represents the number `2⁰ + 2³ + 2⁵ + 2⁶ + 2⁷`, which is `233`:

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ----- | --- | --- | --- | --- | --- | --- | --- | --- |
| bits  | 1   | 1   | 1   | 0   | 1   | 0   | 0   | 1   |

Given an arbitrary sequence of bytes, any non-negative whole number could be theoretically represented like this.

In practice, however, a register can only hold up to 64 bits.
So, the range of representable non-negative integers in a register goes from `0` (no bit set) to `2⁶⁴ - 1` (sum of all 64 bits set).

Widening an unsigned number to a larger size is done by filling all upper bits with `0`, so that no new bit contributes to the value.
This is called **zero-extension**.

The instruction [movzx][movzx] (`z` for zero) zero-extends an 8-bit or 16-bit source operand to a larger destination operand.
A 32-bit source operand is always zero-extended to all 64 bits of the destination operand with a simple `mov`.

## Signed Numbers

If an integer can assume positive or negative values, it's called a **signed** number.

To represent [negative numbers][negative], x86-64 uses the [two's complement][two-complement] representation.

In two's complement, a negative number is represented by flipping all bits and then adding `1` to the result.
Flipping a bit means that the values are inverted: a bit with the value of `1` becomes `0` and a bit with the value of `0` becomes `1`.

For instance, the number `-23` can be obtained from `23` like this:

Original number (23):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ----- | --- | --- | --- | --- | --- | --- | --- | --- |
| bits  | 0   | 0   | 0   | 1   | 0   | 1   | 1   | 1   |

Step 1 (flip all bits):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ----- | --- | --- | --- | --- | --- | --- | --- | --- |
| bits  | 1   | 1   | 1   | 0   | 1   | 0   | 0   | 0   |

Step 2 (add 1):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ----- | --- | --- | --- | --- | --- | --- | --- | --- |
| bits  | 1   | 1   | 1   | 0   | 1   | 0   | 0   | 1   |

The steps are the same when converting from a negative number to its positive counterpart.
So, `-23` can be changed back to `23` in the same way:

Original number (-23):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ----- | --- | --- | --- | --- | --- | --- | --- | --- |
| bits  | 1   | 1   | 1   | 0   | 1   | 0   | 0   | 1   |

Step 1 (flip all bits):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ----- | --- | --- | --- | --- | --- | --- | --- | --- |
| bits  | 0   | 0   | 0   | 1   | 0   | 1   | 1   | 0   |

Step 2 (add 1):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ----- | --- | --- | --- | --- | --- | --- | --- | --- |
| bits  | 0   | 0   | 0   | 1   | 0   | 1   | 1   | 1   |

Note that the binary representation of `-23` and the binary representation of `233` are equal.

To provide disambiguation, in a signed integer the uppermost bit (the one corresponding to `2⁶³`) is not summed up to the others.
Instead, its value is subtracted.

Since this bit corresponds to a higher value than the sum of all the others, in practice this means a number with this bit set is always negative.
This special bit is called the **sign bit**.

Widening a signed number to a larger size means filling every new upper bit with a copy of the sign bit, so that the value is preserved.
This is called **sign-extension**.

The instruction [movsx][movsx] (`s` for sign) sign-extends an 8-bit or 16-bit source operand to a larger destination operand.
A variant of `movsx` called `movsxd` does the same from a 32-bit source operand to a 64-bit destination operand.

The [neg][neg] instruction can be used to change the sign of a number.

~~~~exercism/caution
In assembly, there's no way to tell if a sequence of bytes represents a signed or an unsigned number.
It's the programmer's responsibility to give meaning to those bytes.

The use of comments can be a great aid in this task.
~~~~

## Immediates

In a previous concept, it was mentioned that a constant number, such as `4` or `-15`, can be used as source operand to many instructions.
Those numbers are called **immediates**.

An immediate is not held in a register or in memory: it is encoded inside the instruction itself.
In most instructions, the space reserved for it is only 32 bits wide, no matter how large the destination operand is.

When the destination operand is 64 bits wide, those 32 bits are _sign-extended_ to fill it.
The upper half of the operand receives copies of the uppermost bit of the immediate, so only a number in the range of a _32-bit signed integer_ can be written this way:

```x86asm
add rax, -1          ; the immediate is sign-extended, so all 64 bits of rax are affected
add rax, 2147483647  ; the largest immediate an instruction like this accepts
```

A number outside that range can not be used as an immediate.
The exception to this rule is `mov`, which has a special form, available only when the destination operand is a register, that carries a full 64-bit immediate.
If a 64-bit immediate is needed, first use `mov` to load it into a register, then use the register:

```x86asm
mov rax, 3435973837           ; this works, mov can take a 64-bit immediate
mov rdx, 18446744073709551615 ; the largest immediate mov accepts
sub rdx, rax
```

Note that a negative immediate and the unsigned number with the same bit representation are equivalent and assemble to exactly the same value:

```x86asm
mov rax, -1                   ; rax = 18446744073709551615
mov rax, 18446744073709551615 ; rax = -1
```

## Sum

The sum of two integers can be represented as setting all bits that are set in only one of the two numbers and carrying over bits that are set in both.

Carrying over a bit means that this bit is then added to the next bit index in the sum (not the individual numbers being summed).
This bit is called _carry_.

If the bit in the next index is not set, the carry is "deposited" there, making the bit set.

If, however, the bit is already set, then this bit is cleared and the carry is then added to the following bit index in the sum.
This continues until a bit not set is found, or until the end of the number.

For instance, consider:

Number `30`:

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ----- | --- | --- | --- | --- | --- | --- | --- | --- |
| bits  | 0   | 0   | 0   | 1   | 1   | 1   | 1   | 0   |

Number `13`:

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ----- | --- | --- | --- | --- | --- | --- | --- | --- |
| bits  | 0   | 0   | 0   | 0   | 1   | 1   | 0   | 1   |

The bits in index `1` and `4` are only set in the number `30` and the bit in index `0` is only set in number `13`.
So they are all set in the resulting sum:

Step 1 (set all bits present in only one of the numbers):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ----- | --- | --- | --- | --- | --- | --- | --- | --- |
| bits  | 0   | 0   | 0   | 1   | 0   | 0   | 1   | 1   |

The bits in index `2` and `3`, however, are set in both numbers being added.
So those indexes are cleared and their bits are carried over to the next index in the sum.

Since the bit in index `3` is not set in the sum, the carry from index `2` is put there:

Step 2 (carry over bit in index 2):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ----- | --- | --- | --- | --- | --- | --- | --- | --- |
| bits  | 0   | 0   | 0   | 1   | 1   | 0   | 1   | 1   |

However, the bit in index `4` is already set in the sum, so the carry from index `3` clears it and moves to the next bit index.

Since the bit in index `5` is not set, the carry is put there:

Step 3 (carry over bit in index 3):

| index | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
| ----- | --- | --- | --- | --- | --- | --- | --- | --- |
| bits  | 0   | 0   | 1   | 0   | 1   | 0   | 1   | 1   |

The resulting number is `2⁵ + 2³ + 2¹ + 2⁰`, which is `43`, the sum of `30` and `13`.

In x86-64, the addition of two numbers can be calculated using the `add` instruction.

Sometimes, the sum of two numbers leaves an excessive bit that does not fit into the destination operand.
This carry is represented by a special value called the **carry flag (CF)**.
The `CF` can also be set by other instructions, performing other operations.

The instruction [adc][adc] can be used to sum two numbers and also the value in the carry flag.
It is a two-operand instruction, with the same syntax as `add`.

There's also an [inc][inc] one-operand instruction, that adds `1` to the value in its operand:

```x86asm
inc rax ; rax = rax + 1
```

The sum of two integers operates in the same way for both unsigned and signed numbers.

## Subtraction

The subtraction of two integers is performed using the `sub` instruction.

In the same way an addition can leave a carry, a subtraction can leave a _borrow_ in `CF`.
There is an instruction [sbb][sbb] that subtracts both the source operand and also the borrow from the destination operand.

There's also a [dec][dec] one-operand instruction, that subtracts `1` from the value in its operand:

```x86asm
dec rax ; rax = rax - 1
```

The subtraction of two integers also operates in the same way for both unsigned and signed numbers.

## Multiplication

There are two different instructions to perform multiplication between two numbers in x86-64.
As a rule, unsigned multiplication uses the instruction [mul][mul], while signed multiplication uses [imul][imul].

The `mul` instruction takes the following one-operand form, where `src` is the source operand:

```x86asm
mul src
```

The `imul` instruction can take a one-operand, two-operand or three-operand form:

```x86asm
imul src
imul dest, src
imul dest, src1, src2
```

### One-Operand Multiplication

As a general rule, the range of bits needed to represent the product of two integers is the sum of the range of bits needed for each integer being multiplied.

This means that the product of two numbers in the range of a 64-bit register needs up to 128 bits to be represented.

That's why two registers are implicitly used to perform a multiplication in one-operand form: `rax` and `rdx`.
If the multiplication involves two 64-bit numbers, then the lower 64 bits of the result will be in `rax` and the upper 64 bits will be in `rdx`.

This is usually called `rdx:rax`, to indicate that both registers are used in tandem:

```x86asm
mul rcx ; rax = lower 64 bits of rax * rcx
        ; rdx = upper 64 bits of rax * rcx
```

The same happens for other operand sizes.
So, for instance, if two 32-bit numbers are being multiplied, `eax` and `edx` will be used.

The exception is the multiplication between two bytes.

In this case, instead of `dl:al`, `ax` will be used.
The lower portion of `ax` (`al`) will get the lower 8 bits of the product, while the upper portion (`ah`) will get the upper 8 bits.

~~~~exercism/caution
Registers implicitly used in a multiplication, such as `rax` and `rdx`, are always overwritten.
The values in those registers should be saved before the operation if they are necessary later.
~~~~

### Two-Operand Multiplication

The two-operand form of `imul` has an explicit destination operand and follows the usual syntax.
`rdx` is not used. Instead, the result is truncated to fit into the destination operand.

```x86asm
imul r8, r9 ; r8 = lower 64 bits of r8 * r9
```

### Three-Operand Multiplication

The three-operand form of `imul` has two source operands, the second of which is always an immediate (a constant number).
Both source operands are multiplied and the result is truncated and placed in the destination operand:

```x86asm
imul r8, r9, 100 ; r8 = lower 64 bits of r9 * 100
```

Note that the destination operand is not used in the multiplication. It just receives the result.

### Handling Overflow

Both two-operand and three-operand multiplication truncate the result to fit into the size of the destination operand.
A one-operand multiplication preserves the full range, but it is usually split into two registers, `rdx` and `rax`.

So, it is sometimes useful to widen the operands before the multiplication to make room for the whole product in a single register.
An unsigned operand is zero-extended, while a signed one is sign-extended:

```x86asm
movzx eax, di ; di and si hold unsigned 16-bit numbers
movzx ecx, si
mul ecx       ; the 32-bit product fits in eax, and edx is cleared
```

Widening is also necessary whenever only part of a register was written, since the remaining bits keep whatever they held before:

```x86asm
mov ax, 1000 ; lower 16 bits of eax are 1000, upper bits keep their previous contents
mov cx, 200  ; lower 16 bits of ecx are 200, upper bits keep their previous contents

; 200 * 1000 does not fit in 16 bits, so a 32-bit multiplication is necessary
; however, multiplying eax by ecx would also multiply those leftover upper bits

movzx eax, ax ; lower 16 bits of eax remain 1000, upper bits are cleared
movzx ecx, cx ; lower 16 bits of ecx remain 200, upper bits are cleared
mul ecx       ; now eax correctly holds 200 * 1000, and edx holds 0
```

### Using imul With Unsigned Numbers

It is possible to use `imul` to multiply unsigned numbers.
However, this may give an incorrect result if one of the numbers may be interpreted as negative.

Since the sign bit in a signed integer corresponds to the most significant bit in an unsigned integer, in practice this difference becomes relevant only when more than the truncated result is needed, that is, when the full range of `rdx:rax` is used.

The lower half of the product is the same for both instructions.
Only the upper half, in `rdx`, differs.

## Division

As is the case with multiplication, there are also two instructions to perform division between two numbers.
Unsigned division uses the instruction [div][div], while signed division uses [idiv][idiv].

Both instructions work with only one operand:

```x86asm
div src
idiv src
```

16-bit, 32-bit and 64-bit division use `dx:ax`, `edx:eax` and `rdx:rax` as the dividend, respectively.
In these cases, both registers act in tandem to create a 2N-bit value, where N is the size of the operation (16-bit, 32-bit or 64-bit).
This value is then divided by the source operand.
The quotient is written to `ax`, `eax` or `rax` and the remainder is written to `dx`, `edx` or `rdx`, according to the size of the operation.

The division between bytes is special: instead of using `dl:al`, `ax` is used.
The lower 8 bits of `ax` (`al`) will get the quotient of the operation and the higher 8 bits (`ah`) will get the remainder.

Note that all bits in the dividend should be appropriately set before the division.
Any bit set in `rdx` (or in `ah` for 8-bit division) contributes to the value being divided.

In unsigned division, when the value to be divided fits in the lower half, the upper half should be cleared.
Any instruction that clears those bits will do.
For example, `mov edx, 0` clears the upper bits in 32-bit division:

```x86asm
mov eax, edi ; the value to be divided
mov edx, 0   ; a 32-bit destination is zero-extended, so the upper half is cleared
div esi      ; eax = edi / esi, edx = edi % esi
```

In signed division, the value should be sign-extended instead.
There are instructions that automate this process: [cbw][cbw], [cwd][sign-extension], [cdq][sign-extension] and [cqo][sign-extension].
The first sets the bits in `ah` according to the sign of `al`.
The others perform sign-extension from `ax` to `dx`, from `eax` to `edx` and from `rax` to `rdx`, respectively.

```x86asm
mov eax, edi ; the value to be divided
cdq          ; every bit of edx receives a copy of the sign bit of eax
idiv esi     ; eax = edi / esi, edx = edi % esi
```

Failing to set the upper half can produce a wrong quotient.
It can also stop the program: when the quotient does not fit in the destination register, the processor raises a divide error.

~~~~exercism/caution
Registers implicitly used in a division, such as `rax` and `rdx`, are always overwritten.
The values in those registers should be saved before the division if they are necessary later.
~~~~

[byte]: https://en.wikipedia.org/wiki/Byte
[bit]: https://en.wikipedia.org/wiki/Bit
[integer]: https://en.wikipedia.org/wiki/Integer_(computer_science)
[binary]: https://en.wikipedia.org/wiki/Binary_number
[two-complement]: https://en.wikipedia.org/wiki/Two%27s_complement
[negative]: https://en.wikipedia.org/wiki/Negative_number
[neg]: https://www.felixcloutier.com/x86/neg
[adc]: https://www.felixcloutier.com/x86/adc
[inc]: https://www.felixcloutier.com/x86/inc
[sbb]: https://www.felixcloutier.com/x86/sbb
[dec]: https://www.felixcloutier.com/x86/dec
[mul]: https://www.felixcloutier.com/x86/mul
[imul]: https://www.felixcloutier.com/x86/imul
[div]: https://www.felixcloutier.com/x86/div
[idiv]: https://www.felixcloutier.com/x86/idiv
[cbw]: https://www.felixcloutier.com/x86/cbw:cwde:cdqe
[sign-extension]: https://www.felixcloutier.com/x86/cwd:cdq:cqo
[movzx]: https://www.felixcloutier.com/x86/movzx
[movsx]: https://www.felixcloutier.com/x86/movsx:movsxd
