FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef uint64_t (*transaction_t)(uint64_t);
typedef bool (*guard_t)(uint64_t);

typedef struct {
    uint64_t balance;
    uint64_t approved;
} result_t;

extern uint64_t clobber(uint64_t result);

static uint64_t identity(uint64_t x)   { return clobber(x); }
static uint64_t add_one(uint64_t x)    { return clobber(x + 1); }
static uint64_t add_five(uint64_t x)   { return clobber(x + 5); }
static uint64_t double_it(uint64_t x)  { return clobber(x * 2); }
static uint64_t to_zero(uint64_t x)    { return clobber(x * 0); }
static uint64_t sub_sixty(uint64_t x)  { return clobber(x - 60); }

static bool always_true(uint64_t x) { x = 1; return clobber(x); }
static bool always_false(uint64_t x) { x = 0; return clobber(x); }

static bool not_below_50(uint64_t x) { return clobber(x >= 50); }
static bool is_even(uint64_t x) { return clobber(!(x & 1)); }

extern void remember_transaction(transaction_t fn);
extern uint64_t apply_remembered(uint64_t balance);
extern void register_transaction(transaction_t table[], size_t index, transaction_t fn);
extern uint64_t select_transaction(const transaction_t table[], size_t index, uint64_t balance);
extern uint64_t process_statement(uint64_t balance, const transaction_t transactions[], size_t num_transactions);
extern result_t process_with_guard(uint64_t balance, const transaction_t transaction[], size_t num_transactions, const guard_t guard);
"""


def extra_cases():
    return [
        {
            "task_id": 1,
            "description": "remember_and_apply_identity",
            "property": "remember_then_apply",
            "input": ["identity", 100],
            "expected": 100,
        },
        {
            "task_id": 1,
            "description": "remember_and_apply_add_one_to_zero",
            "property": "remember_then_apply",
            "input": ["add_one", 0],
            "expected": 1,
        },
        {
            "task_id": 1,
            "description": "remember_and_apply_add_five",
            "property": "remember_then_apply",
            "input": ["add_five", 50],
            "expected": 55,
        },
        {
            "task_id": 1,
            "description": "remember_and_apply_double",
            "property": "remember_then_apply",
            "input": ["double_it", 100],
            "expected": 200,
        },
        {
            "task_id": 1,
            "description": "remember_and_apply_collapses_to_zero",
            "property": "remember_then_apply",
            "input": ["to_zero", 99999],
            "expected": 0,
        },
        {
            "task_id": 1,
            "description": "remember_replaces_previous",
            "property": "remember_then_apply",
            "input": ["add_five", "double_it", 10],
            "expected": 20,
        },
        {
            "task_id": 1,
            "description": "remember_and_apply_large_balance",
            "property": "remember_then_apply",
            "input": ["double_it", 1000000000],
            "expected": 2000000000,
        },
        {
            "task_id": 2,
            "description": "register_and_select_at_slot_0",
            "property": "register_then_select",
            "input": [[("add_five", 0)], 100, 0],
            "expected": 105,
        },
        {
            "task_id": 2,
            "description": "register_and_select_at_slot_3",
            "property": "register_then_select",
            "input": [[("to_zero", 3)], 9999, 3],
            "expected": 0,
        },
        {
            "task_id": 2,
            "description": "select_picks_correct_slot_among_four",
            "property": "register_then_select",
            "input": [
                [("add_one", 0), ("add_five", 1), ("double_it", 2), ("to_zero", 3)],
                100,
                1,
            ],
            "expected": 105,
        },
        {
            "task_id": 2,
            "description": "select_picks_slot_2_among_four",
            "property": "register_then_select",
            "input": [
                [("add_one", 0), ("add_five", 1), ("double_it", 2), ("to_zero", 3)],
                100,
                2,
            ],
            "expected": 200,
        },
        {
            "task_id": 2,
            "description": "register_overwrites_same_slot",
            "property": "register_then_select",
            "input": [[("add_five", 0), ("double_it", 0)], 10, 0],
            "expected": 20,
        },
        {
            "task_id": 2,
            "description": "register_at_slot_2_does_not_disturb_slot_0",
            "property": "register_then_select",
            "input": [[("add_one", 0), ("double_it", 2)], 50, 0],
            "expected": 51,
        },
        {
            "task_id": 2,
            "description": "select_at_slot_0_zero_balance",
            "property": "register_then_select",
            "input": [[("add_five", 0)], 0, 0],
            "expected": 5,
        },
        {
            "task_id": 2,
            "description": "select_large_balance",
            "property": "register_then_select",
            "input": [[("add_one", 2)], 999999999, 2],
            "expected": 1000000000,
        },
        {
            "task_id": 3,
            "description": "process_statement_empty_array",
            "property": "process_statement",
            "input": [100, [], 0],
            "expected": 100,
        },
        {
            "task_id": 3,
            "description": "process_statement_single_identity",
            "property": "process_statement",
            "input": [100, ["identity"], 1],
            "expected": 100,
        },
        {
            "task_id": 3,
            "description": "process_statement_single_add_five",
            "property": "process_statement",
            "input": [100, ["add_five"], 1],
            "expected": 105,
        },
        {
            "task_id": 3,
            "description": "process_statement_three_transactions",
            "property": "process_statement",
            "input": [100, ["add_five", "double_it", "add_one"], 3],
            "expected": 211,
        },
        {
            "task_id": 3,
            "description": "process_statement_same_transaction_repeated",
            "property": "process_statement",
            "input": [10, ["double_it", "double_it", "double_it", "double_it"], 4],
            "expected": 160,
        },
        {
            "task_id": 3,
            "description": "process_statement_collapses_then_increments",
            "property": "process_statement",
            "input": [99999, ["add_five", "to_zero", "add_one"], 3],
            "expected": 1,
        },
        {
            "task_id": 3,
            "description": "process_statement_ten_transactions",
            "property": "process_statement",
            "input": [0, ["add_one"] * 10, 10],
            "expected": 10,
        },
        {
            "task_id": 3,
            "description": "process_statement_long_mixed_sequence",
            "property": "process_statement",
            "input": [
                50,
                [
                    "add_five",
                    "double_it",
                    "to_zero",
                    "add_five",
                    "double_it",
                    "add_one",
                ],
                6,
            ],
            "expected": 11,
        },
        {
            "task_id": 4,
            "description": "process_with_guard_empty_array",
            "property": "process_with_guard",
            "input": [100, [], 0, "always_true"],
            "expected": {"balance": 100, "approved": 0},
        },
        {
            "task_id": 4,
            "description": "process_with_guard_always_approves",
            "property": "process_with_guard",
            "input": [100, ["add_five", "double_it", "add_one"], 3, "always_true"],
            "expected": {"balance": 211, "approved": 3},
        },
        {
            "task_id": 4,
            "description": "process_with_guard_always_rejects",
            "property": "process_with_guard",
            "input": [100, ["add_five", "double_it", "add_one"], 3, "always_false"],
            "expected": {"balance": 100, "approved": 0},
        },
        {
            "task_id": 4,
            "description": "process_with_guard_rejects_below_minimum",
            "property": "process_with_guard",
            "input": [100, ["sub_sixty", "add_five", "sub_sixty"], 3, "not_below_50"],
            "expected": {"balance": 105, "approved": 1},
        },
        {
            "task_id": 4,
            "description": "process_with_guard_first_rejected_others_approved",
            "property": "process_with_guard",
            "input": [
                10,
                ["add_five", "double_it", "identity", "double_it"],
                4,
                "is_even",
            ],
            "expected": {"balance": 40, "approved": 3},
        },
        {
            "task_id": 4,
            "description": "process_with_guard_alternating",
            "property": "process_with_guard",
            "input": [0, ["add_one", "double_it", "add_one", "add_five"], 4, "is_even"],
            "expected": {"balance": 0, "approved": 1},
        },
        {
            "task_id": 4,
            "description": "process_with_guard_threshold_all_approved",
            "property": "process_with_guard",
            "input": [100, ["add_five", "add_one", "double_it"], 3, "not_below_50"],
            "expected": {"balance": 212, "approved": 3},
        },
        {
            "task_id": 4,
            "description": "process_with_guard_threshold_recovery_after_rejection",
            "property": "process_with_guard",
            "input": [100, ["sub_sixty", "add_five", "double_it"], 3, "not_below_50"],
            "expected": {"balance": 210, "approved": 2},
        },
    ]


def to_literal(value):
    return str(value).replace("'", "")


def array_literal(array):
    return to_literal(array).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "remember_then_apply":
        for fn in inp[0:-1]:
            str_list.append(f"remember_transaction({to_literal(fn)});")
        str_list.append(
            f"TEST_ASSERT_EQUAL_UINT64({expected}, apply_remembered({inp[-1]}));"
        )
    elif prop == "register_then_select":
        str_list.append("transaction_t table[16];")
        for fn, idx in inp[0]:
            str_list.append(f"register_transaction(table, {idx}, {to_literal(fn)});")
        str_list.append(
            f"TEST_ASSERT_EQUAL_UINT64({expected}, select_transaction(table, {inp[2]}, {inp[1]}));"
        )
    elif prop == "process_statement":
        if inp[1]:
            str_list.append(f"transaction_t transactions[] = {array_literal(inp[1])};")
            str_list.append(
                f"TEST_ASSERT_EQUAL_UINT64({expected}, {prop}({inp[0]}, transactions, ARRAY_SIZE(transactions)));"
            )
        else:
            str_list.append(
                f"TEST_ASSERT_EQUAL_UINT64({expected}, {prop}({inp[0]}, NULL, 0));"
            )
    else:
        guard = f"{array_literal(inp[3])}"
        str_list.append(
            f"const result_t expected = {{ .balance = {expected['balance']}, .approved = {expected['approved']} }};"
        )
        if inp[1]:
            str_list.append(f"transaction_t transactions[] = {array_literal(inp[1])};")
            str_list.append(
                f"const result_t actual = {prop}({inp[0]}, transactions, ARRAY_SIZE(transactions), {guard});"
            )
        else:
            str_list.append(
                f"const result_t actual = {prop}({inp[0]}, NULL, 0, {guard});"
            )
        str_list.append("TEST_ASSERT_EQUAL_UINT64(expected.balance, actual.balance);")
        str_list.append("TEST_ASSERT_EQUAL_UINT64(expected.approved, actual.approved);")
    return "\n".join(str_list)
