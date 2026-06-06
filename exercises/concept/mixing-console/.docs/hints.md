# Hints

## General

- `movdqa` should only be used when a memory operand is known to be aligned.
  It is safe to use when both operands are registers.
- `movdqu` works for any alignment.
- Memory addresses are passed as integer values.
  The first six integer arguments are passed to a function in `rdi`, `rsi`, `rdx`, `rcx`, `r8` and `r9`, respectively.

## 1. Mix two tracks

- The saturating signed addition for 16-bit lanes is `paddsw`.
- All three memory addresses are 16-byte aligned, so the aligned move variant, `movdqa`, is appropriate.
  They can also be used directly as a source operand (but not as the destination).

## 2. Remove bleed

- The saturating signed subtraction for 16-bit lanes is `psubsw`.
- `track` is aligned, but `result` and `bleed` are not guaranteed to be, so they need the unaligned move variant, `movdqu`.

## 3. Combine meters

- The saturating unsigned addition for 8-bit lanes is `paddusb`.
- All three memory addresses are 16-byte aligned, so the aligned move variant, `movdqa`, is appropriate.
  They can also be used directly as a source operand (but not as the destination).

## 4. Apply a fade

- The multiplication that keeps the high 16 bits of a signed 16-bit product is `pmulhw`.
- All three memory addresses are 16-byte aligned, so `movdqa` is appropriate.
  They can also be used directly as a source operand (but not as the destination).
- Both `track` and `gains` are read as signed, which is what `pmulhw` expects.
- Two-operand instructions usually overwrite their destination operand.
- Each 128-bit register holds 8 samples, and `n` (the fourth argument) is always non-zero and a multiple of `8`.
- You should use a loop to process all samples, advancing 16 bytes (8 samples) each iteration.

## 5. Attenuate a track

- Integer SIMD has no packed division, so convert to packed floating-point, divide, then convert back.
- The samples are 16-bit and must be widened to 32-bit before converting to floating-point.
  The signed widening from 16-bit lanes to 32-bit lanes is `pmovsxwd`.
- `pmovsxwd` can take a 64-bit memory operand, loading and widening 4 samples in a single step.
- Convert the widened integers to packed floats with `cvtdq2ps`.
- The divisor is a 32-bit integer already supplied in 4 copies.
  It should be converted to packed floats before used in floating-point division.
- The packed single-precision division is `divps`.
- Convert the quotient back to packed 32-bit integers with `cvttps2dq`, which always truncates toward zero.
- Each result block is 4 32-bit integers, and `n` (the fourth argument) is always non-zero and a multiple of `4`.
- You should use a loop, advancing 8 bytes in `samples` (4 values) and 16 bytes in `result` (4 values) each iteration.
