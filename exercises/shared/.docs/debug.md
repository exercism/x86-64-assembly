# Debug

To help with debugging, there are various macros defined in a [debug.mac file][debug].
They can be called with one or more arguments of the appropriate type and size.
For example:

```x86asm
debugf32 xmm0, xmm1 ; prints the value of two 32-bit floating-point numbers
debugd16 ax, cx, dx ; prints the value of three signed 16-bit integers
debugx64 [rax]      ; prints the value of a 64-bit integer in hexadecimal format
debugs rel mem, rsi ; prints two NUL-terminated strings
debugu8_xmm xmm1    ; prints 16 packed 8-bit unsigned integers
debug_flag e        ; prints true if je would jump, and false otherwise
```

To use any of those macros, `debug.mac` must be included at the top of the solution file:

```x86asm
%include "debug.mac"
```

Note that `rsp` is temporarily modified by all macros.
To debug a value on the stack, load its address into another register before debugging.

[debug]: https://github.com/exercism/x86-64-assembly/tree/main/templates/debug.mac
