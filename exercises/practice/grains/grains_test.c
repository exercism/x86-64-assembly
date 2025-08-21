#include "vendor/unity.h"

extern uint64_t square(int64_t number);
extern uint64_t total(void);

void setUp(void) {
}

void tearDown(void) {
}

void test_grains_on_square_1(void) {
    TEST_ASSERT_EQUAL_UINT64(UINT64_C(1), square(1));
}

void test_grains_on_square_2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(UINT64_C(2), square(2));
}

void test_grains_on_square_3(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(UINT64_C(4), square(3));
}

void test_grains_on_square_4(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(UINT64_C(8), square(4));
}

void test_grains_on_square_16(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(UINT64_C(32768), square(16));
}

void test_grains_on_square_32(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(UINT64_C(2147483648), square(32));
}

void test_grains_on_square_64(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(UINT64_C(9223372036854775808), square(64));
}

void test_square_0_is_invalid(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(UINT64_C(0), square(0));
}

void test_negative_square_is_invalid(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(UINT64_C(0), square(-1));
}

void test_square_greater_than_64_is_invalid(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(UINT64_C(0), square(65));
}

void test_returns_the_total_number_of_grains_on_the_board(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(UINT64_C(18446744073709551615), total());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_grains_on_square_1);
    RUN_TEST(test_grains_on_square_2);
    RUN_TEST(test_grains_on_square_3);
    RUN_TEST(test_grains_on_square_4);
    RUN_TEST(test_grains_on_square_16);
    RUN_TEST(test_grains_on_square_32);
    RUN_TEST(test_grains_on_square_64);
    RUN_TEST(test_square_0_is_invalid);
    RUN_TEST(test_negative_square_is_invalid);
    RUN_TEST(test_square_greater_than_64_is_invalid);
    RUN_TEST(test_returns_the_total_number_of_grains_on_the_board);
    return UNITY_END();
}
