// Version: 0

#include "vendor/unity.h"

#define BUFFER_SIZE 16

extern void convert(int number, char *buffer);

void setUp(void) {
}

void tearDown(void) {
}

void test_the_sound_for_1_is_1(void) {
    char buffer[BUFFER_SIZE];

    convert(1, buffer);
    TEST_ASSERT_EQUAL_STRING("1", buffer);
}

void test_the_sound_for_3_is_pling(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(3, buffer);
    TEST_ASSERT_EQUAL_STRING("Pling", buffer);
}

void test_the_sound_for_5_is_plang(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(5, buffer);
    TEST_ASSERT_EQUAL_STRING("Plang", buffer);
}

void test_the_sound_for_7_is_plong(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(7, buffer);
    TEST_ASSERT_EQUAL_STRING("Plong", buffer);
}

void test_the_sound_for_6_is_pling_as_it_has_a_factor_3(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(6, buffer);
    TEST_ASSERT_EQUAL_STRING("Pling", buffer);
}

void test_2_to_the_power_3_does_not_make_a_raindrop_sound_as_3_is_the_exponent_not_the_base(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(8, buffer);
    TEST_ASSERT_EQUAL_STRING("8", buffer);
}

void test_the_sound_for_9_is_pling_as_it_has_a_factor_3(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(9, buffer);
    TEST_ASSERT_EQUAL_STRING("Pling", buffer);
}

void test_the_sound_for_10_is_plang_as_it_has_a_factor_5(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(10, buffer);
    TEST_ASSERT_EQUAL_STRING("Plang", buffer);
}

void test_the_sound_for_14_is_plong_as_it_has_a_factor_of_7(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(14, buffer);
    TEST_ASSERT_EQUAL_STRING("Plong", buffer);
}

void test_the_sound_for_15_is_plingplang_as_it_has_factors_3_and_5(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(15, buffer);
    TEST_ASSERT_EQUAL_STRING("PlingPlang", buffer);
}

void test_the_sound_for_21_is_plingplong_as_it_has_factors_3_and_7(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(21, buffer);
    TEST_ASSERT_EQUAL_STRING("PlingPlong", buffer);
}

void test_the_sound_for_25_is_plang_as_it_has_a_factor_5(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(25, buffer);
    TEST_ASSERT_EQUAL_STRING("Plang", buffer);
}

void test_the_sound_for_27_is_pling_as_it_has_a_factor_3(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(27, buffer);
    TEST_ASSERT_EQUAL_STRING("Pling", buffer);
}

void test_the_sound_for_35_is_plangplong_as_it_has_factors_5_and_7(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(35, buffer);
    TEST_ASSERT_EQUAL_STRING("PlangPlong", buffer);
}

void test_the_sound_for_49_is_plong_as_it_has_a_factor_7(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(49, buffer);
    TEST_ASSERT_EQUAL_STRING("Plong", buffer);
}

void test_the_sound_for_52_is_52(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(52, buffer);
    TEST_ASSERT_EQUAL_STRING("52", buffer);
}

void test_the_sound_for_105_is_plingplangplong_as_it_has_factors_3_5_and_7(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(105, buffer);
    TEST_ASSERT_EQUAL_STRING("PlingPlangPlong", buffer);
}

void test_the_sound_for_3125_is_plang_as_it_has_a_factor_5(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    convert(3125, buffer);
    TEST_ASSERT_EQUAL_STRING("Plang", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_the_sound_for_1_is_1);
    RUN_TEST(test_the_sound_for_3_is_pling);
    RUN_TEST(test_the_sound_for_5_is_plang);
    RUN_TEST(test_the_sound_for_7_is_plong);
    RUN_TEST(test_the_sound_for_6_is_pling_as_it_has_a_factor_3);
    RUN_TEST(test_2_to_the_power_3_does_not_make_a_raindrop_sound_as_3_is_the_exponent_not_the_base);
    RUN_TEST(test_the_sound_for_9_is_pling_as_it_has_a_factor_3);
    RUN_TEST(test_the_sound_for_10_is_plang_as_it_has_a_factor_5);
    RUN_TEST(test_the_sound_for_14_is_plong_as_it_has_a_factor_of_7);
    RUN_TEST(test_the_sound_for_15_is_plingplang_as_it_has_factors_3_and_5);
    RUN_TEST(test_the_sound_for_21_is_plingplong_as_it_has_factors_3_and_7);
    RUN_TEST(test_the_sound_for_25_is_plang_as_it_has_a_factor_5);
    RUN_TEST(test_the_sound_for_27_is_pling_as_it_has_a_factor_3);
    RUN_TEST(test_the_sound_for_35_is_plangplong_as_it_has_factors_5_and_7);
    RUN_TEST(test_the_sound_for_49_is_plong_as_it_has_a_factor_7);
    RUN_TEST(test_the_sound_for_52_is_52);
    RUN_TEST(test_the_sound_for_105_is_plingplangplong_as_it_has_factors_3_5_and_7);
    RUN_TEST(test_the_sound_for_3125_is_plang_as_it_has_a_factor_5);
    return UNITY_END();
}
