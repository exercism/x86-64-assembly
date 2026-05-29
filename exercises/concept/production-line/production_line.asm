section .text

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                           TASK 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
global sum_yields
sum_yields:
    ; TODO: Define the function `sum_yields`
    ;
    ; This function takes as arguments, in order:
    ; 1. `line_a`: 16-byte aligned memory address holding 4 32-bit floating-point numbers
    ; 2. `line_b`: 16-byte aligned memory address holding 4 32-bit floating-point numbers
    ; 3. `result`: 16-byte aligned memory address where the function will write 4 32-bit floating-point numbers
    ;
    ; It calculates the lane-wise sum of the numbers in `line_a` and `line_b` and stores this sum in `result`
    ;
    ; The function has no return value
    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                           TASK 2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
global scaled_deviation
scaled_deviation:
    ; TODO: Define the function `scaled_deviation`
    ;
    ; This function takes as arguments, in order:
    ; 1. `measured`: 16-byte aligned memory address holding 2 64-bit floating-point numbers
    ; 2. `target`: memory address holding 2 64-bit floating-point numbers (alignment not guaranteed)
    ; 3. `sensitivity`: memory address holding 2 64-bit floating-point numbers (alignment not guaranteed)
    ; 4. `result`: memory address for a buffer where the function will write 2 64-bit floating-point numbers (alignment not guaranteed)
    ;
    ; It calculates the lane-wise scaled deviation of the numbers in `measured` and stores this deviation in `result`
    ; The scaled deviation is defined as (measured - target) * sensitivity
    ;
    ; The function has no return value
    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                           TASK 3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section .rodata
    ; TODO: Define a conversion factor for `calibrate_batch`

section .text

global calibrate_batch
calibrate_batch:
    ; TODO: Define the function `calibrate_batch`
    ;
    ; This function takes as arguments, in order:
    ; 1. `raw`: memory address holding 4 32-bit floating-point numbers (alignment not guaranteed)
    ; 2. `reference`: 16-byte aligned memory address holding 2 64-bit floating-point numbers
    ; 3. `offset`: 16-byte aligned memory address holding 2 64-bit floating-point numbers
    ; 4. `result`: 16-byte aligned memory address where the function will write 4 64-bit floating-point numbers (32 bytes total)
    ;
    ; The function should, for each of the two rows of the batch:
    ; 1. Convert the 2 single-precision raw values of the row to double precision.
    ; 2. Subtract `offset` from the converted pair.
    ; 3. Divide `reference` by the result.
    ; 4. Lane-wise multiply each 64-bit floating-point number by the fixed conversion factor of `0.5`.
    ; 5. Store the 2 64-bit floating-point numbers to the corresponding 16 bytes of `result`.
    ;
    ; Note that the reference and the offset are the same for both rows of the batch.
    ; The conversion factor is the same on every calibration, so you should declare it as a packed 16-byte constant in memory.
    ;
    ; The function has no return value
    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                           TASK 4
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
global normalize_scores
normalize_scores:
    ; TODO: Define the `normalize_scores` function
    ;
    ; This function takes as arguments, in order:
    ; 1. `scores`: 16-byte aligned memory address holding `n` 64-bit floating-point numbers (modified in place)
    ; 2. `gains`: 16-byte aligned memory address holding `n` 64-bit floating-point numbers
    ; 3. `scale`: 16-byte aligned memory address holding 2 64-bit floating-point numbers
    ; 4. `n`: a 64-bit positive even integer (minimum `2`), the number of scores to normalize
    ;
    ; The two scale lanes apply to the two elements of each pair:
    ; 1. the first lane scales the first element of each pair (lanes at even positions)
    ; 2. the second lane scales the second element of each pair (lanes at odd positions)
    ;
    ; For each score, the function computes `score * gain / scale_lane` and stores it back in-place
    ;
    ; The function has no return value
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
