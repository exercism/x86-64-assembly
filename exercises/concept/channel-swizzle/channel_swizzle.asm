section .text

global to_display_order
to_display_order:
    ; TODO: implement the `to_display_order` function
    ;
    ; This function converts a whole image from RGBA to BGRA, one block at a time.
    ; In every pixel the red and blue channels are swapped, and green and alpha are left in place.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the converted blocks are written, 16 bytes per block
    ; 2. `pixels`: 16-byte aligned memory address of the source blocks, 4 pixels per block, each pixel 4 bytes in RGBA order
    ; 3. `block_count`: the number of blocks, always greater than `0`, as a 64-bit unsigned integer
    ;
    ; Each channel is 1-byte wide and a pixel has 4 channels.
    ; A block has 4 pixels.
    ;
    ; The channel-reordering control mask may be defined as a packed constant.
    ;
    ; This function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global fill_region
fill_region:
    ; TODO: implement the `fill_region` function
    ;
    ; This function fills a region of `block_count` blocks with copies of one color.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the filled blocks are written, 16 bytes per block
    ; 2. `color`: 16-byte aligned memory address of one pixel, 4 bytes in RGBA order
    ; 3. `block_count`: the number of blocks to fill, always greater than `0`, as a 64-bit unsigned integer
    ;
    ; Each channel is 1-byte wide and a pixel has 4 channels.
    ; A block has 4 pixels.
    ;
    ; This function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global weave_scanlines
weave_scanlines:
    ; TODO: implement the `weave_scanlines` function
    ;
    ; This function interleaves two rows of 16 samples each into a single row of 32 samples.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 32 interleaved samples are written
    ; 2. `first`: 16-byte aligned memory address of the first row, with 16 samples, each an 8-bit value
    ; 3. `second`: 16-byte aligned memory address of the second row, with 16 samples, each an 8-bit value
    ;
    ; Even-indexed samples are taken from `first`, while odd-indexed samples are taken from `second`.
    ;
    ; This function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global pack_samples
pack_samples:
    ; TODO: implement the `pack_samples` function
    ;
    ; This function narrows two groups of 8 working values into one row of 16 samples, in order.
    ; The values should be clamped to the range `0` to `255`.
    ;
    ; This function takes as arguments, in order:
    ; 1. `result`: 16-byte aligned memory address where the 16 clamped samples are written, each an 8-bit value
    ; 2. `first`: 16-byte aligned memory address of the first 8 working values, each a 16-bit signed integer
    ; 3. `second`: 16-byte aligned memory address of the next 8 working values, each a 16-bit signed integer
    ;
    ; This function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

global split_coordinates
split_coordinates:
    ; TODO: implement the `split_coordinates` function
    ;
    ; This function separates four interleaved (x, y) points into two vectors.
    ; The first vector holds only `x` coordinates, and the second holds only `y` coordinates.
    ;
    ; This function takes as arguments, in order:
    ; 1. `xs`: 16-byte aligned memory address where the 4 x coordinates are written, 4 32-bit floating-point numbers
    ; 2. `ys`: 16-byte aligned memory address where the 4 y coordinates are written, 4 32-bit floating-point numbers
    ; 3. `first`: 16-byte aligned memory address of the first two points, 4 32-bit floating-point numbers as `{x0, y0, x1, y1}`
    ; 4. `second`: 16-byte aligned memory address of the next two points, 4 32-bit floating-point numbers as `{x2, y2, x3, y3}`
    ;
    ; The coordinates should be stored in the same order they are given:
    ; xs = {x0, x1, x2, x3}
    ; ys = {y0, y1, y2, y3}
    ;
    ; This function has no return value.
    ; The computation should use SIMD instructions, not scalar operations.
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
