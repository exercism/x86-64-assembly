# Design

## Learning objectives

- Know what is a macro and how it differs from a function.
- Know how to define single-line macros.
- Know how to define multi-line macros.
- Know how to define labels inside a macro.
- Know how to repeat a block of code at assemble-time, using `times` and `%rep...%endrep`.
- Know how to use `%assign` to create counters for assemble-time loops.
- Know how to use `%rotate` to handle variadic arguments in a macro.
- Know how to use `%if...%elif...%else...%endif` for conditional assembly.
- Know how to `%include` a macro file.
- Know how to create a data layout with `struc`, and how to access declared fields.

## Out of scope

- Other conditional assembly directives besides the simple `%if`.
- Other define-like preprocessor directives, such as `%defalias`, `%defstr`, etc.

## Concepts

- `macros`

## Prerequisites

- `strings`
