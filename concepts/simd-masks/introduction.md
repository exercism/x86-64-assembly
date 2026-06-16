# Introduction

Scalar code relies on flags set by various instructions to branch in response to a certain condition.
Packed values, however, represent not one but many values in parallel.
A single condition may fail for one lane and succeed for another.

This is why SIMD code is _branchless_ by default.

Instead of relying on flags, packed comparisons usually produce a **mask** into the destination operand.
For each lane, the comparison fills the whole lane with ones when it is true and with zeros when it is false.
Read as a signed integer, a true lane is `-1` and a false lane is `0`.

This mask can then be composed with bitwise operations to filter specific lanes.

## Packed Comparisons

A scalar `cmp` is generic in the sense that it is used to set various flags at the same time.
Another instruction can then consume those flags to either branch or perform computations.

However, since a packed comparison both checks a condition and computes a mask, it is not generic.
The comparison must be given the exact condition being tested.

There are two ways to do that:

- Integer comparisons are given the condition as a suffix: `eq` for equality, and `gt` for greater-than.
  Other variants are constructed by composing the result of one of these.
- Floating-point comparisons are given the condition encoded in an immediate.
  Different values of this immediate correspond to different conditions being tested.

Other than the use of a specific conditional suffix on integer comparisons, the syntax follows the same structure we have already seen:

- For integers, `p` + `cmp` + condition + size (`b`, `w`, `d` or `q`).
- For floats, `cmp` + `p` + size (`s` or `d`).
  The condition is passed in an immediate as an extra operand.

### Integer Comparisons

As mentioned, there are only integer comparisons for equality and greater-than:

| instruction                                | description                      |
|--------------------------------------------|----------------------------------|
| `pcmpeqb`, `pcmpeqw`, `pcmpeqd`, `pcmpeqq` | per-lane equality                |
| `pcmpgtb`, `pcmpgtw`, `pcmpgtd`, `pcmpgtq` | per-lane **signed** greater-than |

```x86asm
movdqa  xmm0, [rel scores]
pcmpgtd xmm0, [rel threshold] ; lane i = 0xFFFFFFFF (-1) if scores[i] > threshold[i], else 0
```

To create a less-than comparison, use `gt` with the operands swapped: `a < b` == `b > a`.

Note that the comparison is **signed**.
To perform an unsigned comparison, flip the top bit of both operands.
This can be done with an XOR with a mask where only the top bit is set.

~~~~exercism/note
Two handy idioms are:

1. XORing a register with itself to produce all zeros.
2. Comparing a register with itself to produce all ones.

For example:

```x86asm
pxor xmm4, xmm4    ; xmm4 = all zeros
pcmpeqd xmm7, xmm7 ; xmm7 = all ones
```

All-zeros and all-ones are common masks to encode "false everywhere" and "true everywhere", respectively.
They can also be used to represent packed `0` or packed `-1`, which are common sentinel values.
For example, the NUL that marks the end of a string is a `0`.
~~~~

### Floating-Point Comparisons

Floating-point lanes use a different shape: one instruction, `cmpps` (and `cmppd` for 64-bit lanes), with the condition as an immediate:

```x86asm
movaps xmm0, [rel readings]
cmpps  xmm0, [rel limits], 1 ; condition 1 is "less than": lane i = all ones if readings[i] < limits[i]
```

NASM also has pseudo-ops that map to the correct immediate and are easier to remember.
In all of the following, `x` in `px` can be `s` (32-bit floats) or `d` (64-bit floats):

| pseudo-op 	 | immediate | comparison             |
|--------------|-----------|------------------------|
| `cmpeqpx`    | 0         | a == b                 |
| `cmpltpx`    | 1         | a <  b                 |
| `cmplepx`    | 2         | a <= b                 |
| `cmpunordpx` | 3         | a is NaN or b is NaN   |
| `cmpneqpx`   | 4         | a != b                 |
| `cmpnltpx`   | 5         | a >= b                 |
| `cmpnlepx`   | 6         | a >  b                 |
| `cmpordpx`   | 7         | neither a nor b is NaN |

## Selecting With a Mask

A mask encodes the result of a condition.
It can then be used for choosing, lane by lane, between two sets of values according to that condition.
We take the lane from one value where the mask is true, from another where it is false:

```x86asm
; result = (a AND mask) OR (b AND NOT mask)
movdqa xmm2, xmm0  ; xmm0 holds the mask, keep a copy
pand   xmm2, xmm3  ; xmm2 = a AND mask: lanes of a where mask is true
pandn  xmm0, xmm4  ; xmm0 = NOT mask AND b: lanes of b where mask is false
por    xmm2, xmm0  ; combine the two halves
```

Note that the `pandn` asymmetry pays off here: the mask sits in the destination, gets negated, and selects from `b` in a single instruction.

This pattern is the packed form of branchless selection.
Every lane is computed, and the mask alone decides which value survives, with no `jcc` anywhere.

## Dedicated Blends

There are instructions that perform that same selection directly, reading one bit per element from a mask register.
They are called **blend** instructions:

| instruction | element     | mask source     |
|-------------|-------------|-----------------|
| `pblendvb`  | byte        | implicit `xmm0` |
| `blendvps`  | 32-bit lane | implicit `xmm0` |
| `blendvpd`  | 64-bit lane | implicit `xmm0` |

Note that the first instruction follows the integer syntax, whereas the other two follow the float syntax.
However, since these instructions simply select raw bytes, any of them can be used with both integers and floats.

For each element, the blend keeps the destination when the top bit of the matching mask element is clear, and takes the source when it is set.
Only that **top bit** is consulted, which a comparison mask satisfies, since its lanes are all ones or all zeros.
The mask register is always `xmm0`, which is implicit:

```x86asm
movaps   xmm0, [rel mask]  ; the selecting mask must be in xmm0
movaps   xmm1, [rel b]     ; destination: kept where the mask bit is clear
blendvps xmm1, [rel a]     ; source: taken where the mask bit is set
```

It is also possible to use `pblendvb` to select lanes from a comparison mask for any other size.
Since all bytes in a true lane are all ones, `pblendvb` selects all of them.

~~~~exercism/note
These instructions all add `v` after the operation being performed (`blend`).
This `v` stands for _variable_, because the selection is not static: it depends on a register.

There are also variants without `v`, that select according to an immediate.
They follow the same pattern, selecting a lane `i` if the bit `i` of the immediate is set.
~~~~

## From a Mask Back to a Scalar

Although powerful, SIMD code lacks much of the flexibility of scalar code.
In many situations, it is necessary to move from a packed register back to the world of scalar instructions.

The family of instructions `movmsk` serves as a bridge between the two worlds.
These instructions extract the **top bit** of every lane into a general-purpose register:

| instruction | gathers                     | result width |
|-------------|-----------------------------|--------------|
| `pmovmskb`  | top bit of each of 16 bytes | 16 bits      |
| `movmskps`  | top bit of each of 4 dwords | 4 bits       |
| `movmskpd`  | top bit of each of 2 qwords | 2 bits       |

If used after a comparison, each set bit represents a "true" lane and each cleared bit, a "false" lane.
This result can then be manipulated as usual with scalar instructions.
For example, a `popcnt` counts the number of matches, and `tzcnt` finds the first.

The general-purpose register may be 32-bit or 64-bit wide.

## Testing a Whole Vector

There is also a packed variant of the `test` scalar instruction: `ptest`.

It is similar to its scalar counterpart in that it performs an AND operation between two operands, without modifying them.
Unlike `test`, `ptest` also performs an ANDN operation, negating the first operand.

Thus, `ptest` can be thought of as a non-destructive version of `pand` and `pandn` that sets flags according to the result.
In much the same way as these two instructions, `ptest` treats the whole SIMD register as a single lane and so it does not take a size prefix.

If the result of an AND operation is `0`, the `ZF` is set, and if the ANDN operation results in `0`, it is `CF` that is set.
This means that `ptest` can be used to check for both an all-ones and an all-zeros mask:

1. Using `ptest` on a register with itself sets `ZF` only if the register is all zeros.
   This mimics the common scalar idiom of using `test` on a register with itself to check for `0`.
2. Using `ptest` on a register with an all-ones mask sets `CF` only if the register is all ones.
   Also, it sets `ZF` only if the register is all zeros, making it possible to check for both masks at once.

```x86asm
pxor    xmm0, xmm0   ; all zeros
pcmpeqb xmm1, xmm1   ; all ones
pcmpeqb xmm2, xmm2

ptest xmm0, xmm0     ; ZF set: a register against itself detects all zeros
ptest xmm0, xmm1     ; ZF set, CF clear: xmm0 is all zeros, not all ones
ptest xmm2, xmm1     ; CF is set only if xmm2 is all ones
```

The result of a `ptest` can be used to branch or in branchless instructions such as `setcc` or `cmovcc`, as usual.
