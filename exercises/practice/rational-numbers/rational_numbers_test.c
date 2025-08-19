#include "vendor/unity.h"

#include <stdint.h>

typedef struct {
    int64_t numerator;
    int64_t denominator;
} rational_t;

extern rational_t add_rationals(rational_t r1, rational_t r2);
extern rational_t sub_rationals(rational_t r1, rational_t r2);
extern rational_t mul_rationals(rational_t r1, rational_t r2);
extern rational_t div_rationals(rational_t r1, rational_t r2);
extern rational_t abs_rational(rational_t r);
extern rational_t exprational(rational_t r, int64_t n);
extern float expreal(int64_t x, rational_t r);
extern rational_t reduce(rational_t r);

void setUp(void) {
}

void tearDown(void) {
}

void test_add_two_positive_rational_numbers(void) {
    rational_t r1 = {1, 2};
    rational_t r2 = {2, 3};
    const rational_t result = add_rationals(r1, r2);
    const rational_t expected = {7, 6};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_add_a_positive_rational_number_and_a_negative_rational_number(void) {
    TEST_IGNORE();
    rational_t r1 = {1, 2};
    rational_t r2 = {-2, 3};
    const rational_t result = add_rationals(r1, r2);
    const rational_t expected = {-1, 6};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_add_two_negative_rational_numbers(void) {
    TEST_IGNORE();
    rational_t r1 = {-1, 2};
    rational_t r2 = {-2, 3};
    const rational_t result = add_rationals(r1, r2);
    const rational_t expected = {-7, 6};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_add_a_rational_number_to_its_additive_inverse(void) {
    TEST_IGNORE();
    rational_t r1 = {1, 2};
    rational_t r2 = {-1, 2};
    const rational_t result = add_rationals(r1, r2);
    const rational_t expected = {0, 1};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_subtract_two_positive_rational_numbers(void) {
    TEST_IGNORE();
    rational_t r1 = {1, 2};
    rational_t r2 = {2, 3};
    const rational_t result = sub_rationals(r1, r2);
    const rational_t expected = {-1, 6};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_subtract_a_positive_rational_number_and_a_negative_rational_number(void) {
    TEST_IGNORE();
    rational_t r1 = {1, 2};
    rational_t r2 = {-2, 3};
    const rational_t result = sub_rationals(r1, r2);
    const rational_t expected = {7, 6};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_subtract_two_negative_rational_numbers(void) {
    TEST_IGNORE();
    rational_t r1 = {-1, 2};
    rational_t r2 = {-2, 3};
    const rational_t result = sub_rationals(r1, r2);
    const rational_t expected = {1, 6};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_subtract_a_rational_number_from_itself(void) {
    TEST_IGNORE();
    rational_t r1 = {1, 2};
    rational_t r2 = {1, 2};
    const rational_t result = sub_rationals(r1, r2);
    const rational_t expected = {0, 1};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_multiply_two_positive_rational_numbers(void) {
    TEST_IGNORE();
    rational_t r1 = {1, 2};
    rational_t r2 = {2, 3};
    const rational_t result = mul_rationals(r1, r2);
    const rational_t expected = {1, 3};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_multiply_a_negative_rational_number_by_a_positive_rational_number(void) {
    TEST_IGNORE();
    rational_t r1 = {-1, 2};
    rational_t r2 = {2, 3};
    const rational_t result = mul_rationals(r1, r2);
    const rational_t expected = {-1, 3};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_multiply_two_negative_rational_numbers(void) {
    TEST_IGNORE();
    rational_t r1 = {-1, 2};
    rational_t r2 = {-2, 3};
    const rational_t result = mul_rationals(r1, r2);
    const rational_t expected = {1, 3};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_multiply_a_rational_number_by_its_reciprocal(void) {
    TEST_IGNORE();
    rational_t r1 = {1, 2};
    rational_t r2 = {2, 1};
    const rational_t result = mul_rationals(r1, r2);
    const rational_t expected = {1, 1};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_multiply_a_rational_number_by_1(void) {
    TEST_IGNORE();
    rational_t r1 = {1, 2};
    rational_t r2 = {1, 1};
    const rational_t result = mul_rationals(r1, r2);
    const rational_t expected = {1, 2};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_multiply_a_rational_number_by_0(void) {
    TEST_IGNORE();
    rational_t r1 = {1, 2};
    rational_t r2 = {0, 1};
    const rational_t result = mul_rationals(r1, r2);
    const rational_t expected = {0, 1};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_divide_two_positive_rational_numbers(void) {
    TEST_IGNORE();
    rational_t r1 = {1, 2};
    rational_t r2 = {2, 3};
    const rational_t result = div_rationals(r1, r2);
    const rational_t expected = {3, 4};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_divide_a_positive_rational_number_by_a_negative_rational_number(void) {
    TEST_IGNORE();
    rational_t r1 = {1, 2};
    rational_t r2 = {-2, 3};
    const rational_t result = div_rationals(r1, r2);
    const rational_t expected = {-3, 4};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_divide_two_negative_rational_numbers(void) {
    TEST_IGNORE();
    rational_t r1 = {-1, 2};
    rational_t r2 = {-2, 3};
    const rational_t result = div_rationals(r1, r2);
    const rational_t expected = {3, 4};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_divide_a_rational_number_by_1(void) {
    TEST_IGNORE();
    rational_t r1 = {1, 2};
    rational_t r2 = {1, 1};
    const rational_t result = div_rationals(r1, r2);
    const rational_t expected = {1, 2};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_absolute_value_of_a_positive_rational_number(void) {
    TEST_IGNORE();
    rational_t r = {1, 2};
    const rational_t result = abs_rational(r);
    const rational_t expected = {1, 2};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_absolute_value_of_a_positive_rational_number_with_negative_numerator_and_denominator(void) {
    TEST_IGNORE();
    rational_t r = {-1, -2};
    const rational_t result = abs_rational(r);
    const rational_t expected = {1, 2};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_absolute_value_of_a_negative_rational_number(void) {
    TEST_IGNORE();
    rational_t r = {-1, 2};
    const rational_t result = abs_rational(r);
    const rational_t expected = {1, 2};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_absolute_value_of_a_negative_rational_number_with_negative_denominator(void) {
    TEST_IGNORE();
    rational_t r = {1, -2};
    const rational_t result = abs_rational(r);
    const rational_t expected = {1, 2};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_absolute_value_of_zero(void) {
    TEST_IGNORE();
    rational_t r = {0, 1};
    const rational_t result = abs_rational(r);
    const rational_t expected = {0, 1};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_absolute_value_of_a_rational_number_is_reduced_to_lowest_terms(void) {
    TEST_IGNORE();
    rational_t r = {2, 4};
    const rational_t result = abs_rational(r);
    const rational_t expected = {1, 2};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_raise_a_positive_rational_number_to_a_positive_integer_power(void) {
    TEST_IGNORE();
    rational_t r = {1, 2};
    const rational_t result = exprational(r, 3);
    const rational_t expected = {1, 8};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_raise_a_negative_rational_number_to_a_positive_integer_power(void) {
    TEST_IGNORE();
    rational_t r = {-1, 2};
    const rational_t result = exprational(r, 3);
    const rational_t expected = {-1, 8};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_raise_a_positive_rational_number_to_a_negative_integer_power(void) {
    TEST_IGNORE();
    rational_t r = {3, 5};
    const rational_t result = exprational(r, -2);
    const rational_t expected = {25, 9};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_raise_a_negative_rational_number_to_an_even_negative_integer_power(void) {
    TEST_IGNORE();
    rational_t r = {-3, 5};
    const rational_t result = exprational(r, -2);
    const rational_t expected = {25, 9};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_raise_a_negative_rational_number_to_an_odd_negative_integer_power(void) {
    TEST_IGNORE();
    rational_t r = {-3, 5};
    const rational_t result = exprational(r, -3);
    const rational_t expected = {-125, 27};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_raise_zero_to_an_integer_power(void) {
    TEST_IGNORE();
    rational_t r = {0, 1};
    const rational_t result = exprational(r, 5);
    const rational_t expected = {0, 1};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_raise_one_to_an_integer_power(void) {
    TEST_IGNORE();
    rational_t r = {1, 1};
    const rational_t result = exprational(r, 4);
    const rational_t expected = {1, 1};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_raise_a_positive_rational_number_to_the_power_of_zero(void) {
    TEST_IGNORE();
    rational_t r = {1, 2};
    const rational_t result = exprational(r, 0);
    const rational_t expected = {1, 1};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_raise_a_negative_rational_number_to_the_power_of_zero(void) {
    TEST_IGNORE();
    rational_t r = {-1, 2};
    const rational_t result = exprational(r, 0);
    const rational_t expected = {1, 1};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_raise_a_real_number_to_a_positive_rational_number(void) {
    TEST_IGNORE();
    rational_t r = {4, 3};
    const float delta = 0.000001;
    const float result = expreal(8, r);
    const float expected = 16.0;
    TEST_ASSERT_FLOAT_WITHIN(delta, expected, result);
}

void test_raise_a_real_number_to_a_negative_rational_number(void) {
    TEST_IGNORE();
    rational_t r = {-1, 2};
    const float delta = 0.000001;
    const float result = expreal(9, r);
    const float expected = 0.3333333333333333;
    TEST_ASSERT_FLOAT_WITHIN(delta, expected, result);
}

void test_raise_a_real_number_to_a_zero_rational_number(void) {
    TEST_IGNORE();
    rational_t r = {0, 1};
    const float delta = 0.000001;
    const float result = expreal(2, r);
    const float expected = 1.0;
    TEST_ASSERT_FLOAT_WITHIN(delta, expected, result);
}

void test_reduce_a_positive_rational_number_to_lowest_terms(void) {
    TEST_IGNORE();
    rational_t r = {2, 4};
    const rational_t result = reduce(r);
    const rational_t expected = {1, 2};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_reduce_places_the_minus_sign_on_the_numerator(void) {
    TEST_IGNORE();
    rational_t r = {3, -4};
    const rational_t result = reduce(r);
    const rational_t expected = {-3, 4};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_reduce_a_negative_rational_number_to_lowest_terms(void) {
    TEST_IGNORE();
    rational_t r = {-4, 6};
    const rational_t result = reduce(r);
    const rational_t expected = {-2, 3};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_reduce_a_rational_number_with_a_negative_denominator_to_lowest_terms(void) {
    TEST_IGNORE();
    rational_t r = {3, -9};
    const rational_t result = reduce(r);
    const rational_t expected = {-1, 3};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_reduce_zero_to_lowest_terms(void) {
    TEST_IGNORE();
    rational_t r = {0, 6};
    const rational_t result = reduce(r);
    const rational_t expected = {0, 1};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_reduce_an_integer_to_lowest_terms(void) {
    TEST_IGNORE();
    rational_t r = {-14, 7};
    const rational_t result = reduce(r);
    const rational_t expected = {-2, 1};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

void test_reduce_one_to_lowest_terms(void) {
    TEST_IGNORE();
    rational_t r = {13, 13};
    const rational_t result = reduce(r);
    const rational_t expected = {1, 1};
    TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);
    TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_add_two_positive_rational_numbers);
    RUN_TEST(test_add_a_positive_rational_number_and_a_negative_rational_number);
    RUN_TEST(test_add_two_negative_rational_numbers);
    RUN_TEST(test_add_a_rational_number_to_its_additive_inverse);
    RUN_TEST(test_subtract_two_positive_rational_numbers);
    RUN_TEST(test_subtract_a_positive_rational_number_and_a_negative_rational_number);
    RUN_TEST(test_subtract_two_negative_rational_numbers);
    RUN_TEST(test_subtract_a_rational_number_from_itself);
    RUN_TEST(test_multiply_two_positive_rational_numbers);
    RUN_TEST(test_multiply_a_negative_rational_number_by_a_positive_rational_number);
    RUN_TEST(test_multiply_two_negative_rational_numbers);
    RUN_TEST(test_multiply_a_rational_number_by_its_reciprocal);
    RUN_TEST(test_multiply_a_rational_number_by_1);
    RUN_TEST(test_multiply_a_rational_number_by_0);
    RUN_TEST(test_divide_two_positive_rational_numbers);
    RUN_TEST(test_divide_a_positive_rational_number_by_a_negative_rational_number);
    RUN_TEST(test_divide_two_negative_rational_numbers);
    RUN_TEST(test_divide_a_rational_number_by_1);
    RUN_TEST(test_absolute_value_of_a_positive_rational_number);
    RUN_TEST(test_absolute_value_of_a_positive_rational_number_with_negative_numerator_and_denominator);
    RUN_TEST(test_absolute_value_of_a_negative_rational_number);
    RUN_TEST(test_absolute_value_of_a_negative_rational_number_with_negative_denominator);
    RUN_TEST(test_absolute_value_of_zero);
    RUN_TEST(test_absolute_value_of_a_rational_number_is_reduced_to_lowest_terms);
    RUN_TEST(test_raise_a_positive_rational_number_to_a_positive_integer_power);
    RUN_TEST(test_raise_a_negative_rational_number_to_a_positive_integer_power);
    RUN_TEST(test_raise_a_positive_rational_number_to_a_negative_integer_power);
    RUN_TEST(test_raise_a_negative_rational_number_to_an_even_negative_integer_power);
    RUN_TEST(test_raise_a_negative_rational_number_to_an_odd_negative_integer_power);
    RUN_TEST(test_raise_zero_to_an_integer_power);
    RUN_TEST(test_raise_one_to_an_integer_power);
    RUN_TEST(test_raise_a_positive_rational_number_to_the_power_of_zero);
    RUN_TEST(test_raise_a_negative_rational_number_to_the_power_of_zero);
    RUN_TEST(test_raise_a_real_number_to_a_positive_rational_number);
    RUN_TEST(test_raise_a_real_number_to_a_negative_rational_number);
    RUN_TEST(test_raise_a_real_number_to_a_zero_rational_number);
    RUN_TEST(test_reduce_a_positive_rational_number_to_lowest_terms);
    RUN_TEST(test_reduce_places_the_minus_sign_on_the_numerator);
    RUN_TEST(test_reduce_a_negative_rational_number_to_lowest_terms);
    RUN_TEST(test_reduce_a_rational_number_with_a_negative_denominator_to_lowest_terms);
    RUN_TEST(test_reduce_zero_to_lowest_terms);
    RUN_TEST(test_reduce_an_integer_to_lowest_terms);
    RUN_TEST(test_reduce_one_to_lowest_terms);
    return UNITY_END();
}
