# About

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

~~~~exercism/note
The stack's privacy is a convention rather than a protection: a thread's stack lives in the same shared memory, and a thread that hands out the address of one of its locals lets another thread reach it.
Registers, on the other hand, are exclusive in hardware: each core has its own set, and the operating system saves and restores them across a thread switch.
~~~~

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
The processor asserts a lock on the location for the duration, the same mechanism the `lock` prefix uses for other instructions, described next.

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

On any other instruction, such as a plain `mov`, the prefix is invalid and the processor raises an invalid-opcode fault.
A lone load or a lone store needs no prefix: a naturally aligned access is already atomic on its own.

~~~~exercism/caution
Holding a location exclusively and keeping every other core out is not free.
A `lock`-prefixed operation is markedly slower than its plain form, and slower still when several cores contend for the same location.

This prefix should be reserved for memory that is expected to be mutated by more than one thread.
Avoid using it if the memory is not shared or if it is only ever read.
~~~~

~~~~exercism/note
Keep a shared atomic value naturally aligned, so it sits within a single cache line.
A locked access that straddles two cache lines, called a **split lock**, is legal but dramatically slower, since the processor must lock more than one line, and some recent systems trap it outright.
~~~~

## Atomic Bit Operations

Among the lockable instructions, the bit tests pair naturally with the spinlock at the end of this document.
Each of `bts`, `btr`, and `btc` copies one chosen bit into the carry flag and then sets, clears, or flips it.
With the `lock` prefix that becomes a one-bit read-modify-write: the bit is changed atomically, and `CF` reports what it was before.

```x86asm
    lock bts qword [rdi], 0 ; set bit 0; CF = the bit's previous value
    setc al                 ; al = 1 when the bit was already set
```

A set that finds the bit already set means another thread claimed it first.
This is a single-bit version of the flag-claiming that `xchg` does for a whole word.

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

The source may be any general-purpose register, and the operand width runs from a byte to a quadword.
Adding a negative value turns the same instruction into a fetch-and-subtract.

## Compare and Exchange

`xadd` adds and `xchg` overwrites, but neither can make the new value depend on the current one and apply it only if nothing changed underneath.
That conditional update is what `cmpxchg`, compare-and-exchange, provides, and it is the most general of these primitives.

`cmpxchg dest, src` uses `rax` as an implicit accumulator, and compares it against `dest`:

- If `dest == rax`, `dest = src` and `ZF = 1`.
- If `dest != rax`, `rax = dest` and `ZF = 0`.

The accumulator follows the operand size: `al` for a byte, then `ax`, `eax`, and `rax` for the wider forms.

Note that `dest` is only updated when it is equal to the expected value, previously loaded into `rax`.
This equality ensures `dest` still holds the value the new one was computed from, so an update based on a stale read is never applied.
That makes `cmpxchg` the building block for an atomic update, also known as [**compare-and-swap (CAS)**][cas]:

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

One subtlety is worth knowing.
`cmpxchg` checks that the value equals what was read, not that the location was never touched.
If another thread moves the value from `A` to `B` and back to `A` inside the window, the exchange _still succeeds_, even though the world changed underneath it.

For a plain counter that is harmless, since an equal count is an equally good count.
For a memory address at the head of a lock-free list it is not, because the same address may now lead somewhere else.
This is the [ABA problem][aba].

The usual solution to this issue pairs the value with some "stamp", for example a counter that only ever grows.
Because the stamp only ever advances, a matching stamp proves the location was not touched in between, not merely that it looks unchanged.

For this to work in a multi-threaded environment, however, both the memory address and its stamp must be updated together.
Since a memory address is a full qword in x86-64, a `cmpxchg` is not enough to update it and also another value at the same time.

There is a double-width instruction called [cmpxchg16b][cmpxchg16b] that is semantically the same as `cmpxchg` but works on 16 bytes at once and can be used in that situation.
It does not have a source operand, instead using `rcx:rbx` as the replacement value.
Its only operand is a 16-byte aligned memory location.
This instruction also uses `rdx:rax` as the accumulator, instead of only `rax`.

## Memory Ordering

Every operation so far has touched a single location.
When threads coordinate through more than one location, a new question appears: in what order does one thread's writes become visible to another.
The rules that answer this question are the processor's **memory ordering**.

The [branchless-code][branchless-code] concept introduced the idea that a modern core does not plod through instructions one at a time.
It keeps many in flight at once and runs ahead where it can.
This means a write may become visible to the other cores later than the program suggests, while instructions after it have already gone ahead.

x86-64 keeps a **strong memory ordering** among ordinary loads and stores, so that on each core:

1. a load is never reordered after a later load;
2. a store is never reordered after a later store;
3. a load is never reordered after a later store.

The only possible reordering is a store appearing to complete after a later load of a _different_ address.

A `lock`-prefixed instruction, or an `xchg` with a memory operand, is a full barrier: nothing appears to move across it in either direction.
This is why they are enough to ensure full ordering in most situations.

The mechanism behind the one surviving reordering is the **store buffer**.
To keep running ahead, a core parks each store in that buffer and lets later instructions proceed before the store reaches the memory the other cores can see.
A write followed by a read of a different location can therefore appear out of order: the write may still sit in the buffer while the later read goes ahead.
This model, everything ordered except that write-then-read gap, is called **total store order**.

That single gap is enough to break a store-then-check handshake.
If two threads each write their own flag and then read the other's, both reads can come back unset, because neither store has left its store buffer yet.
The `mfence` instruction closes the gap by draining the store buffer: every write before it becomes visible before any read after it.

```x86asm
    mov dword [rdi], 1    ; publish: this thread is ready
    mfence                ; the store above must land before the load below
    mov eax, dword [rsi]  ; observe whether the other thread is ready
```

Two narrower barriers exist as well:
- `sfence` orders writes against each other and matters mainly with the streaming, non-temporal stores;
- `lfence` orders reads.

For the ordinary atomic patterns above, the `lock`-prefixed instructions already carry full ordering, so an explicit barrier is only needed for a handshake built from plain stores and loads like the one above.

These guarantees have names that reach beyond x86.
An operation has **acquire** ordering when no later access can appear to move before it, and **release** ordering when no earlier access can appear to move after it.
On x86 every load is an acquire, every store is a release, and a `lock`-prefixed instruction, or an `xchg` with memory, is both at once.

## Spinning and `pause`

Instructions that set a flag while also returning its previous state are known as [**test-and-set**][test-and-set].
They may be used as the basis of a [**spinlock**][spinlock], ensuring a core has exclusive access to some part of the code.

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

Note that in a test-and-set, an instruction such as `xchg` always sets the flag, even when it was already set.
This means it gets exclusive access to the memory every spin even when it is likely the lock is still being held.

There is a variant to this algorithm, known as [**test-and-test-and-set**][test-and-test-and-set], that first tests (reads) the flag to check if it is already set.
It then only attempts the test-and-set (the `xchg` in this case) once the lock looks free:

```x86asm
acquire:
    mov  eax, 1
    xchg dword [rdi], eax ; try to take the lock
    test eax, eax
    jz   .taken           ; got it
.held:
    pause                 ; wait before trying again
    cmp  dword [rdi], 0   ; watch the lock without writing to it
    jne  .held            ; still held
    jmp  acquire          ; looks free: retry
.taken:
    ret
```

Once the thread finishes its work, it may release the lock with a plain store of `0` using `mov`.
Nothing more than a `mov` is needed, because on x86-64 loads and stores are never reordered after a later store.
A store that never overtakes the accesses before it is said to have **release ordering**, and on x86 every plain store carries it.

~~~~exercism/note
Any instruction that atomically tests and sets a memory location may be used for a spinlock.
For example, `lock bts` may be used instead of `xchg`, to set a specific bit while checking if it was already set.

Note that flags, such as the `CF` modified by `bts`, are part of `rflags`, a register.
This means they are exclusive to each thread.
~~~~

~~~~exercism/note
A full reference for every instruction mentioned here is available in the [x86 instruction reference][instruction-reference].

[instruction-reference]: https://www.felixcloutier.com/x86/
~~~~

[cas]: https://en.wikipedia.org/wiki/Compare-and-swap
[cmpxchg16b]: https://www.felixcloutier.com/x86/cmpxchg8b:cmpxchg16b
[aba]: https://en.wikipedia.org/wiki/ABA_problem
[branchless-code]: https://exercism.org/tracks/x86-64-assembly/concepts/branchless-code
[test-and-set]: https://en.wikipedia.org/wiki/Test-and-set
[spinlock]: https://en.wikipedia.org/wiki/Spinlock
[test-and-test-and-set]: https://en.wikipedia.org/wiki/Test_and_test-and-set
