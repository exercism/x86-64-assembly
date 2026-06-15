# Instructions

You run the marking station for a school, scoring class results a block at a time.

Each block holds 4 results, and the station applies the same operation to every result in the block.
A score is a 32-bit floating-point number.
Several steps work with a **mask**: a block of 4 lanes where each lane is either all ones (a _yes_ for that result) or all zeros (a _no_).

You have five tasks.
You receive the operands through memory addresses.
Some tasks write their answer to a result address, whereas others return it directly.

All memory addresses in this exercise are 16-byte aligned.

~~~~exercism/note
The computations in this exercise should be performed using SIMD instructions.
~~~~

## 1. Flag the scores above the threshold

The first step grades each result against a threshold.
A result clears the bar when its score is strictly **greater** than the threshold.
Any score less than, or equal to, the threshold does not.

Implement the `flag_above_threshold` function, which builds a mask with an all-ones lane for every score above its threshold and an all-zeros lane otherwise.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the 4 mask lanes are written.
- `scores`: memory address of the scores, with 4 32-bit normal floating-point numbers (never `NaN`).
- `thresholds`: memory address of the threshold for each lane, with 4 32-bit normal floating-point numbers (never `NaN`).

```c
scores     = {72.0, 55.0, 90.0, 40.0}
thresholds = {60.0, 60.0, 60.0, 60.0}
result     = {0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000}
```

This function has no return value.

## 2. Flag the perfect scores

A separate report highlights the perfect results, those that reached the maximum possible mark.

Implement the `flag_perfect` function, which builds a mask with an all-ones lane for every score equal to its maximum and an all-zeros lane otherwise.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the 4 mask lanes are written.
- `scores`: memory address of the scores, with 4 32-bit normal floating-point numbers (never `NaN`).
- `maxima`: memory address of the maximum mark for each lane, with 4 32-bit normal floating-point numbers (never `NaN`).

```c
scores = {100.0, 88.0, 100.0, 73.0}
maxima = {100.0, 100.0, 100.0, 100.0}
result = {0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000}
```

This function has no return value.

## 3. Assign a rank

Each score earns a rank from 1 to 3:

- Rank 1 for a score at or below the passing threshold of `50.0`.
- Rank 2 for a score above that threshold but short of the maximum.
- Rank 3 for a perfect score, one that equals the maximum.

Implement the `assign_ranks` function, which writes the rank of each score.

You should define the passing threshold and the rank values as packed constants in memory.
The functions in the two previous tasks may be reused: a score is at least rank 2 when it is above the threshold, and rank 3 when it equals the maximum.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the 4 ranks are written, each a 32-bit unsigned integer.
- `scores`: memory address of the scores, with 4 32-bit normal floating-point numbers (never `NaN`).
- `maxima`: memory address of the maximum mark for each lane, with 4 32-bit normal floating-point numbers (never `NaN`).

```c
scores = {40.0, 75.0, 100.0, 60.0}
maxima = {100.0, 100.0, 100.0, 100.0}
result = {1, 2, 3, 2}
```

This function has no return value.

## 4. Count the failures

Over the year, each student builds up a total rank.
The station tallies how many ranks across the whole cohort fall below a passing threshold, to plan how many extra classes to run.

Implement the `count_failures` function, which returns how many ranks, across every block, are strictly below the passing threshold.
The threshold is given as a block of 4 identical lanes, so you can load it once and reuse it for every block.

This function takes as arguments, in this order:

- `ranks`: memory address of the ranks, a whole number of 4-lane blocks, each rank a 32-bit unsigned integer.
- `block_count`: the number of 4-lane blocks, always greater than `0`.
- `pass_threshold`: memory address of the passing threshold, with 4 identical 32-bit integers.

```c
ranks          = {1, 2, 3, 1, 2, 2, 1, 3} // 2 blocks
block_count    = 2
pass_threshold = {2, 2, 2, 2}
// => 3
```

This function returns the count as a signed 32-bit integer.

## 5. Did everyone pass?

Before the records are filed, the station checks whether the cohort is clean: it passes when not a single result failed in any block.

Implement the `all_passed` function, which returns `1` if all students passed, and `0` otherwise.
A student passes when their corresponding lane in the `failing` array is all zeros.

This function takes as arguments, in this order:

- `failing`: memory address of the failing masks, a whole number of 4-lane blocks, each lane all ones or all zeros.
- `block_count`: the number of 4-lane blocks, always greater than `0`.

```c
failing     = {0x00000000, 0x00000000, 0x00000000, 0x00000000,
               0x00000000, 0x00000000, 0x00000000, 0x00000000} // 2 blocks
block_count = 2
// => 1
```

This function returns the answer as a signed 32-bit integer, either `1` or `0`.
