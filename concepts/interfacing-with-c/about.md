# About

In previous concepts, it was mentioned that the `global` directive makes a function or variable defined in one source file visible to other files.
Similarly, the `extern` directive informs the assembler that a function or variable used in the current source file is defined in another one.

Those two directives are the main way assembly code interacts with other source files to achieve modularization.

For the purposes of these directives, it is indifferent if the external code is defined in assembly, or if the global code is used by assembly.
So, for example, even a function defined in a high-level language may be used in x86-64 code if declared `extern`.

In the same way, the calling convention is shared across all of those functions, defined in assembly or in high-level languages, and even with the Operating System (OS).

However, since in assembly data is just a sequence of bytes, it is important to be aware of how the interfacing high-level language manages memory.

## C Types

The C language is a common choice for a high-level language to interface with assembly code.
It makes the task of interacting with the OS easier, offering high-level wrappers for many important tasks, such as printing to the screen, reading from a keyboard or allocating dynamic memory.

In this track, the tests are written in C and so it is important to offer a general overview of the language.

Any of the types indicated below may be qualified with `const`, which make them read-only.

### Primitive Types

There are many primitive types in C and the size those types occupy may vary.
Some of them are summarized in the following table, with typical size in a x86-64 system:

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
| size_t | usually an unsigned 8 byte integer            |

Values of those types are passed to, and returned from, functions according to the usual rules for integers and floating-point values.

### Enums

An [enum][enum] is a type that can assume one of a number of explicitly indicated elements:

```c
enum example {
    example_1,
    example_2,
    example_3,
    example_4
};
```

In C, enums are implicitly converted to an integer type, which is typically an `int`.

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

In x86-64 assembly, an enum is passed to, and returned from, functions as `int`, ie, as 4-byte integers.

### Memory addresses

In C, a memory address is referenced by a [pointer][pointer] to a type and denoted with the `*` operator.
So, for example, `int64_t *` refers to a memory location for one or more `int64_t`.

Addresses are treated as 8-byte integers, as usual.

### Arrays

Arrays are passed to, and returned from, functions as pointers to its first element.

```c
int64_t example_arr[] = {1, 2, 3}; // this is an array of 3 signed 8-byte integers
fn(example_arr); // this is a function that passes a pointer to the beginning of the array as argument
```

It is important to note that each element in an array has the size of the type pointed by the array.
So `example_arr` defined above, for example, has 3 elements of 8 bytes each, which is 24 bytes in total.

Since the array typically has no indication of its length, a separate argument usually is also passed to indicate the number of elements in the array.

### Strings

Strings in C are an array of `char`, which is a 1-byte type.
Most strings are of ASCII characters and NUL-terminated, so they end when a byte with the value `0` is found.
This means the length of a string does not usually need to be passed as a separate argument.

### Structs

A [struct][struct] is a composite type, formed of different fields.
Each field has its own type and size.

For instance, this defines a type formed of two 4-byte integers, in this order:

```c
struct example {
    int32_t first_four_byte_integer;
    uint32_t second_four_byte_integer;
    uint64_t eight_byte integer;
};
```

A struct may also contain other structs:

```c
struct example_2 {
    struct example first;
    struct example second;
};
```

#### Calling convention

The calling convention for structs has many different rules.
But, as a rule of thumb, all fields in a struct occupy adjacent space in memory and should be passed in a single register whenever possible.

So, an instance of the struct example, defined above, would be passed in two registers:

1. The first register would hold `first_four_byte_integer` in the lower 4 bytes and `second_four_byte_integer` in the upper 4 bytes.
2. The second register would hold `eight_byte_integer`.

If a struct occupies more than 16 bytes in space, it is usually passed on the stack.
It will also be passed on the stack if any field in the struct is too big to fit into a register.
That would be the case for `struct example_2`, defined above.

A struct is returned in the same manner, ie, if possible in a single register.
If more than 16 bytes are necessary, the function gets a memory address as an implicit first argument (in `rdi`).
The struct should be placed on this memory location and `rax` should have the address of that memory location.

#### Alignment

Another important consideration in accessing values in a struct is its [alignment][alignment].

The alignment is a value that represents the number of bytes between the addresses of two elements of a type.
It is always a non-negative power of two: 1, 2, 4, 8, etc.

For a primitive type, the alignment is its size, so, for instance, a `int32_t` has 4-byte alignment.

The alignment of a struct, however, is the largest alignment of its fields.
So, for example, the `struct example`, defined above, would have an alignment of 8 bytes, since this is the alignment of `uint64_t`.

If a field in a struct occupies less bytes than the struct's alignment, the remaining bytes are padded.
This means they are not used in the value of the struct and are in practice "wasted":

```c
struct example_3 {
    char one_byte;
    int four_byte;
};
// example_3 has alignment of 4 (the same as int)
// it occupies 8 bytes in space:
// 1 byte for the field 'one_byte'
// 3 bytes for padding (with undefined value)
// 4 bytes for the field 'four_byte'
```

It is important to account for any possible padding bytes whenever accessing a struct in assembly.

[enum]: https://en.cppreference.com/w/c/language/enum.html
[pointer]: https://en.cppreference.com/w/c/language/pointer.html
[struct]: https://en.wikipedia.org/wiki/Struct_(C_programming_language)
[alignment]: https://en.cppreference.com/w/c/language/object.html#Alignment
