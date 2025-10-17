# Introduction

## Floating-Point Numbers

A **floating-point** is a number which can take a fractional part, such as `-1.23` or `3.1415`.

In order to represent such a number as a sequence of bytes, x86-64 uses the **IEEE-754** standard.
The two most common formats in this standard are single-precision floating-point and double-precision floating-point numbers.
x86-64 supports both.

A single-precision floating-point number is 32-bit wide, whereas a double-precision is 64-bit wide.

### XMM Registers

In x86-64, there are 16 dedicated registers for doing floating-point arithmetic, named `xmm0` to `xmm15`.

Those registers are at least 128-bit wide, but recent processors increase this to 256-bits or 512-bits.
However, in practice, most floating-point numbers only use the lowest 32-bit or 64-bits, depending on the desired precision.

### Conversion between numbers

There is a family of instructions for converting between number formats: `cvtxx2yy`.

Both `xx` and `yy` are not literals, but placeholders:

- `xx` is a placeholder for the type of the source operand.
- `yy` is a placeholder for the type of the destination operand.

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

The `roundxx` family of instruction converts a floating-point in the source operand to a rounded floating-point stored in the destination operand.

Here, `xx` is a placeholder for the type of the operands, as usual: `ss` for single-precision and `sd` for double-precision floats.

Those instructions take a constant number as third operand.
This number indicates the rounding mode:

| Number | Mode         |
|:-------|:-------------|
| 0      | Nearest      |
| 1      | Floor (down) |
| 2      | Ceil (up)    |
| 3      | Truncate     |

Those instructions can be used in preparation for a `cvtxx2si`.

### Arithmetic Instructions

Many operations with floating-point numbers take instructions with a similar name as its equivalent for integers, but adding the necessary placeholder (`ss` or `sd`) at the end.
Those instructions are two-operand, with the usual semantics, even those that perform multiplication or division.

For instance, `addss` adds two single-precision floating-point numbers and `mulsd` multiplies two double-precision floating-point numbers.

### Move

Similarly to what happens with arithmetic operations, to move from a XMM register to another, the instruction is `movss` or `movsd`.

It is **not** possible to move an immediate (a constant signed integer) to a xmm register directly.
This number first needs to be moved into a general-purpose register and then converted using `cvtsi2xx`.

### Comparisons

There are two groups of instructions to make a comparison between two floating-point numbers.
They take the form `comixx` and `ucomixx`, where `xx` is either `ss` or `sd`.
Both set flags in `rflags` as usual, following the same semantics as `cmp`.

The difference between them is that `ucomixx` sets the parity flag (PF) if one of the two floating-point numbers has a `NaN` value, whereas `comixx` raises an exception in this case.

### Other instructions

There are many more instructions for working with floating-point numbers, implementing common operations.
Some of them are:

| Instruction | Description                                      |
|:------------|:-------------------------------------------------|
| `sqrtxx`    | Computes square root (`sqrt(x)`)                 |
| `rcpss`     | Computes reciprocal (`1/x`)                      |
| `rsqrtss`   | Computes reciprocal of square root (`1/sqrt(x)`) |
| `minxx`     | Computes minimum (`min(x, y)`)                   |
| `maxxx`     | Computes maximum (`max(x, y)`)                   |

Where a `xx` placeholder is used, it can take the form of `ss` or `sd`, as usual.
However, `rcpss` and `rsqrtss` only work with single-precision floating-point numbers.

Those instructions are all two-operand.

### Calling Convention

In System V ABI, the first eight floating-point arguments are passed to functions in order, from `xmm0` to `xmm7`.
Floating-point values are returned from functions in `xmm0` and, if necessary, `xmm1`.

All `xmm` registers are freely available to use, none of them is reserved for the caller.

### Memory

Floating-point values can be defined in memory following the same semantics as integers of the same size.
NASM (The Netwide Assembler - the assembler used by this track) also allows for declaration of floating-point values in scientific notation.

```nasm
section .data
    pi dq 3.141592653589793 ; this is a double-precision floating-point value
    exp_num dd 1.e5 ; this is a single precision floating-point value equal to 1 * 10⁵
    exp_num2 dd 1.e+5 ; this is a single precision floating-point value equal to 1 * 10⁵
    frac dq 1.e-10 ; this is a double precision floating-point value equal to 1 * 10⁻¹⁰, ie, 0.0000000001
```
