# About

A **floating-point** is a number which can take a fractional part, such as `-1.23` or `3.1415`.

In order to represent such a number as a sequence of bytes, x86-64 uses the [IEEE-754][ieee] standard.
The two most common formats in this standard are single-precision floating-point and double-precision floating-point numbers.
x86-64 supports both.

A single-precision floating-point number is 32-bit wide, whereas a double-precision is 64-bit wide.

```exercism/note
Since floating-point numbers are an approximation of the whole of real numbers, operations with them may give imprecise results.

For an in-depth explanation, please refer to [Appendix D][guide] of Oracle's Numerical Computation Guide "What Every Computer Scientist Should Know About Floating-Point Arithmetic".

The [Float Toy page][toy] has a nice, graphical explanation for how a floating-point numbers' bits are converted to an actual floating-point value.

[guide]: https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
[toy]: https://evanw.github.io/float-toy
```

## XMM Registers

In x86-64, there are 16 dedicated registers for doing floating-point arithmetic, named `xmm0` to `xmm15`.

Those registers are at least 128-bit wide, but recent processors increase this to 256-bits or 512-bits.
However, in practice, most floating-point numbers only use the lowest 32-bit or 64-bits, depending on the desired precision.

## Conversion between numbers

There is a family of instructions for converting between number formats: `cvtxx2yy`.

Both `xx` and `yy` are not literals, but placeholders:

- `xx` is a placeholder for the type of the source operand.
- `yy` is a placeholder for the type of the destination operand.

This placeholder can take many forms, between them:

| placeholder | meaning               |
| ----------- | --------------------- |
| `si`        | signed integer        |
| `ss`        | 32-bit floating-point |
| `sd`        | 64-bit floating-point |

For example:

```x86asm
cvtsi2ss xmm0, eax ; converts a 32-bit signed integer to a single-precision floating-point
cvtsd2si rax, xmm1 ; converts a double-precision floating-point to a 64-bit signed integer
```

Note that it is possible to convert a 32-bit integer to a 64-bit floating-point or a 64-bit integer to a 32-bit floating-point.
Similarly, it is also possible to convert a 32-bit floating-point to a 64-bit integer or a 64-bit floating-point to a 32-bit integer.
In other words, the size of both operands in a `cvtxx2yy` _do not need to be the same_:

```x86asm
cvtsi2sd xmm0, eax ; converts a 32-bit signed integer to a double-precision floating-point
cvtsi2ss xmm0, rax ; converts a 64-bit signed integer to a single-precision floating-point
cvtss2si rax, xmm0 ; converts a single-precision floating-point to a 64-bit signed integer
cvtsd2si eax, xmm0 ; converts a double-precision floating-point to a 32-bit signed integer
```

When the floating-point number can not be exactly expressed as an integer, `cvtxx2si` rounds the number according to the rounding control in a special register called `mxcsr`.
This could be a round to nearest, a round down, a round up or a truncate.
There is no guaranteed default at function entry.

Note that a exact result is not rounded and, thus, not affected by the rounding control.
For instance, `42.0` would _always_ be converted to `42`.

There is a similar family of instructions with the format `cvttxx2si` (with an extra `t`) that always truncates the result.

## Round

The `roundxx` family of instruction converts a floating-point in the source operand to a rounded floating-point stored in the destination operand.

Here, `xx` is a placeholder for the type of the operands, as usual: `ss` for single-precision and `sd` for double-precision floats.

Those instructions take a constant number as third operand.
This number indicates the rounding mode:

| Number | Mode         |
| :----- | :----------- |
| 0      | Nearest      |
| 1      | Floor (down) |
| 2      | Ceil (up)    |
| 3      | Truncate     |

For example:

```x86asm
roundss xmm0, xmm1, 1 ; this rounds down (takes the floor) a 32-bit floating-point in xmm1 and stores it in xmm0
roundsd xmm2, xmm2, 2 ; this rounds up (takes the ceil) a 64-bit floating-point in xmm2 and stores it in xmm2
```

Since those instructions produce an exact result, they can be used in preparation for a `cvtxx2si`.

## Arithmetic Instructions

Many operations with floating-point numbers take instructions with a similar name as its equivalent for integers, but adding the necessary placeholder (`ss` or `sd`) at the end.
Those instructions are two-operand, with the usual semantics, even those that perform multiplication or division:

```x86asm
addss xmm1, xmm2 ; xmm1 = xmm1 + xmm2 (all 32-bit floating-point)
mulsd xmm4, xmm5 ; xmm4 = xmm4 * xmm5 (all 64-bit floating-point)
divss xmm0, xmm3 ; xmm0 = xmm0 / xmm3 (all 32-bit floating-point)
```

## Move

The instructions to move from a XMM register to another are `movss` or `movsd`:

```x86asm
movss xmm1, xmm0 ; this copies a 32-bit floating-point from xmm0 to xmm1
movsd xmm6, xmm4 ; this copies a 64-bit floating-point from xmm4 to xmm6
```

It is **not** possible to move an immediate (a constant signed integer) to a xmm register directly.
This number first needs to be moved into a general-purpose register and then converted using `cvtsi2xx`:

```x86asm
mov rax, 10        ; rax is a 64-bit integer with value 10
cvtsi2sd xmm0, rax ; xmm0 is a 64-bit floating-point with value 10.0
```

## Comparisons

There are two groups of instructions to make a comparison between two floating-point numbers.
They take the form `comixx` and `ucomixx`, where `xx` is either `ss` or `sd`.
Both set flags in `rflags` as usual, following the same semantics as `cmp`.

The difference between them is that `ucomixx` sets the `parity flag (PF)` if one of the two floating-point numbers has a `NaN` value, whereas `comixx` raises an exception in this case.

The comparison between floating-point values is _unsigned_:

```x86asm
ucomisd xmm0, xmm1
ja .greater         ; 'ja' must be used for "greater", not 'jg'
jb .lesser          ; 'jb' must be used for "lesser", not 'jl'
```

## Other instructions

There are many more instructions for working with floating-point numbers, implementing common operations.
Some of them are:

| Instruction | Description                                      |
| :---------- | :----------------------------------------------- |
| `sqrtxx`    | Computes square root (`sqrt(x)`)                 |
| `rcpss`     | Computes reciprocal (`1/x`)                      |
| `rsqrtss`   | Computes reciprocal of square root (`1/sqrt(x)`) |
| `minxx`     | Computes minimum (`min(x, y)`)                   |
| `maxxx`     | Computes maximum (`max(x, y)`)                   |

Where a `xx` placeholder is used, it can take the form of `ss` or `sd`, as usual.
However, `rcpss` and `rsqrtss` only work with single-precision floating-point numbers.

Those instructions are all two-operand.

## Calling Convention

In System V ABI, the first eight floating-point arguments are passed to functions in order, from `xmm0` to `xmm7`.
Floating-point values are returned from functions in `xmm0` and, if necessary, `xmm1`.

All `xmm` registers are freely available to use, none of them is reserved for the caller.

## Memory

Floating-point values can be defined in memory following the same semantics as integers of the same size.
NASM (The Netwide Assembler - the assembler used by this track) also allows for declaration of floating-point values in scientific notation.

```x86asm
section .data
    pi dq 3.141592653589793 ; this is a double-precision floating-point value
    exp_num dd 1.e5 ; this is a single precision floating-point value equal to 1 * 10⁵
    exp_num2 dd 1.e+5 ; this is a single precision floating-point value equal to 1 * 10⁵
    frac dq 1.e-10 ; this is a double precision floating-point value equal to 1 * 10⁻¹⁰, i.e., 0.0000000001
```

[ieee]: https://en.wikipedia.org/wiki/IEEE_754
