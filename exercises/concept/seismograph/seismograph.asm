section .text

global rectify_trace
rectify_trace:
    ; TODO: implement the `rectify_trace` function
    ;
    ; This function computes the absolute value of each reading, by clearing its sign bit.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 4 rectified readings are written
    ; 2. `trace`: 16-byte aligned memory address of the readings, with 4 32-bit floating-point numbers
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global reading_scale
reading_scale:
    ; TODO: implement the `reading_scale` function
    ;
    ; This function extracts the unbiased exponent of each reading as a signed 32-bit integer.
    ; The exponent field sits at bits 30-23 and is biased by 127.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 4 scales are written, as signed 32-bit integers
    ; 2. `trace`: 16-byte aligned memory address of the readings, with 4 32-bit floating-point numbers
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global coarsen_displacements
coarsen_displacements:
    ; TODO: implement the `coarsen_displacements` function
    ;
    ; This function divides each signed count by 2^shift, rounding toward negative infinity.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 4 coarsened counts are written
    ; 2. `counts`: 16-byte aligned memory address of the counts, with 4 signed 32-bit integers
    ; 3. `shift`: the power of two to divide by, as a 64-bit unsigned integer between 0 and 31
    ;
    ; The instruction `movq` may be used to copy a 64-bit integer from a general-purpose register to an `xmm` register.
    ; It does not change the underlying bit representation.
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global gate_channels
gate_channels:
    ; TODO: implement the `gate_channels` function
    ;
    ; This function ORs the two enable masks together, then clears the channels marked faulty.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 4 gated masks are written
    ; 2. `enable_a`: 16-byte aligned memory address of the first enable masks, with 4 unsigned 32-bit integers
    ; 3. `enable_b`: 16-byte aligned memory address of the second enable masks, with 4 unsigned 32-bit integers
    ; 4. `faulty`: 16-byte aligned memory address of the faulty-channel masks, with 4 unsigned 32-bit integers
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global toggle_calibration
toggle_calibration:
    ; TODO: implement the `toggle_calibration` function
    ;
    ; This function flips, in each status word, exactly the bits set in the matching
    ; toggle mask and not set in the matching lock mask, leaving every other bit untouched.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 4 updated status words are written
    ; 2. `status`: 16-byte aligned memory address of the status words, with 4 unsigned 32-bit integers
    ; 3. `toggle`: 16-byte aligned memory address of the toggle masks, with 4 unsigned 32-bit integers
    ; 4. `locked`: 16-byte aligned memory address of the lock masks, with 4 unsigned 32-bit integers
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global amplify_trace
amplify_trace:
    ; TODO: implement the `amplify_trace` function
    ;
    ; This function multiplies each reading by 2 raised to its channel's gain.
    ; This is done by manipulating the exponent field of the reading, without any actual multiplication.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 4 amplified readings are written
    ; 2. `trace`: 16-byte aligned memory address of the readings, with 4 32-bit floating-point numbers
    ; 3. `gains`: 16-byte aligned memory address of the per-channel gains, with 4 signed 32-bit integers
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
