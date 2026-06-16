# Design

## Learning objectives

- Know that a packed comparison produces a per-lane mask (all ones or all zeros), not flags in `rflags`.
- Know packed comparison instructions, both for integers and for floating-point values.
- Know how to select between two blocks with a mask using SIMD bitwise operations or blend instructions.
- Know how to collapse a mask into a general-purpose register with `movmsk` instructions.
- Know how to reduce a whole mask to a scalar branch with `ptest` and its `ZF`/`CF` semantics.

## Out of Scope

- Cross-lane data movement and shuffles.
- Horizontal reductions.

## Concepts

- `simd-masks`

## Prerequisites

- `simd-bitwise`
- `branchless-code`

## Notes

- The concept exercise uses the same icon as the practice exercise `grade-school`.
