# Introduction

A single instruction can look like one indivisible action while being nothing of the sort.
Take adding five to a value in memory:

```x86asm
add qword [rel counter], 5
```

Underneath, the processor does not have a way to add to memory directly.
It breaks this one instruction into three smaller steps, called **micro-operations**:

1. **read** the current value from memory;
2. **modify** this value in a register, adding five to it;
3. **write** the result back.

```x86asm
mov rax, qword [rel counter] ; 1. load the current value
add rax, 5                   ; 2. add five
mov qword [rel counter], rax ; 3. store the result back
```

This is a common pattern called **read-modify-write (RMW)**.

Note that the read (or load) and the write (or store) are separate events, so there is a window of time between them.
We usually do not notice this because on a single core each instruction is guaranteed to produce its effect in full before the next one.
That window is therefore invisible and `add` behaves as a single unit.

However, modern CPUs are rarely single-core, and applications often run on many cores at once, with no sequencing between them.
With several cores running at the very same instant, another core can read or write `counter` inside the window, after this core's load and before its store.
Two threads each load the same old value, each add five, and each store their result.
Two additions happened, but the value only moved by five.
One update was silently lost.

This is a **data race**, and it is a common issue in multi-threaded code.

Not every value is exposed this way.
Each thread has its own registers and its own stack, so a value held in a register, or a local variable on a thread's stack, is exclusive to that thread and cannot race.
Only the memory the threads share, like `counter` above, needs protecting.

x86-64 offers a set of instructions to solve this problem, by making an instruction indivisible.
It behaves as a single unit not only for the core that processes it, but for every other core as well.
An operation that holds together, that no other core can split, is called **atomic**.

~~~~exercism/note
It is common to refer to applications that run on many cores as multi-threaded.
However, a **thread** is not the same as a core.
Two threads may run concurrently on the same core, interleaving with each other, or in parallel on different cores.

Interleaving threads can already race across a read-modify-write if it is split into multiple instructions, since the OS can switch threads between any two instructions.
The window inside a _single_ instruction, however, is only exposed by true parallel code.
Because the OS only switches threads between instructions, never inside one, a single instruction is inherently safe on a single core.

True atomicity across _multiple_ cores is what the instructions below provide.
~~~~

## Atomic Exchange

The `xchg` instruction swaps two operands.
The destination operand becomes equal to the previous value in the source operand, while the source operand becomes equal to the previous value in the destination operand.
Conceptually, it can be thought of as two `mov` instructions happening at once.

As usual, it can be used with two register operands or with one memory operand and one register operand:

```x86asm
mov  eax, 1
xchg dword [rdi], eax ; [rdi] = 1, eax = the old value of [rdi]
mov ecx, 2
mov edx, 3
xchg edx, ecx         ; edx = 2, ecx = 3
```

When used with a memory operand, `xchg` is _always_ atomic.

~~~~exercism/caution
`xchg` is automatically atomic when one of the operands is a memory location.
This also means the operation is much slower in that situation.

If you do not need atomicity, do the swap through a spare register with plain `mov` instructions instead.
~~~~

## The Lock Prefix

The most common way an instruction can be made atomic in x86-64 is by adding the `lock` prefix.
It fuses the read, the modify, and the write into one indivisible step.
This means the core holds the memory exclusively throughout the whole process, so no other core can read or write that location in between.

```x86asm
lock add qword [rel counter], 5 ; the read, the modify, and the write are one step
```

`lock` only works when the destination is memory, and only on instructions that read-modify-write that memory:

1. arithmetic operations, such as `add`, `sub`, `inc`, `dec`, `neg`;
2. bitwise operations, such as `and`, `or`, `xor`, `not`;
3. the bit operations `bts`, `btr`, `btc`;
4. some other dedicated instructions, such as `xadd` and `cmpxchg`, described below.

~~~~exercism/caution
Holding a location exclusively and keeping every other core out is not free.
A `lock`-prefixed operation is markedly slower than its plain form, and slower still when several cores contend for the same location.

This prefix should be reserved for memory that is expected to be mutated by more than one thread.
Avoid using it if the memory is not shared or if it is only ever read.
~~~~

## Exchange and Add

A plain `lock add` updates memory but throws the old value away.
Often the old value is exactly what is wanted, for example to hand each thread a distinct ticket number.

The `xadd` instruction (`x` for exchange) returns the previous value while it adds.
It writes the sum into the destination and leaves the original destination value in the source register.

```x86asm
mov  rax, 1
lock xadd qword [rdi], rax ; [rdi] = [rdi] + rax = [rdi] + 1
                           ; rax = the old value of [rdi]
```

With the `lock` prefix this is an atomic **fetch-and-add**.
Run by many threads on the same counter, each call returns a different old value.

As with `lock add`, the counter ends at the exact number of calls.
However, unlike `lock add`, every intermediate value is returned too, one to each caller.

## Compare and Exchange

`xadd` adds and `xchg` overwrites, but neither can make the new value depend on the current one and apply it only if nothing changed underneath.
That conditional update is what `cmpxchg`, compare-and-exchange, provides, and it is the most general of these primitives.

`cmpxchg dest, src` uses `rax` as an implicit accumulator, and compares it against `dest`:

- If `dest == rax`, `dest = src` and `ZF = 1`.
- If `dest != rax`, `rax = dest` and `ZF = 0`.

Note that `dest` is only updated when it is equal to the expected value, previously loaded into `rax`.
This equality ensures `dest` still holds the value the new one was computed from, so an update based on a stale read is never applied.
That makes `cmpxchg` the building block for an atomic update, also known as **compare-and-swap (CAS)**:

```x86asm
    mov rax, qword [rdi]          ; rax = the value we expect to find
.retry:
    lea rcx, [rax + 10]           ; rcx = the new value we want to install
    lock cmpxchg qword [rdi], rcx ; if [rdi] still equals rax, store rcx and set ZF
                                  ; otherwise reload rax with the current value, clear ZF
    jnz  .retry                   ; ZF is cleared, so another thread won the race. Recompute and retry
```

This **retry loop** is the heart of lock-free updates.
The window between the read and the compare-and-exchange is exactly when another thread might intervene, and `cmpxchg` catches that by refusing to store a value computed from a stale read.

## Memory Ordering

Every operation so far has touched a single location.
When threads coordinate through more than one location, a new question appears: in what order does one thread's writes become visible to another.
The rules that answer this question are the processor's **memory ordering**.

The branchless-code concept introduced the idea that a modern core does not plod through instructions one at a time.
It keeps many in flight at once and runs ahead where it can.
This means a write may become visible to the other cores later than the program suggests, while instructions after it have already gone ahead.

x86-64 keeps a **strong memory ordering** among ordinary loads and stores, so that on each core:

1. a load is never reordered after a later load;
2. a store is never reordered after a later store;
3. a load is never reordered after a later store.

The only possible reordering is a store appearing to complete after a later load of a _different_ address.

A `lock`-prefixed instruction, or an `xchg` with a memory operand, is a full barrier: nothing appears to move across it in either direction.
This is why they are enough to ensure full ordering in most situations.

## Spinning and `pause`

Instructions that set a flag while also returning its previous state are known as **test-and-set**.
They may be used as the basis of a **spinlock**, ensuring a core has exclusive access to some part of the code.

This is the overall algorithm, using the `xchg` instruction with a binary flag:

1. The flag starts as `0`.
2. To acquire the lock, a core swaps the value in the flag with `1`.
3. If the returned value is `1`, this means the lock is _held_ by another core.
   The current core then waits and tries acquiring the lock again.
4. If the returned value is `0`, this means the lock was free.
   `xchg` has now set it to `1`, and other cores will wait until this core releases it.
5. Once the current core finishes working, updating the flag with `0` releases the lock.

```x86asm
acquire:
    mov  eax, 1
    xchg dword [rdi], eax ; try to take the lock; eax = its old value
    test eax, eax
    jnz  .held            ; old value was 1: someone else holds it
    ret                   ; old value was 0: the lock is ours
.held:
    pause                 ; wait before trying again
    jmp  acquire
```

The `pause` instruction in the wait loop does not change what the code computes.
It hints to the processor that this is a spin-wait.
The CPU can then reduce power use on the waiting thread and yield to a sibling thread sharing the same core.
A spin loop without `pause` is still correct, only wasteful.

Once the thread finishes its work, it may release the lock with a plain store of `0` using `mov`.
Nothing more than a `mov` is needed, because on x86-64 loads and stores are never reordered after a later store.
A store that never overtakes the accesses before it is said to have **release ordering**, and on x86 every plain store carries it.

~~~~exercism/note
Any instruction that atomically tests and sets a memory location may be used for a spinlock.
For example, `lock bts` may be used instead of `xchg`, to set a specific bit while checking if it was already set.

Note that flags, such as the `CF` modified by `bts`, are part of `rflags`, a register.
This means they are exclusive to each thread.
~~~~
