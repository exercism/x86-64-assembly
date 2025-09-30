# Introduction

## Binary Notation

An `integer` is an abstraction that represents whole numbers, such as `4`, `-2`, `0` or `64532`.

In order to represent an `integer` as a sequence of bytes, the `binary notation` is used.

This means each bit in the sequence represents a distinct power of two.
The sum of the powers corresponding to set bits is the number represented.

In x86-64, those bits are counted in ascending order from the smallest index.

## Unsigned and Signed Integers

### Unsigned numbers

If the number is know to be non-negative, it's called an `unsigned` number.

Unsigned numbers are represented directly as the sum of all set bits in its sequence.

The range of representable non-negative integers in a register goes from `0` (no bit set) to `2⁶⁴ - 1` (sum of all 64 bits set).

### Signed numbers

If an integer can assume positive or negative values, it's called a `signed` number.

In order to represent negative numbers, x86-64 uses the `two's complement` representation.

In two's complement, a negative number is represented by flipping all bits and then adding `1` to the result.
Flipping a bit means that the values are inverted: a bit with the value of `1` becomes `0` and a bit with the value of `0` becomes `1`.

For instance, the number `-23` can be obtained from `23` like this:

The steps are the same when converting from a negative number to its positive counterpart.

The `neg` instruction can be used to change the sign of a number.

In order to provide disambiguation, in a `signed` integer, the most significant bit is not summed up to the others, but indicates whether the number is negative.
This bit is called the `sign bit`.

~~~~exercism/caution

In assembly, there's no way to tell if a sequence of bytes represents a signed or an unsigned number.
It's the programmer's responsibility to give meaning to those bytes.

The use of comments can greatly aid in this task.

~~~~

## Arithmetic

### Sum

In x86-64, the addition of two numbers can be calculated using the `add` instruction.

Sometimes, the sum of two numbers leaves a bit not set in the result (a carry that reached the end of the number without being added).

This carry is represented by a special value called the `carry flag (CF)`.

The instruction `adc` can be used to sum two numbers and also the value in the carry flag.
Its syntax is the same of `add`:

```nasm
adc dest, src
```

There's also a `inc` instruction, that simply sums 1 to the value in the destination operand:

```nasm
inc dest ; dest = dest + 1
```

The sum of two integers operates in the same way for both unsigned and signed numbers.

## Subtraction

The subtraction of two integers is simply the sum of the first with the `neg` of the second.
It is performed using the `sub` instruction.

There's also a `dec` instruction, that simply subtracts 1 from the value in the destination operand:

```nasm
dec dest ; dest = dest - 1
```

The subtraction of two integers also operates in the same way for both unsigned and signed numbers.

## Multiplication

There are two different instructions to perform multiplication between two numbers in x86-64.
Unsigned multiplication uses the instruction `mul`, while signed multiplication uses `imul`.

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

Two registers are implicitly used to perform a multiplication in one-operand form: `rax` and `rdx`.
If the multiplication involves two 64-bit numbers, then the lower 64-bits of the result will be in `rax` and the upper 64-bits will be in `rdx`.

This is usually called `rdx:rax`, to indicate that both registers are used in tandem.

The same happens if the multiplication involves different register sizes.
So, for instance, if two 32-bit numbers are being multiplied, `eax` and `edx` will be used.

The exception is the multiplication between two bytes.

In this case, instead of `dl:al`, `ax` will be used.
The lower portion of `ax` (`al`) will get the lower 8-bits of the product, while the upper portion (`ah`) will get the upper 8-bits.

### Two-operand form

The two-operand form of `imul` allows for explicitly declaring a different destination operand.

In that case, the product between source and destination operands is placed in the destination operand.
This product is truncated to fit into the destination operand.

### Three-operand form

The three-operand form of `imul` multiplies the two source operands and places the result in the destination operand.

This means that the destination operand is not multiplied with any of the source operands, it just receives the result
This product is also truncated to fit into the destination operand.

## Division

As is the case with multiplication, there are also two instructions to perform division between two numbers.
Unsigned division uses the instruction `div`, while signed division uses `idiv`.

Both instructions work with only one operand:

```nasm
div src
idiv src
```

In both cases, the value in `rdx:rax` is divided by the value in the source operand.
The quotient is written to the `rax` register and the remainder is written to the `rdx` register.

Notice that as `rdx:rax` is the dividend, both registers must have the appropriate bits set.

So, whenever working with 64-bits integers, all bits in the `rdx` register must be cleared for a non-negative number in `rax` and set for a negative number.
This is called `sign extension`.

Failing to perform sign extension can cause a wrong result for the division or, if the quotient is too large to fit in `rax`, an error.

There are three instructions that automate this process: `cwd`, `cdq` and `cqo`.
They perform sign extension from `ax` to `dx`, from `eax` to `edx` and from `rax` to `rdx`, respectively.

There's no equivalent instruction for extending `al` to `dl` because division between two bytes operate differently.
Instead of using `dl:al`, `ax` is used.

So, the lower 8-bits of `ax` (`al`) will get the quotient of the operation and the higher 8-bits (`ah`) will get the remainder.
