# Instructions

You maintain the processing station of a seismograph array, a network of sensors that record how the ground moves.

Readings arrive as blocks of values.
Some are ground displacements stored as 32-bit floating-point numbers, others are raw counts and status words stored as 32-bit integers.
The station processes a whole block at once, applying the same operation to each value.

You have five tasks, each operating on a block of values held in memory.
You receive the operands through memory addresses and write your answer through a result address.
All memory addresses in this exercise are 16-byte aligned.

~~~~exercism/note
The computations in this exercise should be performed using SIMD bitwise and shifts, not scalar operations.
~~~~

## 1. Rectify the trace

For magnitude analysis, only the size of each ground displacement matters, not its direction.
The first processing step folds every reading to a non-negative value.

Implement the `rectify_trace` function, which computes the absolute value of each reading.
A block holds 4 readings, each a 32-bit floating-point number.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the 4 rectified readings are written.
- `trace`: memory address of the recorded readings, with 4 values, each a 32-bit floating-point number.

```c
trace  = {1.5, -2.25, 0.0, -135.75}
result = {1.5,  2.25, 0.0,  135.75}
```

This function has no return value.

## 2. Read the scale of a tremor

Analysts grade tremors by their power of two: a reading near `8.0` sits at scale `3`, a reading near `0.25` sits at scale `-2`.
That scale is already stored inside each floating-point number, as its exponent field.

A 32-bit floating-point number is laid out as a sign bit at bit 31, an 8-bit exponent at bits 30 to 23, and a 23-bit fraction at bits 22 to 0.
The stored exponent is biased by 127, so the value of the number is `(-1)^sign * 1.fraction * 2^(exponent - 127)`.

Implement the `reading_scale` function, which extracts the unbiased exponent of each reading as a signed 32-bit integer.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the 4 scales are written, each a signed 32-bit integer.
- `trace`: memory address of the rectified readings, with 4 values, each a 32-bit floating-point number.

```c
trace  = {8.0, 0.25, 1.0, 13.5}
result = {  3,   -2,   0,   3}
```

This function has no return value.
All readings are normal, non-zero floating-point numbers.

## 3. Coarsen the resolution

For long-term storage, raw displacement counts are kept at a coarser resolution: each count is divided by a power of two.

Displacement counts are signed: the ground can move both ways.
Dividing them correctly takes the shift that preserves the sign.

Implement the `coarsen_displacements` function, which divides each signed count by `2^shift`, rounding toward negative infinity.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the 4 coarsened counts are written, each a signed 32-bit integer.
- `counts`: memory address of the raw counts, with 4 signed 32-bit integers.
- `shift`: the power of two to divide by, as a 64-bit unsigned integer between `0` and `31`.

```c
counts = {1024, -1024, 25, -25}
shift  = 3
result = { 128,  -128,  3,  -4}
```

~~~~exercism/note
The instruction `movq` may be used to copy a 64-bit integer from a general-purpose register to a `xmm` register without changing the underlying bit representation.
~~~~

This function has no return value.

## 4. Gate the channels

Each station merges two recording campaigns and then silences the channels its hardware report marks as faulty.
Each block holds 4 channel masks, each an unsigned 32-bit integer, where every bit represents one channel: `1` enabled, `0` disabled.

Implement the `gate_channels` function, which combines the channels enabled in either campaign, then clears every channel marked faulty.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the 4 gated masks are written, each an unsigned 32-bit integer.
- `enable_a`: memory address of the first campaign's enable masks, with 4 unsigned 32-bit integers.
- `enable_b`: memory address of the second campaign's enable masks, with 4 unsigned 32-bit integers.
- `faulty`: memory address of the faulty-channel masks, with 4 unsigned 32-bit integers.

```c
enable_a = {0b1100, 0b0001, 0b1111, 0b0000}
enable_b = {0b0110, 0b0001, 0b0000, 0b0000}
faulty   = {0b0100, 0b0011, 0b1001, 0b1111}
result   = {0b1010, 0b0000, 0b0110, 0b0000}
```

This function has no return value.

## 5. Toggle the calibration bits

Once a day the station runs a calibration pass, flipping a chosen set of configuration bits in each status word and leaving every other bit untouched.
But some bits are locked by the hardware and must never change, no matter what the pass requests.
Running the same pass twice restores the original configuration.

Implement the `toggle_calibration` function, which flips, in each status word, exactly the bits that are set in the matching toggle mask and not set in the matching lock mask.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the 4 updated status words are written, each an unsigned 32-bit integer.
- `status`: memory address of the current status words, with 4 unsigned 32-bit integers.
- `toggle`: memory address of the toggle masks, with 4 unsigned 32-bit integers.
- `locked`: memory address of the lock masks, with 4 unsigned 32-bit integers.

```c
status = {0b1100, 0b0001, 0b1111, 0b1010}
toggle = {0b0110, 0b0011, 0b1111, 0b1010}
locked = {0b0010, 0b0001, 0b1100, 0b0000}
result = {0b1000, 0b0011, 0b1100, 0b0000}
```

This function has no return value.

## 6. Amplify the trace

Each channel of the array has its own gain trim, expressed as a power of two: a gain of `3` multiplies the channel's reading by `8`, a gain of `-5` divides it by `32`.

The station applies these gains without a single floating-point multiplication.
A floating-point number is scaled by `2^k` by adding `k` directly to its exponent field: shift `k` into position and add it to the raw bits.

Implement the `amplify_trace` function, which multiplies each reading by `2` raised to its channel's gain, operating only on the raw bits.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the 4 amplified readings are written.
- `trace`: memory address of the readings, with 4 values, each a 32-bit floating-point number.
- `gains`: memory address of the per-channel gains, with 4 signed 32-bit integers.

```c
trace  = {1.5, -2.0, 0.25, 96.0}
gains  = {  2,    1,    3,   -5}
result = {6.0, -4.0,  2.0,  3.0}
```

This function has no return value.
All readings are normal, non-zero floating-point numbers, and every amplified result is also normal.
