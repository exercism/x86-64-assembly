# Debug

To help with debugging, there are various macros defined in a [debug.mac file][debug].
They can be called with a register or memory operand of the approppriate size.
For example:

```x86asm
debugf32 xmm0    ; prints the value of a 32-bit floating-point
debugd16 ax      ; prints the value of a signed 16-bit integer
debugx64 [rax]   ; prints the value of a 64-bit integer in hexadecimal format
debugs rsi       ; prints a NUL-terminated string whose address is stored in `rsi`
debugu8_xmm xmm1 ; prints 16 packed 8-bit unsigned integers
```

In order to use any of those macros, `debug.mac` must be included at the top of the solution file:

```x86asm
%include "debug.mac"
```

[debug]: https://github.com/exercism/x86-64-assembly/tree/main/templates/debug.mac
