# Hints

## General

- All memory addresses in this exercise are 16-byte aligned, so the aligned moves (`movdqa` for integers, `movaps` for floats) are appropriate.
  An aligned address can also be used directly as a memory source operand.

## 1. Convert an image to display order

- Within each 4-byte pixel, the conversion swaps the byte at offset `0` (red) with the byte at offset `2` (blue), and leaves offsets `1` (green) and `3` (alpha) in place.
  The same pattern repeats across all four pixels.
- A [shuffle][pshufb] may be used to reorder bytes in-place according to the indices in a control vector.
- The control vector may be defined in memory.
- There may be more than one block, and each block is 16 bytes.

## 2. Fill a region with one color

- The color is a single 4-byte pixel.
  To store it 16 bytes at a time, it should first be [broadcast][pshufd] across all four lanes of a `xmm` register.
- A 4-byte pixel must first be [moved][pinsrd] to a `xmm` register before being broadcast.
- Every filled block is identical, so the filled register may be created once and then reused.
- There may be more than one block, and each block is 16 bytes.

## 3. Weave two scanlines

- [unpack][unpack] instructions may be used to interleave bytes of two operands.
- Both unpack instructions take the first byte of each pair from the destination operand, and the second from the source operand.

## 4. Pack a brightened row

- [pack][pack] instructions may be used to narrow lanes, while clamping them.
- Pack instructions take the low lanes from the destination operand, and the high lanes from the source operand.

## 5. Split coordinates into x and y

- [floating-point shuffles][shufps] may be used to select and reorder lanes from two operands.
- The `x` coordinates sit in the even lanes (`0` and `2`) of each input, and the `y` coordinates in the odd lanes (`1` and `3`).

[pshufb]: https://www.felixcloutier.com/x86/pshufb
[pshufd]: https://www.felixcloutier.com/x86/pshufd
[pinsrd]: https://www.felixcloutier.com/x86/pinsrb:pinsrd:pinsrq
[unpack]: https://www.felixcloutier.com/x86/punpcklbw:punpcklwd:punpckldq:punpcklqdq
[pack]: https://www.felixcloutier.com/x86/packuswb
[shufps]: https://www.felixcloutier.com/x86/shufps
