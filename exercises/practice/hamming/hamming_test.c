#include "vendor/unity.h"

#define BUFFER_SIZE 16

extern int distance(const char strand1[], const char strand2[]);

void setUp(void) {
}

void tearDown(void) {
}

void test_empty_strands(void) {
    const char strand1[BUFFER_SIZE] = "";
    const char strand2[BUFFER_SIZE] = "";
    TEST_ASSERT_EQUAL_INT(0, distance(strand1, strand2));
}

void test_single_letter_identical_strands(void) {
    TEST_IGNORE();
    const char strand1[BUFFER_SIZE] = "A";
    const char strand2[BUFFER_SIZE] = "A";
    TEST_ASSERT_EQUAL_INT(0, distance(strand1, strand2));
}

void test_single_letter_different_strands(void) {
    TEST_IGNORE();
    const char strand1[BUFFER_SIZE] = "G";
    const char strand2[BUFFER_SIZE] = "T";
    TEST_ASSERT_EQUAL_INT(1, distance(strand1, strand2));
}

void test_long_identical_strands(void) {
    TEST_IGNORE();
    const char strand1[BUFFER_SIZE] = "GGACTGAAATCTG";
    const char strand2[BUFFER_SIZE] = "GGACTGAAATCTG";
    TEST_ASSERT_EQUAL_INT(0, distance(strand1, strand2));
}

void test_long_different_strands(void) {
    TEST_IGNORE();
    const char strand1[BUFFER_SIZE] = "GGACGGATTCTG";
    const char strand2[BUFFER_SIZE] = "AGGACGGATTCT";
    TEST_ASSERT_EQUAL_INT(9, distance(strand1, strand2));
}

void test_disallow_first_strand_longer(void) {
    TEST_IGNORE();
    const char strand1[BUFFER_SIZE] = "AATG";
    const char strand2[BUFFER_SIZE] = "AAA";
    TEST_ASSERT_EQUAL_INT(-1, distance(strand1, strand2));
}

void test_disallow_second_strand_longer(void) {
    TEST_IGNORE();
    const char strand1[BUFFER_SIZE] = "ATA";
    const char strand2[BUFFER_SIZE] = "AGTG";
    TEST_ASSERT_EQUAL_INT(-1, distance(strand1, strand2));
}

void test_disallow_left_empty_strand(void) {
    TEST_IGNORE();
    const char strand1[BUFFER_SIZE] = "";
    const char strand2[BUFFER_SIZE] = "G";
    TEST_ASSERT_EQUAL_INT(-1, distance(strand1, strand2));
}

void test_disallow_empty_first_strand(void) {
    TEST_IGNORE();
    const char strand1[BUFFER_SIZE] = "";
    const char strand2[BUFFER_SIZE] = "G";
    TEST_ASSERT_EQUAL_INT(-1, distance(strand1, strand2));
}

void test_disallow_right_empty_strand(void) {
    TEST_IGNORE();
    const char strand1[BUFFER_SIZE] = "G";
    const char strand2[BUFFER_SIZE] = "";
    TEST_ASSERT_EQUAL_INT(-1, distance(strand1, strand2));
}

void test_disallow_empty_second_strand(void) {
    TEST_IGNORE();
    const char strand1[BUFFER_SIZE] = "G";
    const char strand2[BUFFER_SIZE] = "";
    TEST_ASSERT_EQUAL_INT(-1, distance(strand1, strand2));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_empty_strands);
    RUN_TEST(test_single_letter_identical_strands);
    RUN_TEST(test_single_letter_different_strands);
    RUN_TEST(test_long_identical_strands);
    RUN_TEST(test_long_different_strands);
    RUN_TEST(test_disallow_first_strand_longer);
    RUN_TEST(test_disallow_second_strand_longer);
    RUN_TEST(test_disallow_left_empty_strand);
    RUN_TEST(test_disallow_empty_first_strand);
    RUN_TEST(test_disallow_right_empty_strand);
    RUN_TEST(test_disallow_empty_second_strand);
    return UNITY_END();
}
