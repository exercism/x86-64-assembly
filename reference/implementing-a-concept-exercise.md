# How to implement an x86-64 Assembly concept exercise

This document describes the steps required to implement a concept exercise in the x86-64-assembly track.

**Please please please read the docs before starting.** Posting PRs without reading these docs will be a lot more frustrating for you during the review cycle, and exhaust Exercism's maintainers' time. So, before diving into the implementation, please read the following documents:

- [The features of v3][features-of-v3].
- [Rationale for v3][rationale-for-v3].
- [What are concept exercise and how they are structured?][concept-exercises]

Please also watch the following video:

- [The Anatomy of a Concept Exercise][anatomy-of-a-concept-exercise].

As this document is generic, the following placeholders are used:

- `<SLUG>`: the slug of the exercise in [lowercase and kebab-case][determining-concepts-naming] (e.g. `calculator-conundrum`).
- `<NAME>`: the name of the exercise (e.g. `Calculator Conundrum`).
- `<CONCEPT_SLUG>`: the slug of one of the exercise's concepts in kebab-case (e.g. `anonymous-methods`).

Before implementing the exercise, please make sure you have a good understanding of what the exercise should be teaching (and what not). This information can be found in the exercise's GitHub issue.

To implement a concept exercise, the following files must be added:

<pre>
languages
└── x86-64-assembly
    ├── concepts
    |   └── &lt;CONCEPT_SLUG&gt;
    |       ├── about.md
    |       └── links.json
    └── exercises
        └── concept
            └── &lt;SLUG&gt;
                ├── .docs
                |   ├── instructions.md
                |   ├── introduction.md
                |   ├── hints.md
                |   └── source.md (required if there are third-party sources)
                ├── .meta
                |   |── config.json
                |   |── design.md
                |   └── exemplar.asm
                ├── vendor
                |   |── unity_internals.h
                |   |── unity.c
                |   └── unity.h
                ├── &lt;NAME&gt;_test.c
                ├── &lt;NAME&gt;.asm
                └── Makefile
</pre>

Note that the concept files should be created for each concept the exercise teaches.

All Markdown files should adhere to the [style guide][style-guide], noting the [automatic formatting section][style-guide-auto-formatting].

## Step 1: Add code files

The code files are track-specific and should be designed to help the student learn the exercise's concepts.

The configlet should be [fetched][fetcher] and used to add the following x86-64-assembly code files:

### Add `<NAME>.asm` file

**Purpose:** Provide a stub implementation.

- The stub implementation's code should compile. The only exception is for exercises that introduce syntax we _want_ a student to define themselves. In this case, insert a descriptive TODO comment instead of providing stub code.

For more information, please read [this in-depth description][stub-file] and [watch this video][video-stub-file].

### Add `<NAME>_test.c` file

**Purpose:** The test suite to verify a solution's correctness.

- [Unity][unity] is used as the test framework.
- All but the first test should be skipped by default.
- Test methods must be named using `snake_case`.
- Test methods must have a single assertion.

For more information, please read [this in-depth description][tests-file] and [watch this video][video-tests-file].

### Add `.meta/exemplar.asm` file

**Purpose:** The idiomatic example implementation that passes all the tests.

For more information, please read [this in-depth description][example-file] and [watch this video][video-example-file].

### Add `./vendor/..` and `Makefile` files

**Purpose:** Helper files to assemble and compile solutions and the test file.

They can be fetched from [the templates folder][templates-folder].

## Step 2: Add documentation files

How to create the files common to all tracks is described in the [how to implement a concept exercise document][how-to-implement-a-concept-exercise].

## Step 3: Update list of implemented exercises

- Add the exercise to the [list of implemented exercises][implemented-exercises].

## Inspiration

When implementing an exercise, it can be very useful to look at already implemented x86-64 exercises. You can also check the exercise's [general concepts documents][reference] to see if other languages have already implemented an exercise for that concept.

## Help

If you have any questions regarding implementing this exercise, please post them as comments in the exercise's GitHub issue.

[unity]: https://github.com/ThrowTheSwitch/Unity
[concept-exercises]: https://github.com/exercism/v3/blob/main/docs/concept-exercises.md
[rationale-for-v3]: https://github.com/exercism/v3/blob/main/docs/rationale-for-v3.md
[features-of-v3]: https://github.com/exercism/v3/blob/main/docs/features-of-v3.md
[anatomy-of-a-concept-exercise]: https://www.youtube.com/watch?v=gkbBqd7hPrA
[reference]: https://github.com/exercism/v3/tree/main/reference/concepts/README.md
[style-guide]: https://github.com/exercism/v3/blob/main/docs/maintainers/style-guide.md
[style-guide-auto-formatting]: https://github.com/exercism/v3/blob/main/docs/maintainers/style-guide.md#auto-formatting
[how-to-implement-a-concept-exercise]: https://github.com/exercism/v3/blob/main/docs/maintainers/generic-how-to-implement-a-concept-exercise.md
[determining-concepts-naming]: https://github.com/exercism/v3/blob/main/docs/maintainers/determining-concepts.md#naming-concepts
[stub-file]: https://github.com/exercism/v3/blob/main/docs/concept-exercises.md#stub-implementation-file
[tests-file]: https://github.com/exercism/v3/blob/main/docs/concept-exercises.md#tests-file
[example-file]: https://github.com/exercism/v3/blob/main/docs/concept-exercises.md#example-implementation-file
[video-stub-file]: https://www.youtube.com/watch?v=gkbBqd7hPrA&t=1171
[video-tests-file]: https://www.youtube.com/watch?v=gkbBqd7hPrA&t=1255
[video-example-file]: https://www.youtube.com/watch?v=gkbBqd7hPrA&t=781
[implemented-exercises]: ../reference/implemented-exercises.md
[fetcher]: ../bin/fetch-configlet
[templates-folder]: ../templates/
