%ifndef MAGAZINE_LAYOUT_ASM
%define MAGAZINE_LAYOUT_ASM

; Write your macros in this file.
; A helper file includes the current file and calls these macros in predefined functions.
; Keep the names and argument order as given.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; --- Task 1: name the format constants ---
; Give each value a readable name according to the instructions:
; - `COLUMN_COUNT` is `4`
; - `COLUMN_STRIDE` is `18`
; - `SPACE` is `0x20`, the blank byte
; - `RULE` is `0x3D`, the byte `=`
; - `RULE_WIDTH` is `4`
; - `PLAIN` is `0x2E`, the byte `.`
; - `RULED` is `0x2D`, the byte `-`
; - `BOXED` is `0x23`, the byte `#`
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; --- Task 2: define the COUNTER and the fill_run macros ---
; The COUNTER name should expand to the rcx register
;
; The fill_run macro fills N slots of an output array with copies of a given byte.
;
; It takes 3 arguments:
; 1. the destination address, passed in a 64-bit general-purpose register.
; 2. the count of bytes (N) to write, passed in a 64-bit general-purpose register or as an immediate.
; 3. the byte to write (always non-negative), passed in an immediate.
;
; The `fill_run` macro may clobber `COUNTER` freely, but no other register.
; It is called three times in two different functions.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; --- Task 3: define the lay_columns macro ---
; This macro writes COLUMN_COUNT offsets, each a 64-bit integer, to an output array.
;
; It takes two arguments in this order:
; 1. the destination address, passed in a 64-bit general-purpose register
; 2. the left margin, passed in a 64-bit general-purpose register
;
; The number of offsets to be written to the destination address is fixed and equal to `COLUMN_COUNT`.
; Each offset is a 64-bit value calculated with:
; `offset[i] = margin + i * COLUMN_STRIDE`,
; where `i` is the index of the offset starting at `0`, and `margin` is the second argument.
;
; This macro may clobber its two register arguments, but no other.
; It is called once.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; --- Task 4: define the set_header macro ---
; This macro adds a header byte to an output memory address, according to a literal style id.
;
; It takes two arguments in this order:
; 1. the destination address.
; 2. a literal style id passed as an immediate, where `0` is plain, `1` is ruled, and `2` is boxed.
;
; The destination address is the expression of an effective memory address.
; It takes a base register that may be summed with:
; - an index register scaled by `1`, `2`, `4` or `8`
; - an immediate
;
; The possible ids and their corresponding header byte are:
;
; | id  | header byte |
; |-----|-------------|
; | 0   | PLAIN       |
; | 1   | RULED       |
; | 2   | BOXED       |
;
; Select the header byte with conditional assembly (`%if` / `%elif` / `%else`).
;
; This macro should not clobber any register.
; It is called three times in the same function.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

%endif

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
