# About

In an assembly language, most abstractions common in higher-level languages are not present.

Values in a register or in memory are simply a sequence of one or more [bytes][byte], each formed of eight [bits][bit].
Most, if not all, abstractions are built on top of this.

## Binary notation

One of the most important and fundamental abstractions are [integers][integer].
They represent whole numbers such as `4`, `-2`, `0` or `64532`.

In order to represent an integer as a sequence of bytes, the [binary notation][binary] is used.

This means each bit in the sequence represents a distinct power of two.

In x86-64, those bits are counted in ascending order from the smallest index.
This means x86-64 is [little endian][endianness].

## Unsigned and Signed Integers

### Unsigned numbers

If the number is know to be non-negative, it's called an **unsigned** number.

Unsigned numbers are represented directly as the sum of all set bits in its sequence.

For instance, this represents the number `2⁰ + 2³ + 2⁵ + 2⁶ + 2⁷`, which is `233`:

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 1 | 1 | 1 | 0 | 1 | 0 | 0 | 1 |

Given an arbitrary sequence of bytes, any non-negative whole number could be theoretically represented like this.

In practice, however, a register can only hold up to 64 bits.
So, the range of representable non-negative integers in a register goes from `0` (no bit set) to `2⁶⁴ - 1` (sum of all 64 bits set).

### Signed numbers

If an integer can assume positive or negative values, it's called a **signed** number.

In order to represent [negative numbers][negative], x86-64 uses the [two's complement][two-complement] representation.

In two's complement, a negative number is represented by flipping all bits and then adding `1` to the result.
Flipping a bit means that the values are inverted: a bit with the value of `1` becomes `0` and a bit with the value of `0` becomes `1`.

For instance, the number `-23` can be obtained from `23` like this:

Original number (23):

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 0 | 0 | 0 | 1 | 0 | 1 | 1 | 1 |

Step 1 (flip all bits):

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 1 | 1 | 1 | 0 | 1 | 0 | 0 | 0 |

Step 2 (add 1):

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 1 | 1 | 1 | 0 | 1 | 0 | 0 | 1 |

The steps are the same when converting from a negative number to its positive counterpart.
So, `-23` can be changed back to `23` in the same way:

Original number (-23):

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 1 | 1 | 1 | 0 | 1 | 0 | 0 | 1 |

Step 1 (flip all bits):

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 0 | 0 | 0 | 1 | 0 | 1 | 1 | 0 |

Step 2 (add 1):

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 0 | 0 | 0 | 1 | 0 | 1 | 1 | 1 |

The [neg][neg] instruction can be used to change the sign of a number.

Notice that the binary representation of `-23` and the binary representation of `233` are equal.

In order to provide disambiguation, in a signed integer, the most significant bit is not summed up to the others, but indicates whether the number is negative.
This bit is called the **sign bit**.

~~~~exercism/caution

In assembly, there's no way to tell if a sequence of bytes represents a signed or an unsigned number.
It's the programmer's responsibility to give meaning to those bytes.

The use of comments can be a great aid in this task.

~~~~

## Arithmetic

### Sum

The sum of two integers can be represented as setting all bits that are set in only one of the two numbers and carrying over bits that are set in both.

Carrying over a bit means that this bit is then added to the next bit index in the sum (not the individual numbers being summed).
This bit is called _carry_.

If the bit in the next index is not set, the carry is "deposited" there, making the bit set.

If, however, the bit is already set, then this bit is cleared and the carry is then added to the following bit index in the sum.
This continues until a bit not set is found, or until the end of the number.

For instance, consider:

Number `30`:

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 0 | 0 | 0 | 1 | 1 | 1 | 1 | 0 |

Number `13`:

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 1 |

The bits in index `1` and `4` are only set in the number `30` and the bit in index `0` is only set in number `13`.
So they are all set in the resulting sum:

Step 1 (set all bits present in only of the numbers):

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 0 | 0 | 0 | 1 | 0 | 0 | 1 | 1 |

The bits in index `2` and `3`, however, are set in both numbers being added.
So those indexes are cleared and their bits are carried over to the next index in the sum.

Since the bit in index `3` is not set in the sum, the carry from index `2` is put there:

Step 2 (carry over bit in index 2):

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 0 | 0 | 0 | 1 | 1 | 0 | 1 | 1 |

However, the bit in index `4` is already set in the sum, so the carry from index `3` clears it and moves to the next bit index.

Since the bit in index `5` is not set, the carry is put there:

Step 3 (carry over bit in index 3):

| index | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|-------|---|---|---|---|---|---|---|---|
| bits  | 0 | 0 | 1 | 0 | 1 | 0 | 1 | 1 |

The resulting number is `2⁵ + 2³ + 2¹ + 2⁰`, which is `43`, the sum of `30` and `13`.

In x86-64, the addition of two numbers can be calculated using the `add` instruction.

Sometimes, the sum of two numbers leaves an excessive bit that does not fit into the destination operand.
This carry is represented by a special value called the **carry flag (CF)**.
The `CF` can also be set by other instructions, performing other operations.

The instruction [adc][adc] can be used to sum two numbers and also the value in the carry flag.
It is a two-operand instruction, with the same syntax as `add`.

There's also a [inc][inc] instruction, that simply sums 1 to the value in the destination operand:

```nasm
inc dest ; dest = dest + 1
```

The sum of two integers operates in the same way for both unsigned and signed numbers.

## Subtraction

The subtraction of two integers is performed using the `sub` instruction.

There's also a [dec][dec] instruction, that simply subtracts 1 from the value in the destination operand:

```nasm
dec dest ; dest = dest - 1
```

The subtraction of two integers also operates in the same way for both unsigned and signed numbers.

## Multiplication

There are two different instructions to perform multiplication between two numbers in x86-64.
As a rule, unsigned multiplication uses the instruction [mul][mul], while signed multiplication uses [imul][imul].

The `mul` instruction takes the following one-operand form, where src is the source operand:

```nasm
mul src
```

The `imul` instruction can take a one-operand, two-operand or three-operand form:

```nasm
imul src
imul dest, src
imul dest, src1, src2
```

### One-operand form

As a general rule, the range of bits needed to represent the product of two integers is the sum of the range of bits needed for each integer being multiplied.

This means that the product of two numbers in the range of a 64-bit register needs up to 128 bits to be represented.

That's why two registers are implicitly used to perform a multiplication in one-operand form: `rax` and `rdx`.
If the multiplication involves two 64-bit numbers, then the lower 64 bits of the result will be in `rax` and the upper 64 bits will be in `rdx`.

This is usually called `rdx:rax`, to indicate that both registers are used in tandem.

The same happens if the multiplication involves different register sizes.
So, for instance, if two 32-bit numbers are being multiplied, `eax` and `edx` will be used.

The exception is the multiplication between two bytes.

In this case, instead of `dl:al`, `ax` will be used.
The lower portion of `ax` (`al`) will get the lower 8 bits of the product, while the upper portion (`ah`) will get the upper 8 bits.

~~~~exercism/caution
The `rdx` register is implicitly used in one-operand multiplication.
This means any necessary value in `rdx` must be saved before that operation.
~~~~

### Two-operand form

The two-operand form of `imul` allows for explicitly declaring a different destination operand.

In that case, the product between source and destination operands is placed in the destination operand.
This product is truncated to fit into the destination operand.

### Three-operand form

The three-operand form of `imul` multiplies the two source operands and places the result in the destination operand.

This means that the destination operand is not multiplied with any of the source operands, it just receives the result.
This product is also truncated to fit into the destination operand.

### Handling overflow

In case of a possible overflow, it is sometimes useful to move operands to a larger register size.

A [movzx][movzx] instruction can be used to convert a value in a 8-bit or 16-bit source operand to a larger destination operand, clearing all remaining bits.
This is called **zero extension**:

```nasm
mov ax, 1000 ; lower 16 bits of eax are 1000, upper bits are undefined
mov cx, 200 ; lower 16 bits of ecx are 200, upper bits are undefined

; 200 * 1000 does not fit in 16 bits, so a 32 bits multiplication is necessary
; however, multiplying eax by ecx may produce an incorrect result due to undefined bits

movzx eax, ax ; lower 16 bits of eax remain 1000, upper bits are cleared
movzx ecx, cx ; lower 16 bits of ecx remain 200, upper bits are cleared
mul ecx ; now eax correctly holds 200 * 100
```

A 32-bit source operand is always zero-extended to all 64 bits of the destination operand with a simple `mov`.

### Using imul with unsigned numbers

It is possible to use `imul` to multiply unsigned numbers.
However, this may give an incorrect result if one of the numbers may be interpreted as negative.

Since the sign bit in a signed integer corresponds to the most significant bit in an unsigned integer, in practice, this difference becomes relevant when more than the truncated result is needed, ie, when the full range of `rdx:rax` is used.

## Division

As is the case with multiplication, there are also two instructions to perform division between two numbers.
Unsigned division uses the instruction [div][div], while signed division uses [idiv][idiv].

Both instructions work with only one operand:

```nasm
div src
idiv src
```

In both cases, the value in `rdx:rax` is divided by the value in the source operand.
The quotient is written to the `rax` register and the remainder is written to the `rdx` register.

Notice that as `rdx:rax` is the dividend, both registers must have the appropriate bits set.

So, whenever working with 64-bit integers, all bits in the `rdx` register must be cleared for a non-negative number in `rax` and set for a negative number.
This is called **sign extension**.

Failing to perform sign extension can cause a wrong result for the division or, if the quotient is too large to fit in `rax`, an error.

There are three instructions that automate this process: [cwd][sign-extension], [cdq][sign-extension] and [cqo][sign-extension].
They perform sign extension from `ax` to `dx`, from `eax` to `edx` and from `rax` to `rdx`, respectively.

There's no equivalent instruction for sign extending `al` to `dl` because division between two bytes operate differently.
Instead of using `dl:al`, `ax` is used.

So, the lower 8 bits of `ax` (`al`) will get the quotient of the operation and the higher 8 bits (`ah`) will get the remainder.

There is also the instruction [movsx][movsx] that works similarly to `movzx`, extending from any 8-bit or 16-bit source operand to a larger destination operand.
While `movzx` performs zero-extension, however, `movsx` performs sign-extension.

~~~~exercism/caution
The `rdx` register is implicitly used in an integer division.
This means any necessary value in `rdx` must be saved before that operation.
~~~~

[byte]: https://en.wikipedia.org/wiki/Byte
[bit]: https://en.wikipedia.org/wiki/Bit
[integer]: https://en.wikipedia.org/wiki/Integer_(computer_science)
[binary]: https://en.wikipedia.org/wiki/Binary_number
[endianness]: https://en.wikipedia.org/wiki/Endianness
[two-complement]: https://en.wikipedia.org/wiki/Two%27s_complement
[negative]: https://en.wikipedia.org/wiki/Negative_number
[neg]: https://www.felixcloutier.com/x86/neg
[adc]: https://www.felixcloutier.com/x86/adc
[inc]: https://www.felixcloutier.com/x86/inc
[dec]: https://www.felixcloutier.com/x86/dec
[mul]: https://www.felixcloutier.com/x86/mul
[imul]: https://www.felixcloutier.com/x86/imul
[div]: https://www.felixcloutier.com/x86/div
[idiv]: https://www.felixcloutier.com/x86/idiv
[sign-extension]: https://www.felixcloutier.com/x86/cwd:cdq:cqo
[movzx]: https://www.felixcloutier.com/x86/movzx
[movsx]: https://www.felixcloutier.com/x86/movsx:movsxd
