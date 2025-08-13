#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define MAX_ARRAY_SIZE 120
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern size_t triplets_with_sum(uint64_t n, uint64_t *a, uint64_t *b, uint64_t *c);

void setUp(void) {
}

void tearDown(void) {
}

void test_triplets_whose_sum_is_12(void) {
    const uint64_t expected_a[] = {3};
    const uint64_t expected_b[] = {4};
    const uint64_t expected_c[] = {5};
    uint64_t actual_a[MAX_ARRAY_SIZE];
    uint64_t actual_b[MAX_ARRAY_SIZE];
    uint64_t actual_c[MAX_ARRAY_SIZE];
    const size_t size = triplets_with_sum(12, actual_a, actual_b, actual_c);
    TEST_ASSERT_EQUAL_UINT(ARRAY_SIZE(expected_a), size);
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_a, actual_a, size, "a");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_b, actual_b, size, "b");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_c, actual_c, size, "c");
}

void test_triplets_whose_sum_is_108(void) {
    TEST_IGNORE();
    const uint64_t expected_a[] = {27};
    const uint64_t expected_b[] = {36};
    const uint64_t expected_c[] = {45};
    uint64_t actual_a[MAX_ARRAY_SIZE];
    uint64_t actual_b[MAX_ARRAY_SIZE];
    uint64_t actual_c[MAX_ARRAY_SIZE];
    const size_t size = triplets_with_sum(108, actual_a, actual_b, actual_c);
    TEST_ASSERT_EQUAL_UINT(ARRAY_SIZE(expected_a), size);
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_a, actual_a, size, "a");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_b, actual_b, size, "b");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_c, actual_c, size, "c");
}

void test_triplets_whose_sum_is_1000(void) {
    TEST_IGNORE();
    const uint64_t expected_a[] = {200};
    const uint64_t expected_b[] = {375};
    const uint64_t expected_c[] = {425};
    uint64_t actual_a[MAX_ARRAY_SIZE];
    uint64_t actual_b[MAX_ARRAY_SIZE];
    uint64_t actual_c[MAX_ARRAY_SIZE];
    const size_t size = triplets_with_sum(1000, actual_a, actual_b, actual_c);
    TEST_ASSERT_EQUAL_UINT(ARRAY_SIZE(expected_a), size);
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_a, actual_a, size, "a");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_b, actual_b, size, "b");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_c, actual_c, size, "c");
}

void test_no_matching_triplets_for_1001(void) {
    TEST_IGNORE();
    uint64_t actual_a[MAX_ARRAY_SIZE];
    uint64_t actual_b[MAX_ARRAY_SIZE];
    uint64_t actual_c[MAX_ARRAY_SIZE];
    const size_t size = triplets_with_sum(1001, actual_a, actual_b, actual_c);
    TEST_ASSERT_EQUAL_UINT(0U, size);
}

void test_returns_all_matching_triplets(void) {
    TEST_IGNORE();
    const uint64_t expected_a[] = {9, 15};
    const uint64_t expected_b[] = {40, 36};
    const uint64_t expected_c[] = {41, 39};
    uint64_t actual_a[MAX_ARRAY_SIZE];
    uint64_t actual_b[MAX_ARRAY_SIZE];
    uint64_t actual_c[MAX_ARRAY_SIZE];
    const size_t size = triplets_with_sum(90, actual_a, actual_b, actual_c);
    TEST_ASSERT_EQUAL_UINT(ARRAY_SIZE(expected_a), size);
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_a, actual_a, size, "a");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_b, actual_b, size, "b");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_c, actual_c, size, "c");
}

void test_several_matching_triplets(void) {
    TEST_IGNORE();
    const uint64_t expected_a[] = {40, 56, 105, 120, 140, 168, 210, 240};
    const uint64_t expected_b[] = {399, 390, 360, 350, 336, 315, 280, 252};
    const uint64_t expected_c[] = {401, 394, 375, 370, 364, 357, 350, 348};
    uint64_t actual_a[MAX_ARRAY_SIZE];
    uint64_t actual_b[MAX_ARRAY_SIZE];
    uint64_t actual_c[MAX_ARRAY_SIZE];
    const size_t size = triplets_with_sum(840, actual_a, actual_b, actual_c);
    TEST_ASSERT_EQUAL_UINT(ARRAY_SIZE(expected_a), size);
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_a, actual_a, size, "a");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_b, actual_b, size, "b");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_c, actual_c, size, "c");
}

void test_triplets_for_large_number(void) {
    TEST_IGNORE();
    const uint64_t expected_a[] = {1200, 1875, 5000, 6000, 7500};
    const uint64_t expected_b[] = {14375, 14000, 12000, 11250, 10000};
    const uint64_t expected_c[] = {14425, 14125, 13000, 12750, 12500};
    uint64_t actual_a[MAX_ARRAY_SIZE];
    uint64_t actual_b[MAX_ARRAY_SIZE];
    uint64_t actual_c[MAX_ARRAY_SIZE];
    const size_t size = triplets_with_sum(30000, actual_a, actual_b, actual_c);
    TEST_ASSERT_EQUAL_UINT(ARRAY_SIZE(expected_a), size);
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_a, actual_a, size, "a");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_b, actual_b, size, "b");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_c, actual_c, size, "c");
}

void test_triplets_for_very_large_number(void) {
    TEST_IGNORE();
    const uint64_t expected_a[] = {68145};
    const uint64_t expected_b[] = {71672};
    const uint64_t expected_c[] = {98897};
    uint64_t actual_a[MAX_ARRAY_SIZE];
    uint64_t actual_b[MAX_ARRAY_SIZE];
    uint64_t actual_c[MAX_ARRAY_SIZE];
    const size_t size = triplets_with_sum(238714, actual_a, actual_b, actual_c);
    TEST_ASSERT_EQUAL_UINT(ARRAY_SIZE(expected_a), size);
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_a, actual_a, size, "a");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_b, actual_b, size, "b");
    TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_c, actual_c, size, "c");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_triplets_whose_sum_is_12);
    RUN_TEST(test_triplets_whose_sum_is_108);
    RUN_TEST(test_triplets_whose_sum_is_1000);
    RUN_TEST(test_no_matching_triplets_for_1001);
    RUN_TEST(test_returns_all_matching_triplets);
    RUN_TEST(test_several_matching_triplets);
    RUN_TEST(test_triplets_for_large_number);
    RUN_TEST(test_triplets_for_very_large_number);
    return UNITY_END();
}
