#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define MAX_ARRAY_SIZE 20
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define INCOMPLETE_SEQUENCE -1

extern int64_t encode(uint8_t *buffer, const uint32_t *integers, size_t integer_count);
extern int64_t decode(uint32_t *buffer, const uint8_t *integers, size_t integer_count);

void setUp(void) {
}

void tearDown(void) {
}

void test_zero(void) {
    const uint32_t integers[] = {0};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {0};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_arbitrary_single_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {64};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {64};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_asymmetric_single_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {83};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {83};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_largest_single_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {127};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {127};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_smallest_double_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {128};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {129, 0};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_arbitrary_double_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {8192};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {192, 0};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_asymmetric_double_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {173};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {129, 45};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_largest_double_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {16383};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {255, 127};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_smallest_triple_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {16384};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {129, 128, 0};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_arbitrary_triple_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {1048576};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {192, 128, 0};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_asymmetric_triple_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {120220};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {135, 171, 28};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_largest_triple_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {2097151};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {255, 255, 127};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_smallest_quadruple_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {2097152};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {129, 128, 128, 0};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_arbitrary_quadruple_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {134217728};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {192, 128, 128, 0};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_asymmetric_quadruple_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {3503876};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {129, 213, 238, 4};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_largest_quadruple_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {268435455};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {255, 255, 255, 127};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_smallest_quintuple_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {268435456};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {129, 128, 128, 128, 0};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_arbitrary_quintuple_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {4278190080};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {143, 248, 128, 128, 0};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_asymmetric_quintuple_byte(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {2254790917};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {136, 179, 149, 194, 5};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_maximum_32bit_integer_input(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {4294967295};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {143, 255, 255, 255, 127};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_two_singlebyte_values(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {64, 127};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {64, 127};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_two_multibyte_values(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {16384, 1193046};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {129, 128, 0, 200, 232, 86};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_many_multibyte_values(void) {
    TEST_IGNORE();
    const uint32_t integers[] = {8192, 1193046, 268435455, 0, 16383, 16384};
    uint8_t actual[MAX_ARRAY_SIZE];
    const uint8_t expected[] = {192, 0, 200, 232, 86, 255, 255, 255, 127, 0, 255, 127, 129, 128, 0};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), encode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_one_byte(void) {
    TEST_IGNORE();
    const uint8_t integers[] = {127};
    uint32_t actual[MAX_ARRAY_SIZE];
    const uint32_t expected[] = {127};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), decode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_two_bytes(void) {
    TEST_IGNORE();
    const uint8_t integers[] = {192, 0};
    uint32_t actual[MAX_ARRAY_SIZE];
    const uint32_t expected[] = {8192};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), decode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_three_bytes(void) {
    TEST_IGNORE();
    const uint8_t integers[] = {255, 255, 127};
    uint32_t actual[MAX_ARRAY_SIZE];
    const uint32_t expected[] = {2097151};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), decode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_four_bytes(void) {
    TEST_IGNORE();
    const uint8_t integers[] = {129, 128, 128, 0};
    uint32_t actual[MAX_ARRAY_SIZE];
    const uint32_t expected[] = {2097152};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), decode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_maximum_32bit_integer(void) {
    TEST_IGNORE();
    const uint8_t integers[] = {143, 255, 255, 255, 127};
    uint32_t actual[MAX_ARRAY_SIZE];
    const uint32_t expected[] = {4294967295};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), decode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

void test_incomplete_sequence_causes_error(void) {
    TEST_IGNORE();
    const uint8_t integers[] = {255};
    uint32_t actual[MAX_ARRAY_SIZE];
    TEST_ASSERT_EQUAL(INCOMPLETE_SEQUENCE, decode(actual, integers, ARRAY_SIZE(integers)));
}

void test_incomplete_sequence_causes_error_even_if_value_is_zero(void) {
    TEST_IGNORE();
    const uint8_t integers[] = {128};
    uint32_t actual[MAX_ARRAY_SIZE];
    TEST_ASSERT_EQUAL(INCOMPLETE_SEQUENCE, decode(actual, integers, ARRAY_SIZE(integers)));
}

void test_multiple_values(void) {
    TEST_IGNORE();
    const uint8_t integers[] = {192, 0, 200, 232, 86, 255, 255, 255, 127, 0, 255, 127, 129, 128, 0};
    uint32_t actual[MAX_ARRAY_SIZE];
    const uint32_t expected[] = {8192, 1193046, 268435455, 0, 16383, 16384};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), decode(actual, integers, ARRAY_SIZE(integers)));
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, ARRAY_SIZE(expected));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_zero);
    RUN_TEST(test_arbitrary_single_byte);
    RUN_TEST(test_asymmetric_single_byte);
    RUN_TEST(test_largest_single_byte);
    RUN_TEST(test_smallest_double_byte);
    RUN_TEST(test_arbitrary_double_byte);
    RUN_TEST(test_asymmetric_double_byte);
    RUN_TEST(test_largest_double_byte);
    RUN_TEST(test_smallest_triple_byte);
    RUN_TEST(test_arbitrary_triple_byte);
    RUN_TEST(test_asymmetric_triple_byte);
    RUN_TEST(test_largest_triple_byte);
    RUN_TEST(test_smallest_quadruple_byte);
    RUN_TEST(test_arbitrary_quadruple_byte);
    RUN_TEST(test_asymmetric_quadruple_byte);
    RUN_TEST(test_largest_quadruple_byte);
    RUN_TEST(test_smallest_quintuple_byte);
    RUN_TEST(test_arbitrary_quintuple_byte);
    RUN_TEST(test_asymmetric_quintuple_byte);
    RUN_TEST(test_maximum_32bit_integer_input);
    RUN_TEST(test_two_singlebyte_values);
    RUN_TEST(test_two_multibyte_values);
    RUN_TEST(test_many_multibyte_values);
    RUN_TEST(test_one_byte);
    RUN_TEST(test_two_bytes);
    RUN_TEST(test_three_bytes);
    RUN_TEST(test_four_bytes);
    RUN_TEST(test_maximum_32bit_integer);
    RUN_TEST(test_incomplete_sequence_causes_error);
    RUN_TEST(test_incomplete_sequence_causes_error_even_if_value_is_zero);
    RUN_TEST(test_multiple_values);
    return UNITY_END();
}
