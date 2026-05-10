# Tests

To run the tests, execute the following command:

```bash
make
```

## Skipped tests

Solving an exercise means making all its tests pass.
By default, only one test (the first one) is executed when you run the tests.
This is intentional, as it allows you to focus on just making that one test pass.
Once it passes, you can enable the next test by removing the `TEST_IGNORE()` line.
When all tests have been enabled and your implementation makes them all pass, you'll have solved the exercise!

## Debugging

To help with debugging, there are various macros defined in a `debug.mac` file.
They can be called with one or more arguments of the appropriate size.
For example:

```x86asm
debugf32 xmm0, xmm1 ; prints the value of two 32-bit floating-point numbers
debugd16 ax, cx, dx ; prints the value of three signed 16-bit integers
debugx64 [rax]      ; prints the value of a 64-bit integer in hexadecimal format
debugs rsi          ; prints a NUL-terminated string whose address is stored in `rsi`
debugu8_xmm xmm1    ; prints 16 packed 8-bit unsigned integers
```

In order to use any of those macros, `debug.mac` must be included at the top of the solution file:

```x86asm
%include "debug.mac"
```
