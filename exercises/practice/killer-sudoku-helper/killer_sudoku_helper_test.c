#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define BUFFER_SIZE 10
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern size_t combinations(uint8_t output[][BUFFER_SIZE], uint64_t sum, size_t size, const uint8_t *exclude, size_t exclude_count);

void setUp(void) {
}

void tearDown(void) {
}

void test_1(void) {
    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{1}};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 1, 1, NULL, 0));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 1);
    }
}

void test_2(void) {
    TEST_IGNORE();

    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{2}};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 2, 1, NULL, 0));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 1);
    }
}

void test_3(void) {
    TEST_IGNORE();

    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{3}};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 3, 1, NULL, 0));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 1);
    }
}

void test_4(void) {
    TEST_IGNORE();

    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{4}};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 4, 1, NULL, 0));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 1);
    }
}

void test_5(void) {
    TEST_IGNORE();

    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{5}};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 5, 1, NULL, 0));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 1);
    }
}

void test_6(void) {
    TEST_IGNORE();

    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{6}};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 6, 1, NULL, 0));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 1);
    }
}

void test_7(void) {
    TEST_IGNORE();

    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{7}};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 7, 1, NULL, 0));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 1);
    }
}

void test_8(void) {
    TEST_IGNORE();

    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{8}};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 8, 1, NULL, 0));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 1);
    }
}

void test_9(void) {
    TEST_IGNORE();

    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{9}};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 9, 1, NULL, 0));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 1);
    }
}

void test_cage_with_sum_45_contains_all_digits_19(void) {
    TEST_IGNORE();

    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{1, 2, 3, 4, 5, 6, 7, 8, 9}};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 45, 9, NULL, 0));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 9);
    }
}

void test_cage_with_only_1_possible_combination(void) {
    TEST_IGNORE();

    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{1, 2, 4}};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 7, 3, NULL, 0));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 3);
    }
}

void test_cage_with_several_combinations(void) {
    TEST_IGNORE();

    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{1, 9}, {2, 8}, {3, 7}, {4, 6}};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 10, 2, NULL, 0));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 2);
    }
}

void test_cage_with_several_combinations_that_is_restricted(void) {
    TEST_IGNORE();

    uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
    const uint8_t expected[][BUFFER_SIZE] = {{2, 8}, {3, 7}};
    const uint8_t exclude[] = {1, 4};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), combinations(buffer, 10, 2, exclude, ARRAY_SIZE(exclude)));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], 2);
    }
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
