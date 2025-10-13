# Design

## Learning objectives

- Know what is an array.
- Know how to define an array.
- Know how to view a number as an array of its individual bytes.
- Know how to define uninitialized (zeroed-out) data in `section .bss`.
- Know how to define initialized arrays in `section .data` or `section .rodata`.

## Out of Scope

- Loops
- Bit Manipulation (although it can be used here, the idea is to extract and update bytes using only memory access)

## Concepts

- `arrays`

## Prerequisites

- `memory`
- `conditionals`

## Notes

The exercise is inspired by the [C# version of Bird Watcher][csharp-bird-watcher], but it was heavily modified to:

- Focus on arrays without loops.
- Show how to view numbers as arrays and vice-versa.

[csharp-bird-watcher]: https://github.com/exercism/csharp/blob/main/exercises/concept/bird-watcher/.docs/instructions.md
