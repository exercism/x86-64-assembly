# About

Every SIMD operation so far has acted _lane by lane_.
The value in lane `i` of the result is computed on the lane `i` of the inputs.

However, there are many situations when moving values between lanes is necessary or desired.
For example, the lanes may be out of order for the computation we need to perform.

There are many SIMD instructions that move data across lanes in different ways.

## Shuffling

A **shuffle** reorders the bytes or lanes of a register, drawing each destination lane from a source lane that may sit anywhere.
They can select the same lane to different destinations, which makes them capable of also broadcasting values.

The shuffling instructions behave differently according to their size and execution domain.

### Selecting Lanes With an Immediate

The instruction `pshufd` rearranges the four 32-bit lanes of its source into its destination.

The selection is an 8-bit immediate, read as four 2-bit fields, one per destination lane.
Each field selects which of the four source lanes to copy into that destination lane:

| field | lane index |
|-------|------------|
| `00`  | `0`        |
| `01`  | `1`        |
| `10`  | `2`        |
| `11`  | `3`        |

The position of the field in the immediate, read right-to-left, indicates where the selected lane is inserted.
A source lane may be selected more than once, which is how a single lane is broadcast across the whole register:

```x86asm
; The bit fields are read right-to-left
pshufd xmm1, xmm0, 0b00_01_10_11 ; reverse: lane 0 takes source 0b11 (3), lane 1 takes source 0b10 (2), and so on
pshufd xmm3, xmm2, 0b00_00_00_00 ; broadcast source lane 0 into all four lanes
```

There are two shuffle variants for 16-bit lanes.
`pshuflw` permutes the low four words and copies the high four unchanged, while `pshufhw` permutes the high four words and copies the low four unchanged.
Both reuse the same 8-bit immediate of four 2-bit fields:

```x86asm
pshuflw xmm0, xmm0, 0b00_01_10_11 ; reverse the low four words; the high four are copied unchanged
pshufhw xmm1, xmm1, 0b00_01_10_11 ; reverse the high four words; the low four are copied unchanged
```

### Shuffling Floating-Point Lanes

There are two floating-point shuffle instructions, following the same general syntax: `shuf` + `p` + the size suffix (either `s` or `d`).

They also use an immediate to select the lanes.
`shufps` uses the same 2-bit field encoding as the previous integer shuffles.
However, since there are only 2 64-bit lanes in a 128-bit operand, `shufpd` uses only a 1-bit field encoding.

These instructions differ from their integer counterparts in that they draw the lanes from _two_ operands rather than one:

- The low half of the result is taken from the destination operand.
- The high half is taken from the source operand.

```x86asm
shufps xmm0, xmm1, 0b11_10_01_00 ; xmm0 = {xmm0[0], xmm0[1], xmm1[2], xmm1[3]}
shufps xmm2, xmm3, 0b00_00_00_00 ; xmm2 = {xmm2[0], xmm2[0], xmm3[0], xmm3[0]}
shufpd xmm4, xmm5, 0b0_1         ; xmm4 = {xmm4[1], xmm5[0]}
```

Because both operands feed the result, they can be used to interleave two vectors in one step.
If both source and destination are the same register, every lane is drawn from it.

### The Byte Shuffle

`pshufb` is the most general shuffle.
Even though `pshufb` and `pshufd` have very similar names, differing only on the size suffix, they perform very different operations.

First, while `pshufd` uses an immediate to select lane positions, `pshufb` uses a **control vector** in the source operand.
This control vector is a `xmm` register or a 16-byte memory operand.

For each of the 16 destination lanes, the low four bits of the control vector give a source byte index, 0 to 15.
If lane `i` of the control vector holds the source byte index `j`, then the `j-th` lane of the destination will be moved to the `i-th` lane.

This highlights a second difference between the two instructions.
While `pshufd` takes the shuffling lanes from a different source operand, `pshufb` performs the shuffling in-place in the destination.

```x86asm
section .rodata
align 16
reverse: db 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

section .text
fn:
  pshufb xmm0, [rel reverse]
  ; xmm0[0] = xmm0[reverse[0]] (xmm0[15])
  ; xmm0[1] = xmm0[reverse[1]] (xmm0[14])
  ; ...
  ; in the end, the bytes in xmm0 are reversed
```

`pshufb` is even more flexible than that: it can clear any of the lanes.
If the top bit is set in a lane `i` of the control vector, then the lane `i` of the destination is zeroed-out.
This makes `pshufb` both an arbitrary byte permutation and a selective clear, in a single instruction.

Since `pshufb` acts on a byte granularity, it can also be used to shuffle lanes of different sizes, by grouping neighboring lanes together.
For example, it can be used to shuffle dwords:

```x86asm
section .rodata
align 16
input: dd 13, 25, 37, 49 ; each number takes 4 bytes
reverse_dwords: db 12, 13, 14, 15, 8, 9, 10, 11, 4, 5, 6, 7, 0, 1, 2, 3 ; aligned too, since input spans 16 bytes

section .text
fn:
  movdqa xmm0, [rel input] ; xmm0 = {13, 25, 37, 49}
  pshufb xmm0, [rel reverse_dwords]
  ; xmm0 = {49, 37, 25, 13}
```

As in the examples above, `pshufb` can be thought of as a permutation of some variable data.
In that case, `pshufb` performs similarly to other shuffles, but with the advantage of being able to compute the permutation pattern at runtime.

The instruction is also commonly used for fast table lookup.
In that case, the control vector holds variable indices, possibly hashed from an initial value, and a 16-entry table is loaded on the data register.
After the shuffle, each lane in the destination will hold the entry corresponding to its index.

For example, it can be used to select only valid bytes of a string, after aligning-down its address to avoid crossing a page boundary:

```x86asm
section .rodata
tab: db 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
     times 16 db 0x80

section .text
fn:
  ; assume the string is passed on rsi
  mov rax, rsi
  and rsi, -16 ; align-down rsi, it is now safe to load 16 bytes out of it
  and rax, 15  ; the number of garbage bytes loaded by rsi, before the start of the string

  lea r10, [rel tab]
  movdqa xmm0, [rsi]       ; rsi is 16-byte aligned
  movdqu xmm1, [r10 + rax]
  pshufb xmm0, xmm1        ; only string bytes are selected and put in the low lanes of xmm0
                           ; other bytes are cleared (the top bit of 0x80 is set)
  ...
```

## Interleaving Lanes

The **unpack** instructions take lanes from two operands and weave them together, alternating between the two.
There are integer and float variants and they largely follow the same general syntax structure, with two differences:

1. There is an `l` or `h` suffix to indicate if it acts on the low half (`l`) or the high half (`h`) of each operand.
2. The integer variants take two size suffixes, the second representing twice the first.
   For example, `bw` or `qdq` (the size suffix for 16 bytes is `dq`, as in `movdqu`).

```x86asm
punpcklwd xmm0, xmm1 ; p + unpck + l + wd
; this interleaves the first 4 words of xmm0 and xmm1 into 4 dwords
; for each dword in the result, the first word is taken from xmm0 and the second, from xmm1
; xmm0 = {xmm0[0], xmm1[0], xmm0[1], xmm1[1], xmm0[2], xmm1[2], xmm0[3], xmm1[3]}

unpckhps xmm2, xmm3 ; unpck + h + p + s
; this interleaves the high 32-bit floats of xmm2 and xmm3
; xmm2 = {xmm2[2], xmm3[2], xmm2[3], xmm3[3]}
```

Unpacking is the building block of a register transpose.
For example, for a 2x2 matrix in registers xmm0 and xmm1:

```x86asm
; xmm0 = {1, 2} as qwords -> first row
; xmm1 = {3, 4} as qwords -> second row
movdqa xmm2, xmm0
punpcklqdq xmm0, xmm1 ; xmm0 = {1, 3} -> first row of transpose
punpckhqdq xmm2, xmm1 ; xmm2 = {2, 4} -> second row of transpose
```

## Narrowing With Saturation

The **pack** instructions run the other direction, combining the lanes of two operands into half-width lanes of the destination.

These instructions do not take a `p` prefix.
Other than that, the syntax combines elements we have already seen:

- the operation being performed, `pack`.
- an `s` or `u` to indicate if the output values are _signed_ or _unsigned_, respectively.
- an `s` for _saturating_, as in the [saturating arithmetic][simd-integers] seen in a previous concept.
- two size suffixes, the second indicating _half_ the width of the first (the opposite behavior to `unpck`).

Since the _pack_ operation is narrowing, it does not need an `l` or `h` suffix:

```x86asm
packssdw xmm0, xmm1 ; pack + s (for signed) + s (for saturating) + dw (dword to word)
packuswb xmm2, xmm3 ; pack + u (for unsigned) + s (for saturating) + wb (word to byte)
```

These instructions are **saturating**, i.e., the output values are clamped to the narrower range.
They operate from dword to word and from word to byte.
There is no qword to dword variant.

Note that the input is always interpreted as signed.
The type, either signed or unsigned, is for the _output_.
It indicates the range to be clamped.
For example, `packsswb` clamps to the range of a signed byte, i.e., `[-128, 127]`.

The four variants differ only in the lane widths and the range they clamp to:

| instruction | input lanes   | output lanes   | clamp range       |
|-------------|---------------|----------------|-------------------|
| `packsswb`  | signed words  | signed bytes   | `[-128, 127]`     |
| `packuswb`  | signed words  | unsigned bytes | `[0, 255]`        |
| `packssdw`  | signed dwords | signed words   | `[-32768, 32767]` |
| `packusdw`  | signed dwords | unsigned words | `[0, 65535]`      |

The low lanes of the result come from the destination operand and the high lanes from the source:

```x86asm
packusdw xmm0, xmm1   ; 8 words, each clamped to 0..65535
; xmm0 = {xmm0[0], xmm0[1], xmm0[2], xmm0[3], xmm1[0], xmm1[1], xmm1[2], xmm1[3]}
```

There is no floating-point equivalent for these instructions, because narrowing a float is a conversion, not a clamp.
`cvtpd2ps` converts two doubles to two singles in the low half of the destination.
Combining the results of two such conversions fills a full register.

## Shifting the Whole Register

Earlier concepts shifted each lane independently.
Two instructions instead treat the entire 128-bit register as one large value: `pslldq` shifts it left and `psrldq` shifts it right.
Their count is an immediate measured in **bytes**, not bits, and the vacated bytes are filled with zeros:

```x86asm
pslldq xmm0, 3 ; shift the whole register left by 3 bytes, zero-filling the low end
psrldq xmm1, 4 ; shift the whole register right by 4 bytes, zero-filling the high end
```

The `dq` suffix here stands for `double-qword`, as in `movdqu`.
This means these instructions treat the whole register as a single lane, moving bytes across the full width.

There is no form that takes the count in a register.
When the count is only known at run time, the shift can be emulated with `pshufb` and a control vector sliced out of a precomputed table.
This can be used to extract valid bytes out of an aligned-down string address:

```x86asm
section .rodata
align 16
shift_table: db 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
             db 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80

section .text
fn:
   ; rsi holds the address of a variable-length string
   ; loading the string directly may cause a page fault

   mov rcx, rsi
   and rsi, -16 ; address is now aligned to 16 bytes
   and rcx, 15  ; rcx now holds the count from rsi to the start of the string

   lea rdx, [rel shift_table]
   movdqu xmm1, [rdx + rcx]   ; control = {count, count+1, ..., 15, then 0x80 bytes}
   movdqa xmm0, [rsi]         ; rsi is 16-byte aligned

   ; there may be garbage bytes at the start of xmm0

   pshufb xmm0, xmm1          ; right-shift xmm0 by rcx bytes, bytes past the end are zeroed

   ; now xmm0 holds only valid bytes at the beginning, invalid bytes are zeroed-out
```

## Moving Individual Lanes

Until now, we have always moved data between a SIMD register and a general-purpose register using [`movq`/`movd`][simd].
These instructions can only write to, or read from, the low lane of a SIMD register, and, when writing, they clear all other lanes.

There are instructions that do the same for any lane, not only the first, leaving other lanes untouched:

- the **insert** instructions write one element from a general-purpose register, or memory, into a lane chosen by an immediate.
- the **extract** instructions read from one lane out into a general-purpose register.

Both follow the integer syntax: `p` + `insr`/`extr` + the size suffix (`b`, `w`, `d`, or `q`).

In both cases, the general-purpose register is usually 32-bit wide.
Only `pinsrq` and `pextrq` need a 64-bit operand.
A memory operand is always of the size of the operation: 8-bit for `pinsrb/pextrb`, 16-bit for `pinsrw/pextrw`, and so on.

```x86asm
pinsrb xmm0, eax, 5        ; replace byte 5 of xmm0 with the low byte of eax
pextrb byte [rdx], xmm0, 5 ; copy byte 5 of xmm0 into the memory location indicated by rdx
```

Note that these instructions, much like `movd` and `movq`, simply move raw bytes.
This means they can also be used for floating-point values stored in memory or in a general-purpose register.

For 32-bit floats specifically there is a more capable pair.

`insertps` copies one 32-bit lane from a source into a chosen lane of the destination.
Unlike `pinsrd`, `insertps` takes its source lane from another SIMD register or from memory, not from a general-purpose register.

This instruction uses an immediate to select both the source lane and its position at the destination.
It can also clear any destination lane in the same step.

Unlike, for example, `pshufd`, the bits in the destination should be read left-to-right:

- Bits 7-6 indicate the source lane.
- Bits 5-4 indicate the destination lane.
- Bits 3-0 form a mask to indicate which destination lanes should be cleared, if any.
  Each set bit in this mask clears the lane corresponding to its index.

```x86asm
insertps xmm0, xmm1, 0b01_00_1100 ; copies lane 1 (0b01) from xmm1 into lane 0 (0b00) of xmm0
; also clears lanes 2 and 3 of xmm0, keeping lane 1 unchanged
```

`extractps` copies the bits of one 32-bit lane out into a general-purpose register or memory.

```x86asm
extractps eax, xmm0, 2            ; copy the bits of lane 2 into eax
```

Note that both floating-point variants use the full name of the operation, unlike their integer counterparts:

- `insertps`, not `insrps`
- `extractps`, not `extrps`

## AVX and Beyond

AVX gives every instruction here a `v`-prefixed form, most with a non-destructive three-operand syntax, operating on 256-bit `ymm` registers.
AVX-512 extends them to 512-bit `zmm` registers with per-lane mask predication.

```x86asm
vpshufd    ymm0, ymm1, 0b00_01_10_11 ; reverse the dwords within each 128-bit lane
vpunpcklbw ymm2, ymm3, ymm4          ; interleave low bytes within each 128-bit lane
vshufps    ymm5, ymm6, ymm7, 0b11_10_01_00
```

The important subtlety is that the wide forms of these instructions operate **within each 128-bit lane independently**.
They all treat a 256-bit register as two separate 128-bit halves and never move a byte across the boundary between them.
A 256-bit `vpshufb` is really two 128-bit shuffles side by side.

Crossing that boundary needs dedicated cross-lane permutes:

- `vperm2i128` and `vperm2f128` select and swap whole 128-bit halves.
- `vpermq` and `vpermpd` permute 64-bit lanes across the register using an immediate.
- `vpermd` and `vpermps` permute 32-bit lanes using indices taken from a vector.
- AVX-512 adds byte and word permutes such as `vpermb` and `vpermw`, and the two-source `vpermt2*` family.

Cross-lane permutes usually cost a few cycles more of latency than the in-lane shuffles, though their throughput is similar.
For a full reference, you may check the [Agner Fog's instruction tables][agner].

These extensions are mentioned for completeness.
The exercises in this track use the SSE forms.

~~~~exercism/note
A full reference for every instruction mentioned here is available in the [x86 instruction reference][instruction-reference].

[instruction-reference]: https://www.felixcloutier.com/x86/
~~~~

[simd]: https://exercism.org/tracks/x86-64-assembly/concepts/simd
[simd-integers]: https://exercism.org/tracks/x86-64-assembly/concepts/simd-integers
[agner]: https://www.agner.org/optimize/instruction_tables.pdf
