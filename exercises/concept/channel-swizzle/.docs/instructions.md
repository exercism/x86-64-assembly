# Instructions

You write the inner loops of a software image pipeline, the stage that prepares textures and composites layers before they reach the screen.
The pipeline works on pixels a block at a time, applying the same operation across the whole block.

A pixel is composed of four 1-byte channels: red, green, blue, and alpha, in that order (`RGBA`).
A block is 4 pixels, so 16 bytes in total.

You have five tasks.

You receive the operands through memory addresses, and you write your answer through a result address.
All memory addresses in this exercise are 16-byte aligned.

~~~~exercism/note
The computations in this exercise should be performed using SIMD instructions, not scalar operations.
~~~~

## 1. Convert an image to display order

Textures are stored as `RGBA`, but the framebuffer this pipeline draws into expects each pixel in `BGRA` order: the red and blue channels swapped, the green and alpha channels left in place.
An image arrives as a sequence of blocks, and every block is converted the same way.

Implement the `to_display_order` function, which converts a whole image from `RGBA` to `BGRA`, one block at a time.
You should define the channel-reordering control mask as a packed constant in memory, and reuse it for every block.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the converted blocks are written, 16 bytes per block.
- `pixels`: memory address of the source blocks, 4 pixels per block, each pixel 4 bytes in `RGBA` order.
- `block_count`: the number of blocks, always greater than `0`.

```c
pixels      = {200, 64, 32, 255, 10, 20, 30, 40, 0, 0, 0, 255, 12, 34, 56, 78,
               1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16} // 2 blocks
block_count = 2
result      = {32, 64, 200, 255, 30, 20, 10, 40, 0, 0, 0, 255, 56, 34, 12, 78,
               3, 2, 1, 4, 7, 6, 5, 8, 11, 10, 9, 12, 15, 14, 13, 16}
```

This function has no return value.

## 2. Fill a region with one color

To clear a region or paint a flat span, the pipeline writes a single color across every pixel of the region.

Implement the `fill_region` function, which fills a region of `block_count` blocks with copies of one color.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the filled blocks are written, 16 bytes per block.
- `color`: memory address of one pixel, 4 bytes in `RGBA` order.
- `block_count`: the number of blocks to fill, always greater than `0`.

```c
color       = {18, 52, 86, 120}
block_count = 2
result      = {18, 52, 86, 120, 18, 52, 86, 120, 18, 52, 86, 120, 18, 52, 86, 120,
               18, 52, 86, 120, 18, 52, 86, 120, 18, 52, 86, 120, 18, 52, 86, 120}
```

This function has no return value.

## 3. Weave two scanlines

Two single-channel layers need to be merged into one buffer with their samples interleaved.
The result alternates one sample from the first layer, then one from the second.

Implement the `weave_scanlines` function, which interleaves two rows of 16 samples each into a single row of 32 samples.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the 32 interleaved samples are written.
- `first`: memory address of the first row, 16 samples, each an 8-bit value.
- `second`: memory address of the second row, 16 samples, each an 8-bit value.

```c
first  = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
second = {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115}
result = {0, 100, 1, 101, 2, 102, 3, 103, 4, 104, 5, 105, 6, 106, 7, 107,
          8, 108, 9, 109, 10, 110, 11, 111, 12, 112, 13, 113, 14, 114, 15, 115}
```

This function has no return value.

## 4. Pack a brightened row

A brightness pass scales each sample in 16-bit working precision, so that an over-bright sample can exceed `255` and a difference can drop below `0`.
The final stage narrows those working values back to 8-bit samples for display, clamping anything below `0` up to `0` and anything above `255` down to `255`.

Implement the `pack_samples` function, which narrows two groups of 8 working values into one row of 16 samples, in order.

This function takes as arguments, in this order:

- `result`: memory address for a buffer where the 16 clamped samples are written, each an 8-bit value.
- `first`: memory address of the first 8 working values, each a 16-bit signed integer.
- `second`: memory address of the next 8 working values, each a 16-bit signed integer.

```c
first  = {300, -5, 128, 255, 0, 400, 64, 200}
second = {255, 256, -1, 100, 50, 1000, 7, 0}
result = {255, 0, 128, 255, 0, 255, 64, 200,   255, 255, 0, 100, 50, 255, 7, 0}
```

This function has no return value.

## 5. Split coordinates into x and y

Texture and vertex data often arrives interleaved, each point's `x` and `y` packed together.
However, it is often necessary to have them apart for efficient processing: all the `x` values in one vector, all the `y` values in another.

Implement the `split_coordinates` function, which separates four interleaved `(x, y)` points into a vector of `x` coordinates and a vector of `y` coordinates.

This function takes as arguments, in this order:

- `xs`: memory address for a buffer where the 4 `x` coordinates are written, 4 32-bit floating-point numbers.
- `ys`: memory address for a buffer where the 4 `y` coordinates are written, 4 32-bit floating-point numbers.
- `first`: memory address of the first two points, 4 32-bit floating-point numbers, as `{x0, y0, x1, y1}`.
- `second`: memory address of the next two points, 4 32-bit floating-point numbers, as `{x2, y2, x3, y3}`.

```c
first  = {0.0, 0.5, 1.0, 1.5} // {x0, y0, x1, y1}
second = {2.0, 2.5, 3.0, 3.5} // {x2, y2, x3, y3}
xs     = {0.0, 1.0, 2.0, 3.0} // {x0, x1, x2, x3}
ys     = {0.5, 1.5, 2.5, 3.5} // {y0, y1, y2, y3}
```

This function has no return value.
