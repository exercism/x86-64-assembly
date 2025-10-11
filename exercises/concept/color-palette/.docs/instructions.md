# Instructions

Your friend José is a teacher in a local school.
He had the idea for some fun experiments to show how colors can be combined to produce different ones.

He asked for your help with those experiments.

## 1. Get the RGB value for a color

Each color is represented as a 32-bit number already stored in a table, defined in another source file.
A color is identified by an unique address in that table.

Define a function `get_color_value` that returns this 32-bit representation for a color.
This function takes as parameter a valid address for this color in the color table.

```c
get_color_value(black)
// => 0
```

**Hint** - 32 bits are equivalent to 4 bytes.

## 2. Save colors

In order to mix colors, José first needs to know which are the current colors being used.

Define a function `save_colors` that has no return value and takes as parameters the address of two colors in the color table.
It then saves the 32-bit values for each color in the variables `first_color` and `second_color`, in order of arguments passed (so the first color address corresponds to the 32-bit value stored in `first_color`).

The variables `first_color` and `second_color` are defined by you and must be accessible from other source files.

There will be no more than 1 of each color at the same time.
If `save_colors` is called again, the old colors are discarded.

By default, at the start of the program, `first_color` and `second_color` should be initialized with the 32-bit value for _white_ (`0xFFFFFF00`) and _black_ (`0`) respectively.

## 3. Define constants for primary colors

José expects to make many combinations using primary colors, so he wants to have them separated for fast access.
Since he is using `RGBa` to represent colors, the primary colors are:

- `RED`, with the value `0xFF000000`.
- `GREEN`, with the value `0x00FF0000`.
- `BLUE`, with the value `0x0000FF00`.

Define one constant for each of those colors.
Those constants must be accessible from other source files.

**Hint** - NASM accepts numbers defined in hexadecimal, using `0x`.

## 4. Combine colors

José wants to show different combinations of colors at the same time, so the students can compare them visually.

The colors should be combined according to a `combining_function` defined in another source file.
This function takes as parameters the 32-bit values for the base and secondary colors.
It returns the 32-bit value for the combined color.

Define a function `make_color_combination` that combines two colors and saves the result.
This function has no return value and takes as parameters, in this order:

- The address where the 32-bit value for the combined color should be stored.
- The address of a secondary color in the color table, to be combined with the primary color.

~~~~exercism/caution
Notice that `combining_function` may modify the values in registers you are using.
Make sure to save any variable you need in memory before calling the function.
~~~~
