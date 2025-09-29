# About

A `floating-point` is a number which can take a fractional part, such as `-1.23` or `3.1415`.

In order to represent such a number as a sequence of bytes, there are some standards.
x86-64 uses [IEEE-754][ieee].

The two most common formats in `IEEE-754` are single-precision floating-point and double-precision floating-point numbers.
x86-64 supports both.

A single-precision floating-point number is 32-bit wide, whereas a double-precision is 64-bit wide.

~~~~exercism/note
Since floating-point numbers are an approximation of the whole of fractional numbers, operation with them may give imprecise results.

For an in-depth explanation, please refer to [Appendix D][float-guide] of Oracle's Numerical Computation Guide "What Every Computer Scientist Should Know About Floating-Point Arithmetic".
~~~~

## XMM Registers

In x86-64, there are 16 dedicated registers for doing floating-point arithmetic, named `xmm0` to `xmm15`.

Those registers are at least 128-bit wide, but recent processors increase this to 256-bits or 512-bits

However, in practice, floating-point numbers only use the lowest 32-bit or 64-bits, depending on the desired precision.

### Conversion between numbers

There is a family of instructions with the format `cvtxx2yy`, where `xx` is a placeholder for the type of the source operand and `yy`, for the type of the destination operand.

This placeholder can take many forms, between them:

- for integers, it is `si`;
- for single-precision floating-point numbers, it is `ss`; and
- for double-precision floating-point numbers, it is `sd`.

For instance:

```nasm
cvtsi2ss xmm0, eax ; converts a signed integer to a single-precision floating-point
cvtsd2si rax, xmm1 ; converts a double-precision floating-point to a signed integer
```

When the floating-point number can not be exactly expressed as an integer, `cvtxx2si` rounds the number according to the rounding control in a special register called `mxcsr`.
This could be a round to nearest, a round down, a round up or a truncate.
There is no guaranteed default at function entry.

Notice that a exact result is not rounded and, thus, not affected by the rounding control.
For instance, `42.0` would always be converted to `42`.

There is a similar family of instructions with the format `cvttxx2si` (with an extra `t`) that always truncates the result.

### Round

The `roundxx` family of instruction converts a floating-point in the source operand in a rounded floating-point stored in the destination operand.

Here, `xx` is a placeholder for the type of the operands, as usual: `ss` for single-precision and `sd` for double-precision floats.

Those instructions take a constant number as third operand.
This number indicates the rounding mode:

```
+--------+------------------+
| Number |      Mode        |
+--------+------------------+
|    0   |     Nearest      |
+--------+------------------+
|    1   |   Floor (down)   |
+--------+------------------+
|    2   |   Ceil (up)      |
+--------+------------------+
|    3   |     Truncate     |
+--------+------------------+
```

Those instructions can be used in preparation for a `cvtxx2si` when there's no guarantee that a floating-point number can be exactly expressed as an integer.

### Arithmetic Instructions

Many operations with floating-point numbers take instructions with a similar name as its equivalent for integers, but adding the necessary placeholder (`ss` or `sd`) at the end.

For instance, `addss` adds two single-precision floating-point numbers and `mulsd` multiplies two double-precision floating-point numbers.

Those instructions are two-operand, with the usual semantics, even those that perform multiplication or division.

### Move

Similarly to what happens with arithmetic operations, to move from a `xmm` register to another, the instruction is `movss` or `movsd`.

It is not possible to move a constant or immediate to a xmm register directly.

This number first needs to be moved into a general-purpose register and then converted using `cvtsi2xx`.

### Comparisons

There are two groups of instructions to make a comparison between two floating-point numbers.
They take the form `comixx` and `ucomixx`, where `xx` is either `ss` or `sd`.

Both set flags in `rflags` as usual, following the same semantics as `cmp`.

The difference between them is that `ucomixx` sets the `parity flag (PF)` if one of the two floating-point numbers has a `NaN` value, whereas `comixx` raises an exception.

### Other instructions

There are many more instructions for working with floating-point numbers, implementing common operations.
Some of them include:

#### Sqrtxx

This takes the square root of the source operand and stores the result in the destination operand.

As usual, `xx` is a placeholder for either `ss` or `sd`.

#### Rcpss

Computes the reciprocal of the source operand and stores the result in the destination operand.
The reciprocal of `x` is `1/x`.

There is no double-precision equivalent for this instruction.

#### Rsqrtss

Computes the reciprocal of the square root of the source operand and stores the result in the destination operand.
The reciprocal of `x` is `1/x`.

There is no double-precision equivalent for this instruction.

#### Minxx

The `minxx` instruction computes the minimum of the two operands and stores the result in the destination operand.

As usual, `xx` is a placeholder for either `ss` or `sd`.

#### Maxxx

The `maxxx` instruction computes the maximum of the two operands and stores the result in the destination operand.

As usual, `xx` is a placeholder for either `ss` or `sd`.

[ieee]: https://en.wikipedia.org/wiki/IEEE_754
[float-guide]: https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
