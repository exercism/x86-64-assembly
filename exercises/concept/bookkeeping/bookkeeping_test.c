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

static uint64_t identity(uint64_t x) {
    return clobber(x);
}
static uint64_t add_one(uint64_t x) {
    return clobber(x + 1);
}
static uint64_t add_five(uint64_t x) {
    return clobber(x + 5);
}
static uint64_t double_it(uint64_t x) {
    return clobber(x * 2);
}
static uint64_t to_zero(uint64_t x) {
    return clobber(x * 0);
}
static uint64_t sub_sixty(uint64_t x) {
    return clobber(x - 60);
}

static bool always_true(uint64_t x) {
    x = 1;
    return clobber(x);
}
static bool always_false(uint64_t x) {
    x = 0;
    return clobber(x);
}

static bool not_below_50(uint64_t x) {
    return clobber(x >= 50);
}
static bool is_even(uint64_t x) {
    return clobber(!(x & 1));
}

extern void remember_transaction(transaction_t fn);
extern uint64_t apply_remembered(uint64_t balance);
extern void register_transaction(transaction_t table[], size_t index, transaction_t fn);
extern uint64_t select_transaction(const transaction_t table[], size_t index, uint64_t balance);
extern uint64_t process_statement(uint64_t balance, const transaction_t transactions[], size_t num_transactions);
extern result_t process_with_guard(uint64_t balance, const transaction_t transaction[], size_t num_transactions, const guard_t guard);

void setUp(void) {
}

void tearDown(void) {
}

// TASK: 1
void test_remember_and_apply_identity(void) {
    remember_transaction(identity);
    TEST_ASSERT_EQUAL_UINT64(100, apply_remembered(100));
}

void test_remember_and_apply_add_one_to_zero(void) {
    TEST_IGNORE();
    remember_transaction(add_one);
    TEST_ASSERT_EQUAL_UINT64(1, apply_remembered(0));
}

void test_remember_and_apply_add_five(void) {
    TEST_IGNORE();
    remember_transaction(add_five);
    TEST_ASSERT_EQUAL_UINT64(55, apply_remembered(50));
}

void test_remember_and_apply_double(void) {
    TEST_IGNORE();
    remember_transaction(double_it);
    TEST_ASSERT_EQUAL_UINT64(200, apply_remembered(100));
}

void test_remember_and_apply_collapses_to_zero(void) {
    TEST_IGNORE();
    remember_transaction(to_zero);
    TEST_ASSERT_EQUAL_UINT64(0, apply_remembered(99999));
}

void test_remember_replaces_previous(void) {
    TEST_IGNORE();
    remember_transaction(add_five);
    remember_transaction(double_it);
    TEST_ASSERT_EQUAL_UINT64(20, apply_remembered(10));
}

void test_remember_and_apply_large_balance(void) {
    TEST_IGNORE();
    remember_transaction(double_it);
    TEST_ASSERT_EQUAL_UINT64(2000000000, apply_remembered(1000000000));
}

// TASK: 2
void test_register_and_select_at_slot_0(void) {
    TEST_IGNORE();
    transaction_t table[16];
    register_transaction(table, 0, add_five);
    TEST_ASSERT_EQUAL_UINT64(105, select_transaction(table, 0, 100));
}

void test_register_and_select_at_slot_3(void) {
    TEST_IGNORE();
    transaction_t table[16];
    register_transaction(table, 3, to_zero);
    TEST_ASSERT_EQUAL_UINT64(0, select_transaction(table, 3, 9999));
}

void test_select_picks_correct_slot_among_four(void) {
    TEST_IGNORE();
    transaction_t table[16];
    register_transaction(table, 0, add_one);
    register_transaction(table, 1, add_five);
    register_transaction(table, 2, double_it);
    register_transaction(table, 3, to_zero);
    TEST_ASSERT_EQUAL_UINT64(105, select_transaction(table, 1, 100));
}

void test_select_picks_slot_2_among_four(void) {
    TEST_IGNORE();
    transaction_t table[16];
    register_transaction(table, 0, add_one);
    register_transaction(table, 1, add_five);
    register_transaction(table, 2, double_it);
    register_transaction(table, 3, to_zero);
    TEST_ASSERT_EQUAL_UINT64(200, select_transaction(table, 2, 100));
}

void test_register_overwrites_same_slot(void) {
    TEST_IGNORE();
    transaction_t table[16];
    register_transaction(table, 0, add_five);
    register_transaction(table, 0, double_it);
    TEST_ASSERT_EQUAL_UINT64(20, select_transaction(table, 0, 10));
}

void test_register_at_slot_2_does_not_disturb_slot_0(void) {
    TEST_IGNORE();
    transaction_t table[16];
    register_transaction(table, 0, add_one);
    register_transaction(table, 2, double_it);
    TEST_ASSERT_EQUAL_UINT64(51, select_transaction(table, 0, 50));
}

void test_select_at_slot_0_zero_balance(void) {
    TEST_IGNORE();
    transaction_t table[16];
    register_transaction(table, 0, add_five);
    TEST_ASSERT_EQUAL_UINT64(5, select_transaction(table, 0, 0));
}

void test_select_large_balance(void) {
    TEST_IGNORE();
    transaction_t table[16];
    register_transaction(table, 2, add_one);
    TEST_ASSERT_EQUAL_UINT64(1000000000, select_transaction(table, 2, 999999999));
}

// TASK: 3
void test_process_statement_empty_array(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(100, process_statement(100, NULL, 0));
}

void test_process_statement_single_identity(void) {
    TEST_IGNORE();
    transaction_t transactions[] = {identity};
    TEST_ASSERT_EQUAL_UINT64(100, process_statement(100, transactions, ARRAY_SIZE(transactions)));
}

void test_process_statement_single_add_five(void) {
    TEST_IGNORE();
    transaction_t transactions[] = {add_five};
    TEST_ASSERT_EQUAL_UINT64(105, process_statement(100, transactions, ARRAY_SIZE(transactions)));
}

void test_process_statement_three_transactions(void) {
    TEST_IGNORE();
    transaction_t transactions[] = {add_five, double_it, add_one};
    TEST_ASSERT_EQUAL_UINT64(211, process_statement(100, transactions, ARRAY_SIZE(transactions)));
}

void test_process_statement_same_transaction_repeated(void) {
    TEST_IGNORE();
    transaction_t transactions[] = {double_it, double_it, double_it, double_it};
    TEST_ASSERT_EQUAL_UINT64(160, process_statement(10, transactions, ARRAY_SIZE(transactions)));
}

void test_process_statement_collapses_then_increments(void) {
    TEST_IGNORE();
    transaction_t transactions[] = {add_five, to_zero, add_one};
    TEST_ASSERT_EQUAL_UINT64(1, process_statement(99999, transactions, ARRAY_SIZE(transactions)));
}

void test_process_statement_ten_transactions(void) {
    TEST_IGNORE();
    transaction_t transactions[] = {add_one, add_one, add_one, add_one, add_one, add_one, add_one, add_one, add_one, add_one};
    TEST_ASSERT_EQUAL_UINT64(10, process_statement(0, transactions, ARRAY_SIZE(transactions)));
}

void test_process_statement_long_mixed_sequence(void) {
    TEST_IGNORE();
    transaction_t transactions[] = {add_five, double_it, to_zero, add_five, double_it, add_one};
    TEST_ASSERT_EQUAL_UINT64(11, process_statement(50, transactions, ARRAY_SIZE(transactions)));
}

// TASK: 4
void test_process_with_guard_empty_array(void) {
    TEST_IGNORE();
    const result_t expected = {.balance = 100, .approved = 0};
    const result_t actual = process_with_guard(100, NULL, 0, always_true);
    TEST_ASSERT_EQUAL_UINT64(expected.balance, actual.balance);
    TEST_ASSERT_EQUAL_UINT64(expected.approved, actual.approved);
}

void test_process_with_guard_always_approves(void) {
    TEST_IGNORE();
    const result_t expected = {.balance = 211, .approved = 3};
    transaction_t transactions[] = {add_five, double_it, add_one};
    const result_t actual = process_with_guard(100, transactions, ARRAY_SIZE(transactions), always_true);
    TEST_ASSERT_EQUAL_UINT64(expected.balance, actual.balance);
    TEST_ASSERT_EQUAL_UINT64(expected.approved, actual.approved);
}

void test_process_with_guard_always_rejects(void) {
    TEST_IGNORE();
    const result_t expected = {.balance = 100, .approved = 0};
    transaction_t transactions[] = {add_five, double_it, add_one};
    const result_t actual = process_with_guard(100, transactions, ARRAY_SIZE(transactions), always_false);
    TEST_ASSERT_EQUAL_UINT64(expected.balance, actual.balance);
    TEST_ASSERT_EQUAL_UINT64(expected.approved, actual.approved);
}

void test_process_with_guard_rejects_below_minimum(void) {
    TEST_IGNORE();
    const result_t expected = {.balance = 105, .approved = 1};
    transaction_t transactions[] = {sub_sixty, add_five, sub_sixty};
    const result_t actual = process_with_guard(100, transactions, ARRAY_SIZE(transactions), not_below_50);
    TEST_ASSERT_EQUAL_UINT64(expected.balance, actual.balance);
    TEST_ASSERT_EQUAL_UINT64(expected.approved, actual.approved);
}

void test_process_with_guard_first_rejected_others_approved(void) {
    TEST_IGNORE();
    const result_t expected = {.balance = 40, .approved = 3};
    transaction_t transactions[] = {add_five, double_it, identity, double_it};
    const result_t actual = process_with_guard(10, transactions, ARRAY_SIZE(transactions), is_even);
    TEST_ASSERT_EQUAL_UINT64(expected.balance, actual.balance);
    TEST_ASSERT_EQUAL_UINT64(expected.approved, actual.approved);
}

void test_process_with_guard_alternating(void) {
    TEST_IGNORE();
    const result_t expected = {.balance = 0, .approved = 1};
    transaction_t transactions[] = {add_one, double_it, add_one, add_five};
    const result_t actual = process_with_guard(0, transactions, ARRAY_SIZE(transactions), is_even);
    TEST_ASSERT_EQUAL_UINT64(expected.balance, actual.balance);
    TEST_ASSERT_EQUAL_UINT64(expected.approved, actual.approved);
}

void test_process_with_guard_threshold_all_approved(void) {
    TEST_IGNORE();
    const result_t expected = {.balance = 212, .approved = 3};
    transaction_t transactions[] = {add_five, add_one, double_it};
    const result_t actual = process_with_guard(100, transactions, ARRAY_SIZE(transactions), not_below_50);
    TEST_ASSERT_EQUAL_UINT64(expected.balance, actual.balance);
    TEST_ASSERT_EQUAL_UINT64(expected.approved, actual.approved);
}

void test_process_with_guard_threshold_recovery_after_rejection(void) {
    TEST_IGNORE();
    const result_t expected = {.balance = 210, .approved = 2};
    transaction_t transactions[] = {sub_sixty, add_five, double_it};
    const result_t actual = process_with_guard(100, transactions, ARRAY_SIZE(transactions), not_below_50);
    TEST_ASSERT_EQUAL_UINT64(expected.balance, actual.balance);
    TEST_ASSERT_EQUAL_UINT64(expected.approved, actual.approved);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_remember_and_apply_identity);
    RUN_TEST(test_remember_and_apply_add_one_to_zero);
    RUN_TEST(test_remember_and_apply_add_five);
    RUN_TEST(test_remember_and_apply_double);
    RUN_TEST(test_remember_and_apply_collapses_to_zero);
    RUN_TEST(test_remember_replaces_previous);
    RUN_TEST(test_remember_and_apply_large_balance);
    RUN_TEST(test_register_and_select_at_slot_0);
    RUN_TEST(test_register_and_select_at_slot_3);
    RUN_TEST(test_select_picks_correct_slot_among_four);
    RUN_TEST(test_select_picks_slot_2_among_four);
    RUN_TEST(test_register_overwrites_same_slot);
    RUN_TEST(test_register_at_slot_2_does_not_disturb_slot_0);
    RUN_TEST(test_select_at_slot_0_zero_balance);
    RUN_TEST(test_select_large_balance);
    RUN_TEST(test_process_statement_empty_array);
    RUN_TEST(test_process_statement_single_identity);
    RUN_TEST(test_process_statement_single_add_five);
    RUN_TEST(test_process_statement_three_transactions);
    RUN_TEST(test_process_statement_same_transaction_repeated);
    RUN_TEST(test_process_statement_collapses_then_increments);
    RUN_TEST(test_process_statement_ten_transactions);
    RUN_TEST(test_process_statement_long_mixed_sequence);
    RUN_TEST(test_process_with_guard_empty_array);
    RUN_TEST(test_process_with_guard_always_approves);
    RUN_TEST(test_process_with_guard_always_rejects);
    RUN_TEST(test_process_with_guard_rejects_below_minimum);
    RUN_TEST(test_process_with_guard_first_rejected_others_approved);
    RUN_TEST(test_process_with_guard_alternating);
    RUN_TEST(test_process_with_guard_threshold_all_approved);
    RUN_TEST(test_process_with_guard_threshold_recovery_after_rejection);
    return UNITY_END();
}
