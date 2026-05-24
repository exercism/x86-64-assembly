# Instructions

You are the bookkeeper at a small village bank.
Each customer holds an account, and you keep its balance in your ledger.
Throughout the year, transactions are applied to these balances: interest is credited, fees are deducted, bonuses are paid out, penalties are charged.
Every transaction takes a balance and produces a new one.

You have four tasks.

~~~~exercism/note
You may assume that every thunk (transactions and guards) in this exercise is a function that:
1. takes a 64-bit non-negative integer as argument
2. and also returns a 64-bit non-negative integer.
~~~~

## 1. Remember a transaction

The teller learns a new transaction at the start of the day and writes it down so it can be applied later when a customer arrives.

Define two functions:

- `remember_transaction` takes a transaction and stores it in memory.
- `apply_remembered` takes a balance and applies the previously-stored transaction to it.

Example, assuming `add_interest` is a transaction that credits five units of interest:

```c
remember_transaction(add_interest);
apply_remembered(100);
// => 105

remember_transaction(service_fee);
apply_remembered(100);
// => 98   (assuming service_fee deducts 2)
```

For `remember_transaction`:

- The argument is a transaction to be saved for later use.
- There is no return value.

For `apply_remembered`:

- The argument is a 64-bit non-negative integer.
- The return value is a 64-bit non-negative integer.

## 2. The bank's manual

The bank's manual has a list of frequent transactions stored in a _dispatch table_.
Each branch maintains its own copy of the list, and may register different transactions depending on local policy.

Define two functions that operate on a dispatch table supplied by the caller:

- `register_transaction` takes the memory address of a dispatch table, an index, and a transaction.
  It stores this transaction at the given index in the table.
- `select_transaction` takes the memory address of a dispatch table, an index, and a balance.
  It looks up the transaction at the given index and applies it to the balance, returning the new balance.

`select_transaction` should reach the looked-up transaction with a single indirect tail call.

Example, assuming `manual` is the memory address of a dispatch table with four empty slots:

```c
register_transaction(manual, 0, monthly_interest);
register_transaction(manual, 1, service_fee);

select_transaction(manual, 0, 100);
// applies monthly_interest to 100

select_transaction(manual, 1, 100);
// applies service_fee to 100
```

For `register_transaction`:

- The first argument is the memory address of a dispatch table.
- The second argument is a 64-bit non-negative integer (the index).
- The third argument is a transaction.
- There is no return value.

For `select_transaction`:

- The first argument is the memory address of a dispatch table.
- The second argument is a 64-bit non-negative integer (the index).
- The third argument is a 64-bit non-negative integer (the balance).
- The return value is a 64-bit non-negative integer.

## 3. Process a monthly statement

At the end of the month, a customer's account is reconciled.
Every transaction that took place over the month is applied to the starting balance, one after the other, and the result is the new balance.

Define a function `process_statement` that takes a starting balance, the memory address of an array of transactions, and the number of transactions in the array.
For each transaction in sequence, it should apply the transaction to the running balance, then use the result as the balance for the next transaction.
The final balance is returned.

In pseudocode, `process_statement(balance, transactions, n)` computes:

```
for each transaction in transactions:
    balance = transaction(balance)
return balance
```

Example, assuming `transactions` is the memory address of an array containing the transactions `add_interest`, `service_fee`, and `add_interest` in that order, where `add_interest` adds 5 and `service_fee` deducts 2:

```c
process_statement(100, transactions, 3);
// add_interest(100) = 105
// service_fee(105)  = 103
// add_interest(103) = 108
// => 108
```

The first argument is a 64-bit non-negative integer.
The second argument is the memory address of an array of transactions.
The third argument is a 64-bit non-negative integer (the array length).
The return value is a 64-bit non-negative integer.

## 4. Process with a guard

The bank's policy requires that certain transactions be checked before being committed.
A **guard** is a function that inspects a proposed balance and decides whether it is acceptable.
This guard function returns a non-zero value to approve, or zero to reject.

Define `process_with_guard` that takes a starting balance, the memory address of an array of transactions, the number of transactions in the array, and a guard function.
For each transaction in sequence:

1. Apply the transaction to the running balance to compute a tentative new balance.
2. Call the guard with the tentative balance.
3. If the guard returns non-zero, commit: the running balance becomes the tentative balance.
4. If the guard returns zero, the running balance is unchanged and the transaction is skipped.

After all transactions have been processed, return the final balance alongside the number of approved transactions.

In pseudocode, `process_with_guard(balance, transactions, n, guard)` computes:

```
approved = 0
for each transaction in transactions:
    tentative = transaction(balance)
    if guard(tentative) is non-zero:
        balance = tentative
        approved = approved + 1
return balance, approved
```

For example, assume that:

1. `add_interest` is a transaction that adds 5 and `service_fee` is another transaction that deducts 2
2. `at_least_10` is a guard that returns a non-zero value when the balance is >= 10

Then:

```c
process_with_guard(5, {add_interest, service_fee, add_interest}, 3, at_least_10);
// add_interest(5) = 10; at_least_10(10) != 0;
// => balance = 10, approved = 1
//
// service_fee(10) = 8; at_least_10(8) = 0;
// => balance = 10, approved = 1
//
// add_interest(10) = 15; at_least_10(15) != 0;
// => balance = 15, approved = 2
//
// final balance (15) is returned in rax
// number of approved transactions (2) is returned in rdx
```

For `process_with_guard`:

- The first argument is a 64-bit non-negative integer (the starting balance).
- The second argument is the memory address of an array of transactions.
- The third argument is a 64-bit non-negative integer (the array length).
- The fourth argument is a guard function that takes a 64-bit non-negative integer and returns a 64-bit non-negative integer.
- The return values are two 64-bit non-negative integers: the final balance in `rax`, and the count of approved transactions in `rdx`.
