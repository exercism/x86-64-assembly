# Instructions

You are writing the digital core of a small mixing console at a recording studio.

Sound arrives as a stream of samples.
Each sample is a number describing the position of a loudspeaker cone at one instant.
A console processes a whole block of samples at once, applying the same operation to each.

You have five tasks, each operating on a block of samples held in memory.
You receive the operands through memory addresses and write your answer through a result address.

~~~~exercism/note
The computations in this exercise should be performed using SIMD instructions, not scalar operations.
~~~~

## 1. Mix two tracks

The studio sometimes records instruments on different tracks.
To play them through the same speakers, you sum the two tracks into one.

Implement the `mix_tracks` function, which adds two tracks together, sample by sample.
Each track is a block of 8 signed 16-bit samples.
A sum that overflows the signed 16-bit range must clamp instead of wrapping.

This function takes as arguments, in this order:

- `result`: 16-byte aligned memory address for a buffer where the 8 mixed samples are written.
- `track_a`: 16-byte aligned memory address of the first track, with 8 signed 16-bit samples.
- `track_b`: 16-byte aligned memory address of the second track, with 8 signed 16-bit samples.

```c
track_a = {10000, 30000, 20000, -30000, -20000, -100,  100, 0}
track_b = { 5000,  5000, 20000,  -5000, -20000,  100, -100, 0}
result  = {15000, 32767, 32767, -32768, -32768,    0,    0, 0}
```

This function has no return value.

## 2. Remove bleed

When two microphones record at once, each one picks up a faint copy of the other's source.
This unwanted copy is called _bleed_.
Once this bleed is measured, it must be subtracted back out to clean up the track.

Implement the `remove_bleed` function, which subtracts the bleed block from the track block, sample by sample.
Each block is 8 signed 16-bit samples, and the subtraction must saturate.

This function takes as arguments, in this order:

- `result`: memory address where the 8 cleaned samples are written (alignment not guaranteed).
- `track`: 16-byte aligned memory address of the recorded track, 8 signed 16-bit samples.
- `bleed`: memory address of the bleed to remove, 8 signed 16-bit samples (alignment not guaranteed).

```c
track  = {10000, -30000, 5000, 32767, 0,  200, -200, 15000}
bleed  = { 2000,   5000, 5000,    -5, 0,  300,  300,  5000}
result = { 8000, -32768,    0, 32767, 0, -100, -500, 10000}
```

This function has no return value.

## 3. Combine meters

Above each channel sits a level meter, a little bar whose brightness shows how loud that channel is.
The front panel has one master meter that should glow as brightly as the two channels combined.
You add the two meter blocks to drive it.

Note that a bright meter stays at full brightness rather than wrapping back to dark, so the sum is saturating.

Implement the `combine_meters` function, which adds two meter blocks sample by sample.
This function takes as arguments, in this order:

- `result`: 16-byte aligned memory address where the 16 combined values are written.
- `meter_a`: 16-byte aligned memory address of the first channel's meter block, with 16 packed unsigned 8-bit values.
- `meter_b`: 16-byte aligned memory address of the second channel's meter block, with 16 packed unsigned 8-bit values.

Each block is 16 unsigned 8-bit values.
They should be added together, saturating to the unsigned range.

```c
meter_a = {200, 100,  50, 255, 0, 128, 10, 240, 1, 2, 3, 4, 5, 6, 7, 8}
meter_b = {100, 100, 200,   1, 0, 128, 10,  20, 1, 2, 3, 4, 5, 6, 7, 8}
result  = {255, 200, 250, 255, 0, 255, 20, 255, 2, 4, 6, 8, 10, 12, 14, 16}
```

This function has no return value.

## 4. Apply a fade

The song should not stop abruptly, but fade out at the end.
You have a block of _gain coefficients_, one per sample, that taper from quieter to quieter still.

Each coefficient is a fraction expressed over `65536`.
For example, if a sample has a value of `16384`, it actually expresses `16384 / 65536`, which is `1 / 4`.
The largest usable value, `32767`, is just under one half.

Since `65536` is `2^16`, multiplying a sample by its coefficient and keeping the _high half_ of the product gives `sample * gain / 65536`.

Implement the `apply_fade` function, which scales each sample by its coefficient.
This function takes as arguments, in this order:

- `result`: 16-byte aligned memory address where all the scaled samples are written.
- `track`: 16-byte aligned memory address of the track, with `n` signed 16-bit samples.
- `gains`: 16-byte aligned memory address of the gain coefficients, with `n` signed 16-bit values, each in the range `0` to `32767`.
- `n`: the number of samples, which is always non-zero and a multiple of `8`, as a 64-bit unsigned integer.

Note that the track is an array that holds `n` signed 16-bit samples, where `n` is never zero and always a multiple of `8`.
For each sample, the scaled result is the _high_ 16 bits of the signed product: `sample * gain`.

```c
track  = {20000, 20000, 20000, 20000, -20000, -20000, -20000, -20000}
gains  = {32767, 24576, 16384,  8192,  32767,  24576,  16384,   8192}
result = { 9999,  7500,  5000,  2500, -10000,  -7500,  -5000,  -2500}
```

~~~~exercism/note
Keeping the high half rounds toward negative infinity.
This is why `20000 * 32767` scales to `9999`, while `-20000 * 32767` scales to `-10000` rather than `-9999`.
~~~~

This function has no return value.

## 5. Attenuate a track

The drummer was recorded far too loud.
To bring the whole track down, you divide every sample by a constant.

Implement the `attenuate_track` function.
This function takes as arguments, in this order:

- `result`: 16-byte aligned memory address where the results are written, as 32-bit signed integers.
- `samples`: 16-byte aligned memory address of the samples, `n` signed 16-bit values.
- `divisor`: 16-byte aligned memory address of 4 identical copies of the divisor, as 32-bit integers.
- `n` is the number of samples, which is always non-zero and a multiple of `4`, as a 64-bit unsigned integer.

Note that `samples` is an array that holds `n` signed 16-bit samples, where `n` is never zero and always a multiple of `4`.

The divisor is supplied as `4` copies of the same 32-bit integer, already replicated so it can fill all four lanes at once.

Integer SIMD has no packed division, so the work is done in packed floating-point, and then converted back to packed 32-bit integers to be stored in `result`.
Convert back by truncating toward zero, so a quotient of `2.3` becomes `2` and `-2.3` becomes `-2`.

```c
samples = {300, 150, 90, -120, 100, 50, -50, 7}
divisor = {3, 3, 3, 3}
result  = {100,  50, 30,  -40,  33, 16, -16, 2}
```

This function has no return value.
