section .text

global flag_above_threshold
flag_above_threshold:
    ; TODO: implement the `flag_above_threshold` function
    ;
    ; This function builds a mask with an all-ones lane for every score strictly above its threshold, and an all-zeros lane otherwise.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 4 mask lanes are written
    ; 2. `scores`: 16-byte aligned memory address of the scores, with 4 32-bit normal floating-point numbers (never `NaN`)
    ; 3. `thresholds`: 16-byte aligned memory address of the thresholds, with 4 32-bit normal floating-point numbers (never `NaN`)
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global flag_perfect
flag_perfect:
    ; TODO: implement the `flag_perfect` function
    ;
    ; This function builds a mask with an all-ones lane for every score equal to its maximum, and an all-zeros lane otherwise.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 4 mask lanes are written
    ; 2. `scores`: 16-byte aligned memory address of the scores, with 4 32-bit normal floating-point numbers (never `NaN`)
    ; 3. `maxima`: 16-byte aligned memory address of the maxima, with 4 32-bit normal floating-point numbers (never `NaN`)
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global assign_ranks
assign_ranks:
    ; TODO: implement the `assign_ranks` function
    ;
    ; This function writes a rank for each score: 1 at or below the passing threshold of 50.0,
    ; 2 above the threshold, and 3 for a score equal to the maximum.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 4 ranks are written, as 32-bit unsigned integers
    ; 2. `scores`: 16-byte aligned memory address of the scores, with 4 32-bit normal floating-point numbers (never `NaN`)
    ; 3. `maxima`: 16-byte aligned memory address of the maxima, with 4 32-bit normal floating-point numbers (never `NaN`)
    ;
    ; The passing threshold and the rank values may be defined as packed constants.
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global count_failures
count_failures:
    ; TODO: implement the `count_failures` function
    ;
    ; This function counts how many ranks, across every block, are strictly below the passing threshold.
    ;
    ; This function takes as arguments, in order:
    ; 1. `ranks`: 16-byte aligned memory address of the ranks, a whole number of 4-lane blocks, each a 32-bit unsigned integer
    ; 2. `block_count`: the number of 4-lane blocks, always greater than `0`, as a 64-bit unsigned integer
    ; 3. `pass_threshold`: 16-byte aligned memory address of the passing threshold, with 4 identical signed 32-bit integers
    ;
    ; The function returns the count as a signed 32-bit integer.
    ; The per-lane comparison should use SIMD instructions.
    ret

global all_passed
all_passed:
    ; TODO: implement the `all_passed` function
    ;
    ; This function returns 1 when every lane of every failing mask is clear, and 0 when any lane in any block is set.
    ;
    ; This function takes as arguments, in order:
    ; 1. `failing`: 16-byte aligned memory address of the failing masks, a whole number of 4-lane blocks, each lane all ones or all zeros
    ; 2. `block_count`: the number of 4-lane blocks, always greater than `0`, as a 64-bit unsigned integer
    ;
    ; The function returns the answer as a signed 32-bit integer, either 1 or 0.
    ; The per-block test should use SIMD instructions.
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
