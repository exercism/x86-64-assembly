// Version: 1.0.0

#include "vendor/unity.h"

enum nucleotide {
    ADENINE,
    CYTOSINE,
    GUANINE,
    THYMINE
};

extern void nucleotide_counts(const char* strand, int64_t* counts);

void setUp(void) {
}

void tearDown(void) {
}

void test_empty_strand(void) {
    int64_t counts[4];

    nucleotide_counts("", counts);
    TEST_ASSERT_EQUAL_INT(0, counts[ADENINE]);
    TEST_ASSERT_EQUAL_INT(0, counts[CYTOSINE]);
    TEST_ASSERT_EQUAL_INT(0, counts[GUANINE]);
    TEST_ASSERT_EQUAL_INT(0, counts[THYMINE]);
}

void test_can_count_one_nucleotide_in_single_character_input(void) {
    TEST_IGNORE();
    int64_t counts[4];

    nucleotide_counts("G", counts);
    TEST_ASSERT_EQUAL_INT(0, counts[ADENINE]);
    TEST_ASSERT_EQUAL_INT(0, counts[CYTOSINE]);
    TEST_ASSERT_EQUAL_INT(1, counts[GUANINE]);
    TEST_ASSERT_EQUAL_INT(0, counts[THYMINE]);
}

void test_strand_with_repeated_nucleotide(void) {
    TEST_IGNORE();
    int64_t counts[4];

    nucleotide_counts("GGGGGGG", counts);
    TEST_ASSERT_EQUAL_INT(0, counts[ADENINE]);
    TEST_ASSERT_EQUAL_INT(0, counts[CYTOSINE]);
    TEST_ASSERT_EQUAL_INT(7, counts[GUANINE]);
    TEST_ASSERT_EQUAL_INT(0, counts[THYMINE]);
}

void test_strand_with_multiple_nucleotides(void) {
    TEST_IGNORE();
    int64_t counts[4];

    nucleotide_counts("AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC", counts);
    TEST_ASSERT_EQUAL_INT(20, counts[ADENINE]);
    TEST_ASSERT_EQUAL_INT(12, counts[CYTOSINE]);
    TEST_ASSERT_EQUAL_INT(17, counts[GUANINE]);
    TEST_ASSERT_EQUAL_INT(21, counts[THYMINE]);
}

void test_strand_with_invalid_nucleotides(void) {
    TEST_IGNORE();
    int64_t counts[4];

    nucleotide_counts("AGXXACT", counts);
    TEST_ASSERT_EQUAL_INT(-1, counts[ADENINE]);
    TEST_ASSERT_EQUAL_INT(-1, counts[CYTOSINE]);
    TEST_ASSERT_EQUAL_INT(-1, counts[GUANINE]);
    TEST_ASSERT_EQUAL_INT(-1, counts[THYMINE]);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_empty_strand);
    RUN_TEST(test_can_count_one_nucleotide_in_single_character_input);
    RUN_TEST(test_strand_with_repeated_nucleotide);
    RUN_TEST(test_strand_with_multiple_nucleotides);
    RUN_TEST(test_strand_with_invalid_nucleotides);
    return UNITY_END();
}
