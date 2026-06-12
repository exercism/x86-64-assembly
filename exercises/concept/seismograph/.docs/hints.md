# Hints

## General

- All memory addresses in this exercise are 16-byte aligned, so the aligned move variants (`movaps` for floats, `movdqa` for integers) are appropriate.
  Aligned memory can also be used directly as a source operand (but not as the destination).
- Masks can be defined in memory.

## 1. Rectify the trace

- The sign of a 32-bit floating-point number is its top bit.
  Clearing the uppermost bit makes the number non-negative.
- It is possible to clear the uppermost bit by ANDing with a 32-bit number where all bits are set except the uppermost one.
- A mask can be defined in memory with 4 packed 32-bit numbers.
- The instruction `andps` applies AND to floating-point values.

## 2. Read the scale of a tremor

- The exponent field in a 32-bit IEEE-754 floating-point number is in the bits at positions 23 to 30, inclusive.
- The exponent bits can be isolated by ANDing (`andps` or `pand`) the floats with a mask where only bits 23 to 30 are set.
- Once the exponent bits are isolated, they can be slid to the bottom of each lane with a shift right logical (`psrld`).
- The bias for a 32-bit IEEE-754 float is 127.
  It can be removed by subtracting 127 from each lane (`psubd`).

## 3. Coarsen the resolution

- A shift right arithmetic (`psrad`) by `n` divides by `2^n` while preserving the sign and rounding toward negative infinity.
- The packed shift instructions take their count from an immediate or from an `xmm` register, not from a general-purpose register (GPR).
- The instruction `movq` may be used to move raw 64 bits from a GPR to an `xmm` register.

## 4. Gate the channels

- `por` can be used to combine all bits set in either campaign.
- `pandn` computes ((NOT destination) AND source) in a single instruction.
  It can be used to clear all bits in source that are set in the destination.

## 5. Toggle the calibration bits

- To flip only unlocked bits, all locked bits must be first zeroed in the toggle.
- `pandn` computes ((NOT destination) AND source) in a single instruction.
  It can be used to clear all bits in source that are set in the destination.
- `pxor` can be used to flip the bits selected by the remaining toggle in each status word.

## 6. Amplify the trace

- The exponent field in a 32-bit IEEE-754 floating-point number is in the bits at positions 23 to 30, inclusive.
  To move the gain `k` to the right position, it should be shifted to the left.
- Adding the shifted gains onto the readings' raw bits (`paddd`) has the effect of multiplying the reading by `2^k`.
  The bit pattern stays valid because inputs and results are guaranteed normal.
