#include "vendor/unity.h"

#include <stdint.h>

typedef enum {
    SUCCESS = 0,
    SYNTAX_ERROR,
    UNKNOWN_OPERATION
} error_t;

typedef int64_t result_t;

extern error_t answer(result_t *result, const char *question);

void setUp(void) {
}

void tearDown(void) {
}

void test_just_a_number(void) {
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 5?"));
    TEST_ASSERT_EQUAL(5, result);
}

void test_just_a_zero(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 0?"));
    TEST_ASSERT_EQUAL(0, result);
}

void test_just_a_negative_number(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is -123?"));
    TEST_ASSERT_EQUAL(-123, result);
}

void test_addition(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 1 plus 1?"));
    TEST_ASSERT_EQUAL(2, result);
}

void test_addition_with_a_left_hand_zero(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 0 plus 2?"));
    TEST_ASSERT_EQUAL(2, result);
}

void test_addition_with_a_right_hand_zero(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 3 plus 0?"));
    TEST_ASSERT_EQUAL(3, result);
}

void test_more_addition(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 53 plus 2?"));
    TEST_ASSERT_EQUAL(55, result);
}

void test_addition_with_negative_numbers(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is -1 plus -10?"));
    TEST_ASSERT_EQUAL(-11, result);
}

void test_large_addition(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 123 plus 45678?"));
    TEST_ASSERT_EQUAL(45801, result);
}

void test_subtraction(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 4 minus -12?"));
    TEST_ASSERT_EQUAL(16, result);
}

void test_multiplication(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is -3 multiplied by 25?"));
    TEST_ASSERT_EQUAL(-75, result);
}

void test_division(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 33 divided by -3?"));
    TEST_ASSERT_EQUAL(-11, result);
}

void test_multiple_additions(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 1 plus 1 plus 1?"));
    TEST_ASSERT_EQUAL(3, result);
}

void test_addition_and_subtraction(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 1 plus 5 minus -2?"));
    TEST_ASSERT_EQUAL(8, result);
}

void test_multiple_subtraction(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 20 minus 4 minus 13?"));
    TEST_ASSERT_EQUAL(3, result);
}

void test_subtraction_then_addition(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 17 minus 6 plus 3?"));
    TEST_ASSERT_EQUAL(14, result);
}

void test_multiple_multiplication(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is 2 multiplied by -2 multiplied by 3?"));
    TEST_ASSERT_EQUAL(-12, result);
}

void test_addition_and_multiplication(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is -3 plus 7 multiplied by -2?"));
    TEST_ASSERT_EQUAL(-8, result);
}

void test_multiple_division(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "What is -12 divided by 2 divided by -3?"));
    TEST_ASSERT_EQUAL(2, result);
}

void test_unknown_operation(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(UNKNOWN_OPERATION, answer(&result, "What is 52 cubed?"));
}

void test_non_math_question(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(UNKNOWN_OPERATION, answer(&result, "Who is the President of the United States?"));
}

void test_reject_problem_missing_an_operand(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SYNTAX_ERROR, answer(&result, "What is 1 plus?"));
}

void test_reject_problem_with_no_operands_or_operators(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SYNTAX_ERROR, answer(&result, "What is?"));
}

void test_reject_two_operations_in_a_row(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SYNTAX_ERROR, answer(&result, "What is 1 plus plus 2?"));
}

void test_reject_two_numbers_in_a_row(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SYNTAX_ERROR, answer(&result, "What is 1 plus 2 1?"));
}

void test_reject_postfix_notation(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SYNTAX_ERROR, answer(&result, "What is 1 2 plus?"));
}

void test_reject_prefix_notation(void) {
    TEST_IGNORE();
    result_t result;
    TEST_ASSERT_EQUAL(SYNTAX_ERROR, answer(&result, "What is plus 1 2?"));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_just_a_number);
    RUN_TEST(test_just_a_zero);
    RUN_TEST(test_just_a_negative_number);
    RUN_TEST(test_addition);
    RUN_TEST(test_addition_with_a_left_hand_zero);
    RUN_TEST(test_addition_with_a_right_hand_zero);
    RUN_TEST(test_more_addition);
    RUN_TEST(test_addition_with_negative_numbers);
    RUN_TEST(test_large_addition);
    RUN_TEST(test_subtraction);
    RUN_TEST(test_multiplication);
    RUN_TEST(test_division);
    RUN_TEST(test_multiple_additions);
    RUN_TEST(test_addition_and_subtraction);
    RUN_TEST(test_multiple_subtraction);
    RUN_TEST(test_subtraction_then_addition);
    RUN_TEST(test_multiple_multiplication);
    RUN_TEST(test_addition_and_multiplication);
    RUN_TEST(test_multiple_division);
    RUN_TEST(test_unknown_operation);
    RUN_TEST(test_non_math_question);
    RUN_TEST(test_reject_problem_missing_an_operand);
    RUN_TEST(test_reject_problem_with_no_operands_or_operators);
    RUN_TEST(test_reject_two_operations_in_a_row);
    RUN_TEST(test_reject_two_numbers_in_a_row);
    RUN_TEST(test_reject_postfix_notation);
    RUN_TEST(test_reject_prefix_notation);
    return UNITY_END();
}
