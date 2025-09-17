#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define BUFFER_SIZE 10
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern size_t combinations(uint16_t output[], uint16_t sum, size_t size, const uint16_t exclude);

void setUp(void) {
}

void tearDown(void) {
}

void test_1(void) {
    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000000000000010};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 1, 1, 0));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_2(void) {
    TEST_IGNORE();

    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000000000000100};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 2, 1, 0));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_3(void) {
    TEST_IGNORE();

    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000000000001000};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 3, 1, 0));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_4(void) {
    TEST_IGNORE();

    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000000000010000};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 4, 1, 0));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_5(void) {
    TEST_IGNORE();

    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000000000100000};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 5, 1, 0));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_6(void) {
    TEST_IGNORE();

    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000000001000000};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 6, 1, 0));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_7(void) {
    TEST_IGNORE();

    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000000010000000};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 7, 1, 0));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_8(void) {
    TEST_IGNORE();

    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000000100000000};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 8, 1, 0));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_9(void) {
    TEST_IGNORE();

    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000001000000000};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 9, 1, 0));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_cage_with_sum_45_contains_all_digits_19(void) {
    TEST_IGNORE();

    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000001111111110};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 45, 9, 0));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_cage_with_only_1_possible_combination(void) {
    TEST_IGNORE();

    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000000000010110};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 7, 3, 0));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_cage_with_several_combinations(void) {
    TEST_IGNORE();

    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000000001010000, 0b0000000010001000, 0b0000000100000100, 0b0000001000000010};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 10, 2, 0));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_cage_with_several_combinations_that_is_restricted(void) {
    TEST_IGNORE();

    uint16_t buffer[BUFFER_SIZE];
    const uint16_t expected[] = {0b0000000010001000, 0b0000000100000100};
    const uint16_t exclude = 0b0000000000010010;

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 10, 2, exclude));
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_1);
    RUN_TEST(test_2);
    RUN_TEST(test_3);
    RUN_TEST(test_4);
    RUN_TEST(test_5);
    RUN_TEST(test_6);
    RUN_TEST(test_7);
    RUN_TEST(test_8);
    RUN_TEST(test_9);
    RUN_TEST(test_cage_with_sum_45_contains_all_digits_19);
    RUN_TEST(test_cage_with_only_1_possible_combination);
    RUN_TEST(test_cage_with_several_combinations);
    RUN_TEST(test_cage_with_several_combinations_that_is_restricted);
    return UNITY_END();
}
