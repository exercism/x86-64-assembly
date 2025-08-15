#include "vendor/unity.h"

#include <stdint.h>

#define INVALID_NUMBER -1

extern int64_t prime(uint64_t number);

void setUp(void) {
}

void tearDown(void) {
}

void test_first_prime(void) {
    TEST_ASSERT_EQUAL_INT64(2, prime(1));
}

void test_second_prime(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(3, prime(2));
}

void test_sixth_prime(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(13, prime(6));
}

void test_big_prime(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(104743, prime(10001));
}

void test_there_is_no_zeroth_prime(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(INVALID_NUMBER, prime(0));
}

void test_seventh_prime(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(17, prime(7));
}

void test_very_big_prime(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(821647, prime(65537));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_first_prime);
    RUN_TEST(test_second_prime);
    RUN_TEST(test_sixth_prime);
    RUN_TEST(test_big_prime);
    RUN_TEST(test_there_is_no_zeroth_prime);
    RUN_TEST(test_seventh_prime);
    RUN_TEST(test_very_big_prime);
    return UNITY_END();
}
