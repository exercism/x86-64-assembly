#include "vendor/unity.h"

#include <stdint.h>

extern uint64_t largest_portion(uint64_t a, uint64_t b);
extern uint64_t double_factorial(uint32_t n);
extern double pipers_pi(uint32_t n);

void setUp(void) {
}

void tearDown(void) {
}

// TASK: 1
void test_largest_portion_small_coprime(void) {
    uint64_t a = 17ULL, b = 13ULL;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1, largest_portion(a, b), "Passed arguments are: 17, 13");
}

void test_largest_portion_b_divides_a(void) {
    TEST_IGNORE();
    uint64_t a = 48ULL, b = 12ULL;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(12, largest_portion(a, b), "Passed arguments are: 48, 12");
}

void test_largest_portion_equal_inputs(void) {
    TEST_IGNORE();
    uint64_t a = 100ULL, b = 100ULL;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(100, largest_portion(a, b), "Passed arguments are: 100, 100");
}

void test_largest_portion_first_is_zero(void) {
    TEST_IGNORE();
    uint64_t a = 0ULL, b = 42ULL;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(42, largest_portion(a, b), "Passed arguments are: 0, 42");
}

void test_largest_portion_second_is_zero(void) {
    TEST_IGNORE();
    uint64_t a = 42ULL, b = 0ULL;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(42, largest_portion(a, b), "Passed arguments are: 42, 0");
}

void test_largest_portion_both_zero(void) {
    TEST_IGNORE();
    uint64_t a = 0ULL, b = 0ULL;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(0, largest_portion(a, b), "Passed arguments are: 0, 0");
}

void test_largest_portion_large_coprime(void) {
    TEST_IGNORE();
    uint64_t a = 1000000007ULL, b = 998244353ULL;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1, largest_portion(a, b), "Passed arguments are: 1000000007, 998244353");
}

void test_largest_portion_fibonacci_pair(void) {
    TEST_IGNORE();
    uint64_t a = 12200160415121876738ULL, b = 7540113804746346429ULL;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1, largest_portion(a, b), "Passed arguments are: 12200160415121876738, 7540113804746346429");
}

// TASK: 2
void test_double_factorial_zero(void) {
    TEST_IGNORE();
    uint32_t n = 0;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1, double_factorial(n), "Passed argument is: 0");
}

void test_double_factorial_one(void) {
    TEST_IGNORE();
    uint32_t n = 1;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1, double_factorial(n), "Passed argument is: 1");
}

void test_double_factorial_four(void) {
    TEST_IGNORE();
    uint32_t n = 4;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(8, double_factorial(n), "Passed argument is: 4");
}

void test_double_factorial_ten(void) {
    TEST_IGNORE();
    uint32_t n = 10;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(3840, double_factorial(n), "Passed argument is: 10");
}

void test_double_factorial_eleven(void) {
    TEST_IGNORE();
    uint32_t n = 11;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(10395, double_factorial(n), "Passed argument is: 11");
}

void test_double_factorial_thirty_two(void) {
    TEST_IGNORE();
    uint32_t n = 32;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1371195958099968000, double_factorial(n), "Passed argument is: 32");
}

void test_double_factorial_thirty_three(void) {
    TEST_IGNORE();
    uint32_t n = 33;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(6332659870762850625, double_factorial(n), "Passed argument is: 33");
}

void test_double_factorial_uint64_wrap_no_stack_overflow(void) {
    TEST_IGNORE();
    uint32_t n = 10000000;
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(0, double_factorial(n), "Passed argument is: 10000000");
}

// TASK: 3
void test_pipers_pi_zero_terms(void) {
    TEST_IGNORE();
    uint32_t n = 0;
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(2.0, pipers_pi(n), "Passed argument is: 0");
}

void test_pipers_pi_three_terms(void) {
    TEST_IGNORE();
    uint32_t n = 3;
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(3.047619, pipers_pi(n), "Passed argument is: 3");
}

void test_pipers_pi_five_terms(void) {
    TEST_IGNORE();
    uint32_t n = 5;
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(3.1215, pipers_pi(n), "Passed argument is: 5");
}

void test_pipers_pi_ten_terms(void) {
    TEST_IGNORE();
    uint32_t n = 10;
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(3.141106, pipers_pi(n), "Passed argument is: 10");
}

void test_pipers_pi_fifteen_terms(void) {
    TEST_IGNORE();
    uint32_t n = 15;
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(3.141579, pipers_pi(n), "Passed argument is: 15");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_largest_portion_small_coprime);
    RUN_TEST(test_largest_portion_b_divides_a);
    RUN_TEST(test_largest_portion_equal_inputs);
    RUN_TEST(test_largest_portion_first_is_zero);
    RUN_TEST(test_largest_portion_second_is_zero);
    RUN_TEST(test_largest_portion_both_zero);
    RUN_TEST(test_largest_portion_large_coprime);
    RUN_TEST(test_largest_portion_fibonacci_pair);
    RUN_TEST(test_double_factorial_zero);
    RUN_TEST(test_double_factorial_one);
    RUN_TEST(test_double_factorial_four);
    RUN_TEST(test_double_factorial_ten);
    RUN_TEST(test_double_factorial_eleven);
    RUN_TEST(test_double_factorial_thirty_two);
    RUN_TEST(test_double_factorial_thirty_three);
    RUN_TEST(test_double_factorial_uint64_wrap_no_stack_overflow);
    RUN_TEST(test_pipers_pi_zero_terms);
    RUN_TEST(test_pipers_pi_three_terms);
    RUN_TEST(test_pipers_pi_five_terms);
    RUN_TEST(test_pipers_pi_ten_terms);
    RUN_TEST(test_pipers_pi_fifteen_terms);
    return UNITY_END();
}
