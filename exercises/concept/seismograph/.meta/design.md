# Design

## Learning objectives

- Know the packed bitwise instructions `pand`, `pandn`, `por` and `pxor`, and their float-named twins.
- Know that bitwise operations have no lane size, and why.
- Know the sign-bit idioms for floating-point absolute value (`andps`) and negation (`xorps`).
- Know the per-lane shift instructions and the logical/arithmetic split (`psrld` vs `psrad`).
- Know how to pass a runtime shift count to a packed shift (`movq` into an `xmm` register).
- Know the bit layout of 32-bit and 64-bit floating-point numbers and how to extract or construct their exponent field with mask, shift and subtract.

## Out of Scope

- Packed comparisons, masks and blending, including `ptest`.
- Cross-lane data movement (`pslldq`/`psrldq`).
- Horizontal reductions.

## Concepts

- `simd-bitwise`

## Prerequisites

- `simd-integers`
- `bit-manipulation`
