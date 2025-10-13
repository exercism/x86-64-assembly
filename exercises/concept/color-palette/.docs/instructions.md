# Instructions

Your friend José is a teacher in a local school.
He had an idea for some fun experiments to show how colors can be combined to produce different ones.

He asked for your help with those experiments.

~~~~exercism/note
A color is represented in this exercise by a 32-bit (4-byte) number, encoding its `RGB` value.

A `RGB` value consists of 3 channels, _Red_, _Green_ and _Blue_, each one occupying 8 bits (1 byte).
The fourth byte is usually reserved for the _Alpha_ channel, but in this exercise its value will be empty (`0`).
~~~~

## 1. Get the RGB value for a color

The values for each color are already stored in a table, defined in another source file.
A color is identified by an unique address in this table.

Define a function `get_color_value` that returns the 32-bit value for a color.
This function takes as parameter a valid address for this color in the color table.

```c
get_color_value(black)
// => 0
```

**Hint** - 32 bits are equivalent to 4 bytes.

## 2. Add base color

In order to mix different colors, José will first fix a base one and change only the secondary color being combined with it.

Define a function `add_base_color` that saves the 32-bit value for a color in the variable `base_color`, so it can be used later.
This function has no return value and takes as parameter the address of the color in the color table.

The variable `base_color` is defined by you and must be accessible from other source files.

There will be no more than 1 base color at the same time.
If a new base color is added, the old one is discarded.

By default, at the start of the program, `base_color` should be initialized with the 32-bit value for _white_, which is `0xFFFFFF00`.

**Hint** - NASM accepts numbers defined in hexadecimal using `0x` at the start, such as in `0xFFFFFF00`.

## 3. Define constants for primary colors

José expects to make many combinations using primary colors, so he wants to have them separated for fast access.
Since he is using `RGB` to represent colors, the primary colors are:

- `RED`, with the value `0xFF000000`.
- `GREEN`, with the value `0x00FF0000`.
- `BLUE`, with the value `0x0000FF00`.

Define one constant for each of those colors.
Those constants must be accessible from other source files.

## 4. Combine colors

The colors should be combined according to a `combining_function` defined in another source file.
This function takes as parameters the 32-bit values for `base_color` and for a secondary color to be mixed with it.
It returns the 32-bit value for the combined color.

Define a function `make_color_combination` that combines two colors and saves the result in memory.
This function has no return value and takes as parameters, in this order:

- The address where the 32-bit value for the combined color should be stored.
- The address of a secondary color in the color table, to be combined with the primary color.

~~~~exercism/caution
Notice that `combining_function` may modify the values in registers you are using.
Make sure to save any variable you need in memory before calling the function.
~~~~
