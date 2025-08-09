# Exercism x86-64 Assembly Track

[![Configlet Status](https://github.com/exercism/x86-64-assembly/workflows/configlet/badge.svg)](https://github.com/exercism/x86-64-assembly/actions/workflows/configlet.yml)
[![Exercise Test Status](https://github.com/exercism/x86-64-assembly/workflows/x86-64-assembly%20%2F%20main/badge.svg)](https://github.com/exercism/x86-64-assembly/actions/workflows/ci.yml)

Exercism exercises in x86-64 Assembly.

## NASM

NASM (The Netwide Assembler) is the assembler used by this track. It's a
popular assembler with a syntax that is simple and easy to understand.

## Unity

Unity is a simple unit testing framework for C used by this track. Using a
framework written in C instead of assembly language is easier to understand. It
also shows how parameters are passed when calling assembly routines from C.

## Calling conventions

There are two calling conventions in common use for x86-64. The Microsoft x64
calling convention, and the System V AMD64 ABI. Support is only provided for
the latter. This will spare mentors the trouble of having to switch between the
two.

## Generating test cases

To create a test generator, add a .py file to the generators/exercises folder
with the name of the exercise. See [leap.py](https://github.com/exercism/x86-64-assembly/blob/master/generators/exercises/leap.py) for an example.

Generate the test cases with the following command:

```bash
./generators/generate <exercise name>
```

## pre-commit

You may choose to install [pre-commit](https://pre-commit.com/) hooks using

```
pip install pre-commit
pre-commit install
```

## Contributing Guide

Please see the [contributing guide](https://github.com/exercism/docs/blob/master/contributing-to-language-tracks/README.md).
