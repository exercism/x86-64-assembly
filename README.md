# Exercism x86-64 Assembly Track

[![Configlet Status][configlet-badge]][configlet]
[![Exercise Test Status][main-badge]][ci]

Exercism exercises in x86-64 Assembly.

## NASM

[NASM][nasm] (The Netwide Assembler) is the assembler used by this track.
It's a popular assembler with a syntax that is simple and easy to understand.

## Unity

[Unity][unity] is a simple unit testing framework for C used by this track.
Using a framework written in C instead of assembly language is easier to understand.
It also shows how parameters are passed when calling assembly routines from C.

## Calling conventions

There are two calling conventions in common use for x86-64.
The Microsoft x64 calling convention, and the [System V AMD64 ABI][SystemV].
Support is only provided for the latter.
This will spare mentors the trouble of having to switch between the two.

## Generating test cases

To create a test generator, add a .py file to the generators/exercises folder with the name of the exercise.
See [leap.py][leap-example] for an example.

Generate the test cases with the following command:

```bash
./generators/generate <exercise name>
```

## pre-commit

You may choose to install [pre-commit][precommit] hooks using

```
pip install pre-commit
pre-commit install
```

## Contributing Guide

Please see the [contributing guide][contributing].

[configlet]: https://github.com/exercism/x86-64-assembly/actions/workflows/configlet.yml
[ci]: https://github.com/exercism/x86-64-assembly/actions/workflows/ci.yml
[nasm]: https://www.nasm.us/
[unity]: https://github.com/ThrowTheSwitch/Unity
[SystemV]: https://www.uclibc.org/docs/psABI-x86_64.pdf
[leap-example]: https://github.com/exercism/x86-64-assembly/blob/master/generators/exercises/leap.py
[precommit]: https://pre-commit.com/
[contributing]: ./CONTRIBUTING.md
[main-badge]: https://github.com/exercism/x86-64-assembly/workflows/x86-64-assembly%20%2F%20main/badge.svg
[configlet-badge]: https://github.com/exercism/x86-64-assembly/workflows/Configlet/badge.svg
