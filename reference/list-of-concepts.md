# List of Topics for Concepts

This is a preliminary list of topics to be implemented in the x86-64-assembly track.

Most of the topics should map onto a Concept and have its own Concept Exercise.

## Introductory Topics

GENERAL-PURPOSE REGISTERS:
- what is a register
- accessing 8-bit, 16-bit, 32-bit and 64-bit portion of a register
- callee-saved and caller-saved registers

FUNCTIONS:
- section .text
- extern and global
- calling and returning (CALL and RET)
- calling conventions (registers)

INTEGERS:
- binary representation
- signedness, sign extension (MOVZX, MOVSX, CDQ, CQO) and negation (NEG)
- common arithmetic instructions (ADD, SUB, MUL/IMUL, DIV/IDIV)
- bitwise instructions (NOT, OR, XOR, AND, SHR/SAR, SHL)

CONDITIONALS/LOOPS:
- most common flags in rFLAGs (CF, PF, ZF, SF, DF, OF)
- comparison instructions (CMP and TEST)
- labels and jump instructions (JMP and Jcc)
- difference between signed and unsigned jumps
- branchless instructions (CMOVcc and SETcc)
- additional loop-control instructions (LOOP, LOOPE, LOOPNE)

MEMORY:
- section .data/.rodata/.bss
- RIP-relative addressing (REL)
- BYTE/WORD/DWORD/QWORD
- what is a pointer (labels)
- accessing memory (indirection, LEA)
- array offsets

STRINGS:
- ASCII characters
- strings are arrays ending in NULL
- main string instructions (LODSx, STOSx, MOVSx, CMPSx, SCANSx, REP, REPE, REPNE)
- direction flag (CLD, STD)

FLOATING-POINT NUMBERS:
- binary representation (IEEE-754)
- XMM registers (MOVSx)
- calling conventions
- storing floating-point in memory
- converting between integers and floating-points (CVTxx2xx and ROUND)
- common arithmetic instructions (ADDSx, SUBSx, MULSx, DIVSx)
- comparison instructions (COMISx and UCOMISx)
- other common instructions (SQRTSx, )

STACK:
- RSP and RBP
- prologue and epilogue (PUSH and POP)
- what CALL and RET really do
- stack alignment

## Advanced Topics

MACROS AND ASSEMBLER DIRECTIVES
- what is a macro and how is it different from functions
- single-line macros (%define)
- multi-line macros
- %assign
- times and %rep

SIMD INSTRUCTIONS
- what are SIMD operations
- XMM as SIMD registers
- integer SIMD move (MOVDQA, PMOV)
- packed integer arithmetic instructions (PADD, PSUB, PMUL)
- packed integer horizontal reductions (PHADD, PHSUB)
- packed floating-point arithmetic instructions (ADDPx, SUBPx, MULPx, DIVPx)
- packed floating-point horizontal reductions (HADDPx, HSUBPx)
- packed bitwise instructions (PAND, PANDN, POR, PXOR, PSR, PSL)
- packed comparison instructions (PCMP, PTEST)
- packed shifts (PSLLD, PSRLD)
- other packed instructions (PABS, PMAX, PMIN)

## Other topics (To be discussed)

SYSCALLS?
HEAP?
