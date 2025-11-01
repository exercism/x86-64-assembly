# Introduction

In previous concepts, it was mentioned that the `global` directive makes a function or variable defined in one source file visible to other files.
Similarly, the `extern` directive informs the assembler that a function or variable used in the current source file is defined in another one.

Those two directives are the main way assembly code interacts with other source files to achieve modularization.

For the purposes of these directives, it is indifferent if the external code is defined or used in assembly or in a high-level language.
So, for example, even a function defined in a high-level language may be used in x86-64 code if declared `extern`.

In the same way, the calling convention is shared across all of those functions, defined in assembly or in high-level languages, and even with the Operating System (OS).

However, since in assembly data is just a sequence of bytes, it is important to be aware of how the interfacing high-level language manages memory.

## C Types

The C language is a common choice for a high-level language to interface with assembly code.
It makes the task of interacting with the OS easier, offering high-level wrappers for many important tasks, such as printing to the screen, reading from a keyboard or allocating dynamic memory.

In this track, the tests are written in C and so it is important to offer a general overview of the language.

~~~~exercism/note
Any of the types indicated below may be qualified with `const`.
This makes them read-only.
~~~~

### Primitive Types

There are many primitive types in C and their size, in bytes, may vary.
Some of them are summarized in the following table, with their typical size in a x86-64 system:

| type      | number of bytes | integer/floating-point |
|-----------|-----------------|------------------------|
| _Bool     | 1               | integer                |
| char      | 1               | integer                |
| short     | 2               | integer                |
| int       | 4               | integer                |
| long      | 4 or 8          | integer                |
| long long | 8               | integer                |
| float     | 4               | floating-point         |
| double    | 8               | floating-point         |

Each one of those integral types can be signed (the default) or unsigned.
In case they are unsigned, this must be specified, for example: `unsigned int`.

There are aliases for the integral types that are defined to provide precise control over their size:

| alias   | number of bytes |
|---------|-----------------|
| int8_t  | 1               |
| int16_t | 2               |
| int32_t | 4               |
| int64_t | 8               |

Those aliases may be prefixed by `u` to indicate an unsigned type, for example: `uint64_t`.

Other aliases of note are:

| alias  | type                                          |
|--------|-----------------------------------------------|
| bool   | _Bool                                         |
| size_t | usually an unsigned 8-byte integer            |

A `_Bool`, or its alias `bool`, is unique in that, although it occupies 1 entire byte, it can only assume one of two values: `true` (`1`) and `false` (`0`).

Values of those primitive types are passed to, and returned from, functions according to the usual rules for integers and floating-point values.

### Enums

An **enum** is a type that can assume one of a number of explicitly indicated elements:

```c
enum example {
    example_1,
    example_2,
    example_3,
    example_4
};
```

In C, enums are implicitly converted to an integer type, which is typically an `int`, i.e., a 4-byte integer.

By default the first possible element in an enum is converted to `0` and all subsequent elements are converted to the next integer.
So, in the `enum example` defined above, `example_1` would have value `0`, `example_2` would have value `1` and so on.

It is possible to indicate the value for any element of an enum and then, by default, the next element would have the next integer as value:

```c
enum example_2 {
    example_1 = 4,
    example_2 = 8,
    example_3
}; // example_3 is equal to 9
```

### Memory addresses

In C, a memory address is referenced by a **pointer** to a type and denoted with the `*` operator.
So, for example, `int64_t *` refers to a memory location for one or more `int64_t`.

Addresses are treated as 8-byte integers, as usual.

### Arrays

Arrays are passed to, and returned from, functions as pointers to their first element.

```c
int64_t example_arr[] = {1, 2, 3}; // this is an array of 3 signed 8-byte integers
fn(example_arr); // this is a function that passes a pointer (int64_t *) to the beginning of the array as an argument
```

Each element in an array has the size of the array's element type.
The `example_arr` defined above, for example, has 3 elements of 8 bytes each, which is 24 bytes in total.

Because arrays do not store their length, a separate value is usually necessary to indicate the number of elements unless a sentinel value marks the end.

### Strings

Strings in C are an array of `char`, which is a 1-byte type.
Most strings are of ASCII characters and NUL-terminated, so they end when a byte with the value `0` is found.
This means the length of a string does not usually need to be passed as a separate argument.
