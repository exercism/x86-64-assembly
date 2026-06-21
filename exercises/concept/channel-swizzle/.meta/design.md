# Design

## Learning objectives

- Know how to shuffle lanes from a source operand into a destination operand.
- Know how to use shuffling instructions to broadcast a lane from the source operand into all lanes of the destination operand.
- Know how to interleave lanes from two operands, with or without narrowing.
- Know how to insert a value taken from a general-purpose register into a chosen lane of a `xmm` register.
- Know how to extract a value from a chosen lane of a `xmm` register into a general-purpose register.
- Know about byte shifts across the full `xmm` register.

## Out of Scope

- Horizontal and collapsing reductions.
- AVX and AVX-512 beyond a short closing overview.

## Concepts

- `simd-cross-lane`

## Prerequisites

- `simd-masks`

## Notes

- Some content was moved only to `about.md`, to reduce cognitive load on students in a first take.
  This includes integer shuffles using words, byte shifts and insert/extract involving floats.
- The concept exercise reuses the icon of `circular-buffer`.
