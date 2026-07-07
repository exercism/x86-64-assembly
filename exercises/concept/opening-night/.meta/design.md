# Design

## Learning objectives

- Know that modifying a value in memory is a read-modify-write, not a single indivisible step.
- Know that a read-modify-write on shared memory may lead to a data race.
- Know that `xchg` is automatically atomic when one of the operands is memory.
- Know that the `lock` prefix may be used to turn many instructions atomic.
- Know about using `xadd` as a fetch-and-add.
- Know about using `cmpxchg` to perform a compare-and-swap.
- Know about how x86-64 deals with memory ordering.
- Know how to create a basic spinlock with `xchg` on a binary flag.

## Out of scope

- Fences are only mentioned in `about.md`.
- `cmpxchg16b` is only mentioned in `about.md`.
- Advanced topics on locks and OS-assisted waiting.

## Concepts

- `atomics`

## Prerequisites

- `memory`
- `bit-manipulation`
- `branchless-code`
- `thunks`

## Notes

- The test build needs pthreads.
  Both Linux and macOS systems have built-in support for pthreads, without any external library.
- There is a second test file, `helper.asm`, with a `clobber` function that tests stack alignment and register preservation in task 5 of the exercise.
