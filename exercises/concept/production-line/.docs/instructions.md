# Instructions

You are writing code for the data system on an automotive parts factory floor.
Engine and chassis components move through a series of machining stations.
Each station produces measurements that have to be combined, compared, calibrated, or normalized before the next stage runs.
The functions you implement here are one for each station.

~~~~exercism/note
The computations in this exercise should be performed using SIMD instructions, not scalar operations.
~~~~

## 1. Combine yields from two lines

The factory floor runs two parallel assembly lines.
At the end of each shift, both lines report their yields for 4 part bins as single-precision numbers.
The supervisor's dashboard shows the combined yield per bin, so the two reports are summed bin by bin.
All three buffers are managed by the reporting system and are always 16-byte aligned.

Define a function `sum_yields` that, given the per-bin yields from `line_a` and `line_b`, writes the bin-wise sum to `result`.
The arguments, in order, are:

1. `line_a`: 16-byte aligned memory address holding 4 32-bit floating-point numbers
2. `line_b`: 16-byte aligned memory address holding 4 32-bit floating-point numbers
3. `result`: 16-byte aligned memory address where the function will write 4 32-bit floating-point numbers

This function has no return value, instead the result is stored in the passed buffer (`result`):

```c
line_a = {10.0, 20.0, 30.0, 40.0};
line_b = { 5.0, 15.0, 25.0, 35.0};
sum_yields(line_a, line_b, result);
// => result == {15.0, 35.0, 55.0, 75.0};
```

## 2. Compute scaled deviation

Between operations, a sampling station measures machined parts and compares them against target dimensions.
The measured values stream in from a precision gauge into a buffer that is always 16-byte aligned.
The target values come from the work order packet, which has no alignment guarantee.
The deviation is multiplied by a per-axis sensitivity factor before it is passed to the downstream tolerance checker.
For this stage, the downstream checker reads the deviation directly from a SIMD register rather than from memory.

Define a function `scaled_deviation` that, given `measured` and `target` and a `sensitivity`, writes the scaled deviation to `result`.
The arguments, in order, are:

1. `measured`: 16-byte aligned memory address holding 2 64-bit floating-point numbers
2. `target`: memory address holding 2 64-bit floating-point numbers (alignment not guaranteed)
3. `sensitivity`: memory address holding 2 64-bit floating-point numbers (alignment not guaranteed)
4. `result`: memory address for a buffer where the function will write 2 64-bit floating-point numbers (alignment not guaranteed)

The scaled deviation is `(measured - target) * sensitivity`, lane-wise.

This function has no return value, instead the result is stored in the passed buffer (`result`) as a pair of 64-bit floating-point numbers.

```c
measured    = {10.5, 20.5};
target      = {10.0, 20.0};
sensitivity = { 2.0,  4.0};
scaled_deviation(measured, target, sensitivity, result);
// => result == {1.0, 2.0};
```

## 3. Calibrate a batch

Before parts enter the final inspection bay, the dimensional readings from a 4-part batch are rescaled into double precision and corrected for known temperature drift.

The 4 raw readings arrive as single-precision numbers.
For each row of 2 readings, the calibration computes `reference / (raw - offset)`, and then multiplies this result by a constant conversion factor of `0.5`.

Note that the reference and the offset are the same for both rows of the batch.
The conversion factor is the same on every calibration, so rather than receiving as an argument, you should declare it as a packed 16-byte constant in memory.

Define a function `calibrate_batch` that, given a `raw` batch, a `reference`, an `offset`, and a `result` buffer, writes the calibrated values to `result`.
The arguments, in order, are:

1. `raw`: memory address holding 4 32-bit floating-point numbers (alignment not guaranteed)
2. `reference`: 16-byte aligned memory address holding 2 64-bit floating-point numbers
3. `offset`: 16-byte aligned memory address holding 2 64-bit floating-point numbers
4. `result`: 16-byte aligned memory address where the function will write 4 64-bit floating-point numbers (32 bytes total)

The function should, for each of the two rows of the batch:

1. Convert the 2 single-precision raw values of the row to double precision.
2. Subtract `offset` from the converted pair.
3. Divide `reference` by the result.
4. Lane-wise multiply each 64-bit floating-point number by the fixed conversion factor of `0.5`.
5. Store the 2 64-bit floating-point numbers to the corresponding 16 bytes of `result`.

This function has no return value, instead the result is stored in the passed buffer (`result`):

```c
raw       = {10.0, 20.0, 25.0, 50.0};
reference = {100.0, 100.0};
offset    = {  5.0,  10.0};
calibrate_batch(raw, reference, offset, result);
// => result == {10.0, 5.0, 2.5, 1.25};
```

## 4. Normalize scores along a line

At the end of the line, every part has a quality score that needs to be normalized before it gets reported.
Each score is multiplied by its own per-part gain, then divided by a per-axis production scale.
The gains buffer holds one gain per part.

The production scale is the same for the whole run and is passed in a memory address holding two 64-bit floating-point numbers.
The scores are updated **in place**: the same buffer that held the raw scores now holds the normalized scores.

Define a function `normalize_scores` that, given a `scores` array, a `gains` array, a `scale`, and a count `n`, normalizes the scores in place.
The arguments, in order, are:

1. `scores`: 16-byte aligned memory address holding `n` 64-bit floating-point numbers (modified in place)
2. `gains`: 16-byte aligned memory address holding `n` 64-bit floating-point numbers
3. `scale`: 16-byte aligned memory address holding 2 64-bit floating-point numbers
4. `n`: a 64-bit positive even integer (minimum `2`), the number of scores to normalize

The two scale lanes apply to the two elements of each pair.
The first lane scales the first element of every pair (lanes at even positions), the second lane scales the second (lanes at odd positions).
Each score is multiplied by its corresponding gain, then divided by the appropriate scale lane: `score * gain / scale_lane`.

This function has no return value, instead the result is stored in the input buffer (`scores`), at the same position of the corresponding `score` that was normalized:

```c
n      = 4
scores = {10.0, 20.0, 30.0, 40.0};
gains  = { 2.0,  1.5,  1.0,  0.5};
scale  = { 2.0,  4.0};
normalize_scores(scores, gains, scale, n);
// => scores == {10.0, 7.5, 15.0, 5.0};
```
