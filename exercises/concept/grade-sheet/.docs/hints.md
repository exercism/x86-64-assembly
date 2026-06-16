# Hints

## General

- A packed comparison writes a **mask**: every lane is set to all ones where the condition holds and all zeros where it does not.
- Floating-point comparisons take the condition as an immediate, or you can use the NASM pseudo-ops such as `cmpltps` and `cmpeqps`.
- Integer comparisons take the condition as a suffix: `pcmpgtd` for signed greater-than, `pcmpeqd` for equality.
- The blocks are 16-byte aligned, so `movaps` and `movdqa` are both safe.

## 1. Flag the scores above the threshold

- `a > b` is the same as `not (a <= b)` (immediate 6) or as `b < a` (immediate 1, operands swapped).
- Equality must not count as above.

## 2. Flag the perfect scores

- This is a direct floating-point equality with `cmpeqps`.
- Compare the scores against the maxima.
  Each lane is set where they match.

## 3. Assign a rank

- You can define the threshold `50.0` and the rank values `1`, `2` and `3` as packed constants in memory, four lanes each.
- You can define two masks.
  One for "above the threshold", as in task 1 (but against the packed constant `50.0`).
  Another for "perfect score" (as in task 2).
- The basic rank is `1`.
  Rank `2` should be selected for lanes where the above-threshold mask is set.
  Rank `3` should be selected for lanes where the perfect mask is set.
- Perfect scores are also above the threshold.
  If the above-threshold mask is applied first, the perfect mask correctly overrides it where necessary.
- `blendvps` takes its mask from `xmm0`, and selects according to the top bit of each lane.
  For lanes where this bit is set, it selects from the source operand.
  For the others, it keeps the lane already in the destination operand.

## 4. Count the failures

- A rank fails when it is strictly below the threshold, which is `threshold > rank`.
  You may use `pcmpgtd` with the threshold as the destination and the ranks as the source.
- For each block, `movmskps` can be used to collapse the failing mask into a general-purpose register, taking the top bit of each lane.
  This general-purpose register may be 32-bit or 64-bit in size.
- You can use `popcnt` to count the number of bits set in a general-purpose register.
- There may be more than one block, so a loop is necessary to iterate over them and accumulate a result.
- Each block is 16 bytes.

## 5. Did everyone pass?

- "everyone passed" is represented as an all zeros result in the failing mask.
  A single non-zero lane is a false result.
- There may be more than one block, so a loop is necessary to iterate over them and accumulate a result.
- Each block is 16 bytes.
- A `ptest` on a register with itself can be used to check for all zeros.
- An OR operation preserves set bits and an AND operation preserves cleared bits.
  Both can be used to accumulate logic values in a loop.
- A flag may be transformed into a `0/1` result with `setcc`.
