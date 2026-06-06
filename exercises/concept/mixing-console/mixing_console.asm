section .text

global mix_tracks
mix_tracks:
    ; TODO: implement the `mix_tracks` function
    ;
    ; This function adds two tracks together, sample by sample, clamping on overflow.
    ; A sum outside the signed 16-bit range saturates instead of wrapping.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 8 mixed samples are written
    ; 2. `track_a`: 16-byte aligned memory address of the first track, with 8 signed 16-bit samples
    ; 3. `track_b`: 16-byte aligned memory address of the second track, with 8 signed 16-bit samples
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global remove_bleed
remove_bleed:
    ; TODO: implement the `remove_bleed` function
    ;
    ; This function subtracts the bleed block from the track block, sample by sample, clamping on overflow.
    ; A difference outside the signed 16-bit range saturates instead of wrapping.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: memory address where the 8 cleaned samples are written (alignment not guaranteed)
    ; 2. `track`: 16-byte aligned memory address of the recorded track, with 8 signed 16-bit samples
    ; 3. `bleed`: memory address of the bleed to remove, with 8 signed 16-bit samples (alignment not guaranteed)
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global combine_meters
combine_meters:
    ; TODO: implement the `combine_meters` function
    ;
    ; This function adds two meter blocks together, value by value, clamping on overflow.
    ; A sum outside the unsigned 8-bit range saturates instead of wrapping.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 16 combined values are written
    ; 2. `meter_a`: 16-byte aligned memory address of the first meter block, with 16 unsigned 8-bit values
    ; 3. `meter_b`: 16-byte aligned memory address of the second meter block, with 16 unsigned 8-bit values
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global apply_fade
apply_fade:
    ; TODO: implement the `apply_fade` function
    ;
    ; This function scales each sample by its gain coefficient.
    ; Each coefficient is a fraction over `65536`, so the scaled sample is the high 16 bits of the signed product `sample * gain`.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where all the scaled samples are written
    ; 2. `track`: 16-byte aligned memory address of the track, with `n` signed 16-bit samples
    ; 3. `gains`: 16-byte aligned memory address of the gain coefficients, with `n` signed 16-bit values, each in the range `0` to `32767`
    ; 4. `n`: the number of samples, always a multiple of `8`, as a 64-bit unsigned integer
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global attenuate_track
attenuate_track:
    ; TODO: implement the `attenuate_track` function
    ;
    ; This function divides each sample by a constant divisor.
    ; Integer SIMD has no packed division, so divide in packed floating-point and convert the quotient back to a 32-bit integer, truncating toward zero.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the results are written, as 32-bit signed integers
    ; 2. `samples`: 16-byte aligned memory address of the samples, with `n` signed 16-bit values
    ; 3. `divisor`: 16-byte aligned memory address of 4 identical copies of the divisor, as 32-bit integers
    ; 4. `n`: the number of samples, always a multiple of `4`, as a 64-bit unsigned integer
    ;
    ; The function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
