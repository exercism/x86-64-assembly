section .text
global remember_transaction
remember_transaction:
    ; TODO: Define the `remember_transaction` function
    ; This function takes a function address and stores it in memory
    ;
    ; It has no return value
    ret

global apply_remembered
apply_remembered:
    ; TODO: Define the `apply_remembered` function
    ; This function takes a 64-bit non-negative integer and applies the previously saved function to it
    ;
    ; It forwards whatever the saved function returns
    ret

global register_transaction
register_transaction:
    ; TODO: Define the `register_transaction` function
    ; It takes as arguments:
    ; 1. the address of a dispatch table
    ; 2. an index, as a 64-bit non-negative integer
    ; 3. a transaction, i.e., a function address
    ; It stores the transaction's address at the given index in the table.
    ;
    ; The function has no return value
    ret

global select_transaction
select_transaction:
    ; TODO: Define the `select_transaction` function
    ; It takes as arguments:
    ; 1. the address of a dispatch table
    ; 2. an index, as a 64-bit non-negative integer
    ; 3. a starting balance, as a 64-bit non-negative integer
    ; It looks up the transaction at the given index and applies it to the starting balance
    ;
    ; It returns the new balance, calculated by the transaction, as a 64-bit non-negative integer
    ret

global process_statement
process_statement:
    ; TODO: Define the `process_statement` function
    ; It takes as arguments:
    ; 1. a starting balance, as a 64-bit non-negative integer
    ; 2. the address of an array of transactions (which are function addresses)
    ; 3. the number of transactions in the array, as a 64-bit non-negative integer
    ;
    ; It composes all functions in the array
    ; That means that, for each transaction in sequence, it should:
    ; 1. apply the transaction to the running balance
    ; 2. then use the result as the balance for the next transaction
    ;
    ; The final balance is returned, as a 64-bit non-negative integer
    ret

global process_with_guard
process_with_guard:
    ; TODO: Define the `process_with_guard` function
    ; It takes as arguments:
    ; 1. a starting balance, as a 64-bit non-negative integer
    ; 2. the address of an array of transaction (which are function addresses)
    ; 3. the number of transactions in the array, as a 64-bit non-negative integer
    ; 4. the memory address of a guard function.
    ;
    ; For each transaction in sequence, this function:
    ; 1. Apply the transaction to the running balance to compute a tentative new balance
    ; 2. Call the guard with the tentative balance
    ; 3. If the guard returns non-zero, the running balance becomes the tentative balance
    ; 4. If the guard returns zero, the running balance is unchanged and the transaction is skipped
    ;
    ; The function returns two values, respectively:
    ; 1. the final balance, after all updates (if any)
    ; 2. the number of approved transactions (those for which the guard function returns non-zero)
    ;
    ; Remember that the two first integer results are return in `rax` and `rdx`, respectively
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
