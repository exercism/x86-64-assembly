# About

There are packed variants for most scalar bitwise operations.
They follow the same general syntax as [SIMD integer operations][simd-integers], but they have no size suffix:

| instruction | description                       |
|-------------|-----------------------------------|
| `pand`      | bitwise AND of two 128-bit values |
| `por`       | bitwise OR of two 128-bit values  |
| `pxor`      | bitwise XOR of two 128-bit values |

Note that there is no packed `NOT`.
However, there is an ANDN operation, which complements (flips all bits in) the **destination** operand and then calculates the AND between both operands.
It can be thought of as a NOT combined with an AND:

| instruction | description                                                     |
|-------------|-----------------------------------------------------------------|
| `pandn`     | bitwise AND of the **complemented** destination with the source |

Note that a bitwise operation combines bits at the same position in two different operands, so lane boundaries cannot change the result.
This is why these instructions do not have a size suffix, the register behaves as a single 128-bit lane:

```x86asm
pand xmm0, xmm1   ; xmm0 = xmm0 AND xmm1
por  xmm2, xmm3   ; xmm2 = xmm2 OR xmm3
pxor xmm4, xmm5   ; xmm4 = xmm4 XOR xmm5
pandn xmm6, xmm7  ; xmm6 = (NOT xmm6) AND xmm7
```

~~~~exercism/note
All instructions in this concept compute bits but set no flags.
A later concept will address conditionals with packed values.
~~~~

## Per-Lane Shifts

Shifts, unlike the pure bitwise operations, do move bits across positions, so they need a lane size to set a boundary.
Within each lane they behave like their scalar counterparts, and bits never cross from one lane into a neighbor:

| instruction               | description                         |
|---------------------------|-------------------------------------|
| `psllw`, `pslld`, `psllq` | shift left logical, per lane        |
| `psrlw`, `psrld`, `psrlq` | shift right logical, per lane       |
| `psraw`, `psrad`          | shift right arithmetic, per lane    |

Note that these instructions follow the syntax for packed integer operations, including a size suffix.
There is no byte-lane shift, only word, dword and, with the exception of shift right arithmetic, qword.

One difference between packed shifts and their scalar counterparts is in the operation name:

- Instead of `shl` and `shr`, we have `sll` and `srl`, for **s**hift **l**eft (**r**ight) **l**ogical.
- Instead of `sar`, we have `sra`, for **s**hift **r**ight **a**rithmetic.

Although the name is different, the operation is the same:

- A logical right shift fills the uppermost bits with zero.
  It is equivalent to an unsigned division by a power of two.
- An arithmetic right shift fills the uppermost bits with the value of the sign bit.
  It is equivalent to a signed division by a power of two, rounding toward negative infinity.
- A shift to the left always fills with zero (this is why there is no need for a shift left arithmetic).

The shift count is the same for every lane.
It can be an immediate, or the low 64 bits of an `xmm` register:

```x86asm
pslld xmm0, 4      ; each 32-bit lane shifted left by 4
psrlw xmm1, 1      ; each 16-bit lane shifted right by 1, zero-filled
psrad xmm2, xmm3   ; each 32-bit lane shifted right by the count in xmm3, sign-filled
```

~~~~exercism/note
A shift count larger than the lane width does not wrap around like the scalar `shl`/`shr` family.
It simply produces zero (or all sign bits, for shift right arithmetic).
~~~~

## Floating-Point Bitwise Operations

Each bitwise instruction also has float-named twins, following the same syntax we have seen for packed floating-point operations:

| integer name | float names          |
|--------------|----------------------|
| `pand`       | `andps`, `andpd`     |
| `pandn`      | `andnps`, `andnpd`   |
| `por`        | `orps`, `orpd`       |
| `pxor`       | `xorps`, `xorpd`     |

Since bitwise operations act on bits, in practice integer and floating-point operations compute the same result.
The different names exist for two reasons:

1. Documenting the intent, in the same way as we would prefer `movdqa`, `movaps` or `movapd` according to the nature of the bytes being copied.
2. Integer and floating-point operations often have different execution domains.
   Operations within the same execution domain can usually be sequenced faster.

There is no shift operation for floating-point values.

## Floating-Point Bit Representation

An [IEEE 754][ieee-754] floating-point number has a very different bit representation from an integer.

In an unsigned integer, each bit has a uniform meaning: it represents a power of two corresponding to the bit index.
The integer is the sum of the powers of two corresponding to the set bits.
This is why shifting the bits can multiply or divide the number by a power of two: we are just changing the index of each set bit.

In a signed integer, most bits are interpreted in the same way as in an unsigned integer.
However, the uppermost bit is special.
If it is set, instead of being added to the others, we have to subtract the corresponding power of two, which results in a negative number.
In practice, to change the sign of a number, we would conceptually need two steps: flipping all bits (a `not`) and then adding 1 to the result (an `inc`).

Bits in floating-point numbers do not have a uniform meaning and they need to be interpreted in very different ways according to their position:

| field    | indexes (32-bit) | indexes (64-bit) |
|----------|------------------|------------------|
| sign     | 31               | 63               |
| exponent | 30-23            | 62-52            |
| fraction | 22-0             | 51-0             |

The resulting number is calculated by `(-1)^sign * 1.fraction * 2^(exponent - bias)`.
The bias depends on the precision:

| size   | bias |
|--------|------|
| 32-bit | 127  |
| 64-bit | 1023 |

In both formats, the sign of the number is exclusively determined by the sign bit.
Changing the sign of a floating-point number is achieved by just flipping this bit (an XOR operation).
Getting the absolute value is achieved by just clearing it (an AND where the bit is cleared):

```x86asm
section .rodata
align 16
abs_mask:  dd 0b0_11111111_11111111111111111111111, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF ; same number in binary and hexadecimal
sign_mask: dd 0b1_00000000_00000000000000000000000, 0x80000000, 0x80000000, 0x80000000 ; same number in binary and hexadecimal

section .text
fn:
  andps xmm0, [rel abs_mask]  ; absolute value: clear the sign bit of all 4 floats
  xorps xmm1, [rel sign_mask] ; negation: flip the sign bit of all 4 floats
  ...
```

Note that in this bit representation, shifting bits does not have a predictable and uniform result.
The fraction can "spill" into the exponent and the exponent, into the sign.

However, it is sometimes convenient to isolate the different parts of the representation to operate on them.

For example, the bits in the exponent should first be interpreted as an unsigned number, before the bias is subtracted from it.
This means we can produce a 32-bit or 64-bit integer whose underlying bit representation corresponds to some power of two in the corresponding floating-point format.
Then this raw bit representation can be used to multiply or divide some other floating-point number.

For example:

```x86asm
mov eax, 210       ; in the exponent position, this would be 2^(210 - 127) = 2^83 in a 32-bit floating-point number
shl eax, 23        ; the bits are now in the correct position for the exponent of a 32-bit floating-point number
movd xmm0, eax     ; we move the raw bits to xmm0
mulss xmm1, xmm0   ; we are multiplying a 32-bit floating-point number in xmm1 by 2^83
```

Conversely, we could extract the exponents of packed floating-point numbers by performing an AND with a mask where the exponent bits are set and all others are cleared.
Combined with a shift and a subtraction, this produces the unbiased exponent of every lane as a signed integer:

```x86asm
section .rodata
align 16
exp_mask: dd 0b0_11111111_00000000000000000000000, 0x7F800000, 0x7F800000, 0x7F800000 ; same number in binary and hexadecimal
bias: dd 127, 127, 127, 127

section .text
fn:
  movdqa xmm0, [rel values]   ; 4 packed 32-bit floating-point numbers
  pand   xmm0, [rel exp_mask] ; keep bits 30-23
  psrld  xmm0, 23             ; slide the exponent field to the bottom of each lane
  psubd  xmm0, [rel bias]     ; remove the bias
  ...
```

~~~~exercism/caution
Operating on the raw bits of floating-point numbers, while useful in some situations, should be done with caution.
The formula above only describes **normal** numbers: an exponent field of all zeros encodes zero and the denormal numbers, and a field of all ones encodes the infinities and NaN.
Adding to, or subtracting from, the exponent field is only safe if there is no over or underflow and if the input number is normal.
Also, adding a valid `x` to the exponent field of `0.0` results in `2^(x - bias)`, not in `0.0 * 2^x`.
~~~~

~~~~exercism/note
The [Float Toy page][toy] has a nice, graphical explanation for how a floating-point numbers' bits are converted to an actual floating-point value.

[toy]: https://evanw.github.io/float-toy
~~~~

## AVX and Beyond

AVX gives every instruction here a `v`-prefixed three-operand form on wider registers, leaving the behavior unchanged:

```x86asm
vpand  ymm0, ymm1, ymm2 ; ymm0 = ymm1 AND ymm2, 256 bits
vxorps ymm3, ymm4, ymm5 ; ymm3 = ymm4 XOR ymm5, 256 bits
vpsrad ymm6, ymm7, 2    ; eight 32-bit lanes shifted right arithmetically
```

AVX2 also introduces variable shifts, with a `v` before the size suffix.
They take a vector of counts, shifting according to the count in the corresponding lane:

```x86asm
vpsllvd ymm0, ymm1, ymm2  ; each 32-bit lane shifted left by its own count
vpsravd ymm3, ymm4, ymm5  ; each 32-bit lane shifted right arithmetically by its own count
```

AVX-512 closes both gaps left open by SSE:

- `vpsraq` finally provides the 64-bit arithmetic right shift.
- `vpternlogd` and `vpternlogq` compute **any** three-input bitwise function in one instruction.
  The 8-bit immediate is the truth table itself: bit `i` of the immediate is the output for input combination `i`.
  Every chain of `pand`/`pandn`/`por`/`pxor` over three operands collapses into a single `vpternlog`.

These extensions are mentioned for completeness.
The exercises in this track use the SSE forms.

~~~~exercism/note
A full reference for every instruction mentioned here is available in the [x86 instruction reference][instruction-reference].

[instruction-reference]: https://www.felixcloutier.com/x86/
~~~~

[simd-integers]: https://exercism.org/tracks/x86-64-assembly/concepts/simd-integers
[ieee-754]: https://en.wikipedia.org/wiki/IEEE_754
