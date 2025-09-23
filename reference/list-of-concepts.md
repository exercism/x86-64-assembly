# List of Topics for Concepts

This is a preliminary list of topics to be implemented in the x86-64-assembly track.

Most of the topics should map onto a Concept and have its own Concept Exercise.

## Introductory Topics

### Basics

- comments
- constants (EQU)
- what is a register
- what is an instruction
- general layout of an instruction (INSTRUCTION DEST, SRC)
- some sample instructions (MOV, ADD, SUB)
- general structure of a function
- calling and returning (CALL and RET)

- PREREQUISITES : NONE

### Memory

- section .data/.rodata/.bss
- RIP-relative addressing (REL)
- BYTE/WORD/DWORD/QWORD
- what is a pointer (labels)
- accessing memory (indirection, LEA)
- what is an array
- array offsets

- PREREQUISITES: BASICS

### Integers

- binary representation
- signedness, sign extension (MOVZX, MOVSX, CDQ, CQO) and negation (NEG)
- arithmetic (INC, ADD, ADC, DEC, SUB, MUL/IMUL, DIV/IDIV)

- PREREQUISITES: BASICS

### Conditionals/Loops

- most common flags in rFLAGs (CF, PF, ZF, SF, DF, OF)
- comparison instructions (CMP and TEST)
- jump instructions (JMP and Jcc)
- difference between signed and unsigned jumps
- branchless instructions (CMOVcc and SETcc)
- additional loop-control instructions (LOOP, LOOPE, LOOPNE)

- PREREQUISITES: BASICS

### Bitwise Instructions

- accessing individual bits (BT, BTR, BTS)
- bitwise instructions (NOT, OR, XOR, AND, SHR/SAR, SHL)
- other bit manipulation instructions (POPCNT, LZCNT, BSR, BFR)

- PREREQUISITES: INTEGERS

### Stack

- RSP and RBP
- prologue and epilogue (PUSH and POP)
- stack frame
- stack alignment

- PREREQUISITES: MEMORY

### Strings

- ASCII characters
- strings are arrays ending in NULL
- main string instructions (LODSx, STOSx, MOVSx, CMPSx, SCANSx, REP, REPE, REPNE)
- direction flag (CLD, STD)

- PREREQUISITES: MEMORY

### Functions

- section .text
- extern and global
- calling conventions (registers)
- tail call
- recursion

- PREREQUISITES : CONDITIONALS/LOOPS AND STACK

### Floating-Point Numbers

- binary representation (IEEE-754)
- XMM registers (MOVSx)
- calling conventions
- storing floating-point in memory
- converting between integers and floating-points (CVTxx2xx and ROUND)
- common arithmetic instructions (ADDSx, SUBSx, MULSx, DIVSx)
- comparison instructions (COMISx and UCOMISx)
- other common instructions (SQRTSx)

- PREREQUISITES: INTEGERS, CONDITIONALS/LOOPS, MEMORY

## Advanced Topics

### Macros and Assembler Directives

- what is a macro and how is it different from functions
- single-line macros (%define)
- multi-line macros
- %assign
- times and %rep

- PREREQUISITES: BASICS

### Introduction to SIMD

- what are SIMD operations
- XMM as SIMD registers
- integer SIMD move (MOVDQA, PMOV)
- packed shifts (PSLLD, PSRLD)
- packed integer arithmetic instructions (PADD, PSUB, PMUL)
- packed integer horizontal reductions (PHADD, PHSUB)
- packed bitwise instructions (PAND, PANDN, POR, PXOR, PSR, PSL)

- PREREQUISITES: BITWISE INSTRUCTIONS, FLOATING-POINT NUMBERS

### Floating-Point SIMD Instructions

- packed floating-point arithmetic instructions (ADDPx, SUBPx, MULPx, DIVPx)
- packed floating-point horizontal reductions (HADDPx, HSUBPx)
- packed comparison instructions (PCMP, PTEST)
- other packed instructions (PABS, PMAX, PMIN)

- PREREQUISITES: INTRODUCTION TO SIMD

## Other topics (To be discovered)

- ATOMICS?
- SYSCALLS?
- HEAP?
