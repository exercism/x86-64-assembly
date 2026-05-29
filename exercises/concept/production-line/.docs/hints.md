# Hints

## General

- `movapd` and `movaps` should only be used when a memory operand is known to be aligned.
  They are safe to use when both operands are `xmm` registers.
- Memory addresses are passed as integer values.
  The first six integer arguments are passed to a function in `rdi`, `rsi`, `rdx`, `rcx`, `r8` and `r9`, respectively.

## 1. Combine yields from two lines

- The packed addition for 32-bit floats is `addps`.
- All three pointer arguments are guaranteed to be 16-byte aligned, so the aligned move variant, `movaps`, is appropriate.

## 2. Compute scaled deviation

- The packed subtraction for 64-bit floats is `subpd`.
- The packed multiplication for 64-bit floats is `mulpd`.
- `measured` is aligned and `target` is not, so they need different load variants.

## 3. Calibrate a batch

- Both `reference` and `offset` are aligned, `raw` is not, so they need different load variants.
- Both `reference` and `offset` are needed for both rows.
- Two-operand instructions usually overwrite their destination operand.
- To convert the upper 2 floats of `raw` to doubles, use `cvtps2pd` with a memory operand offset by 8 bytes from the raw pointer.
- The conversion factor should be stored in memory as 2 64-bit floating-point numbers (both equal to `0.5`).
- The result spans 32 bytes (4 64-bit floating-point numbers): the first 16 bytes at `[result]`, the next 16 at `[result + 16]`.

## 4. Normalize scores along a line

- Two-operand instructions usually overwrite their destination operand.
- Memory can't be the destination operand for arithmetic packed instructions.
- For each 64-bit floating-point `score` in the `scores` array (first argument), there is an equivalent `gain` in the `gains` array (second argument).
  Each `score` will operate with the `gain` at the same position.
- The third argument is a fixed `scale` with 2 packed 64-bit floating-point numbers.
- For each pair `score` and `gain`, the function calculates `score * gain / scale_lane`.
  The first lane in `scale` scales the first element of every pair (lanes at even positions), the second lane scales the second (lanes at odd positions).
- The normalized score is stored in-place in the `scores` array, at the same position of its input `score`.
- The number of elements in `scores` and `gains` is the same and equal to the value of `n` (the fourth argument).
- You should use a loop to process all pairs of elements, advancing 16 bytes (2 elements) each iteration.
