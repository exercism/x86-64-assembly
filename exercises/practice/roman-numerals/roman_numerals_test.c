// Version: 0

#include "vendor/unity.h"

#define BUFFER_SIZE 16

extern void roman(int number, char *buffer);

void setUp(void) {
}

void tearDown(void) {
}

void test_1_is_i(void) {
    char buffer[BUFFER_SIZE];

    roman(1, buffer);
    TEST_ASSERT_EQUAL_STRING("I", buffer);
}

void test_2_is_ii(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(2, buffer);
    TEST_ASSERT_EQUAL_STRING("II", buffer);
}

void test_3_is_iii(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(3, buffer);
    TEST_ASSERT_EQUAL_STRING("III", buffer);
}

void test_4_is_iv(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(4, buffer);
    TEST_ASSERT_EQUAL_STRING("IV", buffer);
}

void test_5_is_v(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(5, buffer);
    TEST_ASSERT_EQUAL_STRING("V", buffer);
}

void test_6_is_vi(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(6, buffer);
    TEST_ASSERT_EQUAL_STRING("VI", buffer);
}

void test_9_is_ix(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(9, buffer);
    TEST_ASSERT_EQUAL_STRING("IX", buffer);
}

void test_16_is_xvi(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(16, buffer);
    TEST_ASSERT_EQUAL_STRING("XVI", buffer);
}

void test_27_is_xxvii(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(27, buffer);
    TEST_ASSERT_EQUAL_STRING("XXVII", buffer);
}

void test_48_is_xlviii(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(48, buffer);
    TEST_ASSERT_EQUAL_STRING("XLVIII", buffer);
}

void test_49_is_xlix(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(49, buffer);
    TEST_ASSERT_EQUAL_STRING("XLIX", buffer);
}

void test_59_is_lix(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(59, buffer);
    TEST_ASSERT_EQUAL_STRING("LIX", buffer);
}

void test_66_is_lxvi(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(66, buffer);
    TEST_ASSERT_EQUAL_STRING("LXVI", buffer);
}

void test_93_is_xciii(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(93, buffer);
    TEST_ASSERT_EQUAL_STRING("XCIII", buffer);
}

void test_141_is_cxli(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(141, buffer);
    TEST_ASSERT_EQUAL_STRING("CXLI", buffer);
}

void test_163_is_clxiii(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(163, buffer);
    TEST_ASSERT_EQUAL_STRING("CLXIII", buffer);
}

void test_166_is_clxvi(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(166, buffer);
    TEST_ASSERT_EQUAL_STRING("CLXVI", buffer);
}

void test_402_is_cdii(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(402, buffer);
    TEST_ASSERT_EQUAL_STRING("CDII", buffer);
}

void test_575_is_dlxxv(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(575, buffer);
    TEST_ASSERT_EQUAL_STRING("DLXXV", buffer);
}

void test_666_is_dclxvi(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(666, buffer);
    TEST_ASSERT_EQUAL_STRING("DCLXVI", buffer);
}

void test_911_is_cmxi(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(911, buffer);
    TEST_ASSERT_EQUAL_STRING("CMXI", buffer);
}

void test_1024_is_mxxiv(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(1024, buffer);
    TEST_ASSERT_EQUAL_STRING("MXXIV", buffer);
}

void test_1666_is_mdclxvi(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(1666, buffer);
    TEST_ASSERT_EQUAL_STRING("MDCLXVI", buffer);
}

void test_3000_is_mmm(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(3000, buffer);
    TEST_ASSERT_EQUAL_STRING("MMM", buffer);
}

void test_3001_is_mmmi(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(3001, buffer);
    TEST_ASSERT_EQUAL_STRING("MMMI", buffer);
}

void test_3888_is_mmmdccclxxxviii(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(3888, buffer);
    TEST_ASSERT_EQUAL_STRING("MMMDCCCLXXXVIII", buffer);
}

void test_3999_is_mmmcmxcix(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    roman(3999, buffer);
    TEST_ASSERT_EQUAL_STRING("MMMCMXCIX", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_1_is_i);
    RUN_TEST(test_2_is_ii);
    RUN_TEST(test_3_is_iii);
    RUN_TEST(test_4_is_iv);
    RUN_TEST(test_5_is_v);
    RUN_TEST(test_6_is_vi);
    RUN_TEST(test_9_is_ix);
    RUN_TEST(test_16_is_xvi);
    RUN_TEST(test_27_is_xxvii);
    RUN_TEST(test_48_is_xlviii);
    RUN_TEST(test_49_is_xlix);
    RUN_TEST(test_59_is_lix);
    RUN_TEST(test_66_is_lxvi);
    RUN_TEST(test_93_is_xciii);
    RUN_TEST(test_141_is_cxli);
    RUN_TEST(test_163_is_clxiii);
    RUN_TEST(test_166_is_clxvi);
    RUN_TEST(test_402_is_cdii);
    RUN_TEST(test_575_is_dlxxv);
    RUN_TEST(test_666_is_dclxvi);
    RUN_TEST(test_911_is_cmxi);
    RUN_TEST(test_1024_is_mxxiv);
    RUN_TEST(test_1666_is_mdclxvi);
    RUN_TEST(test_3000_is_mmm);
    RUN_TEST(test_3001_is_mmmi);
    RUN_TEST(test_3888_is_mmmdccclxxxviii);
    RUN_TEST(test_3999_is_mmmcmxcix);
    return UNITY_END();
}
