
// Version: 1.0.0

#include "vendor/unity.h"

extern const char **proteins(const char *rna);

void perform_test(const char *rna_strand, const char **expected, int expected_size) {
    const char **names = proteins(rna_strand);
    int size;
    for (size = 0; names[size]; size++) {}

    TEST_ASSERT_EQUAL_INT(expected_size, size);
    if (expected_size > 0) {
        TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
    }
}

void setUp(void) {
}

void tearDown(void) {
}

void test_empty_sequence(void) {
    perform_test("", NULL, 0);
}

void test_methionine(void) {
    TEST_IGNORE();
    perform_test("AUG", (const char *[]){"Methionine"}, 1);
}

void test_phenylalanine(void) {
    TEST_IGNORE();
    perform_test("UUU", (const char *[]){"Phenylalanine"}, 1);
}

void test_phenylalanine_2(void) {
    TEST_IGNORE();
    perform_test("UUC", (const char *[]){"Phenylalanine"}, 1);
}

void test_leucine(void) {
    TEST_IGNORE();
    perform_test("UUA", (const char *[]){"Leucine"}, 1);
}

void test_leucine_2(void) {
    TEST_IGNORE();
    perform_test("UUG", (const char *[]){"Leucine"}, 1);
}

void test_serine(void) {
    TEST_IGNORE();
    perform_test("UCU", (const char *[]){"Serine"}, 1);
}

void test_serine_2(void) {
    TEST_IGNORE();
    perform_test("UCC", (const char *[]){"Serine"}, 1);
}

void test_serine_3(void) {
    TEST_IGNORE();
    perform_test("UCA", (const char *[]){"Serine"}, 1);
}

void test_serine_4(void) {
    TEST_IGNORE();
    perform_test("UCG", (const char *[]){"Serine"}, 1);
}

void test_tyrosine(void) {
    TEST_IGNORE();
    perform_test("UAU", (const char *[]){"Tyrosine"}, 1);
}

void test_tyrosine_2(void) {
    TEST_IGNORE();
    perform_test("UAC", (const char *[]){"Tyrosine"}, 1);
}

void test_cysteine(void) {
    TEST_IGNORE();
    perform_test("UGU", (const char *[]){"Cysteine"}, 1);
}

void test_cysteine_2(void) {
    TEST_IGNORE();
   perform_test("UGC", (const char *[]){"Cysteine"}, 1);
}

void test_tryptophan(void) {
    TEST_IGNORE();
    perform_test("UGG", (const char *[]){"Tryptophan"}, 1);
}

void test_stop_codon(void) {
    TEST_IGNORE();
    perform_test("UAA", NULL, 0);
}

void test_stop_codon_2(void) {
    TEST_IGNORE();
    perform_test("UAG", NULL, 0);
}

void test_stop_codon_3(void) {
    TEST_IGNORE();
    perform_test("UGA", NULL, 0);
}

void test_two_identical_codons(void) {
    TEST_IGNORE();
    perform_test("UUUUUU", (const char *[]){"Phenylalanine", "Phenylalanine"}, 2);
}

void test_two_different_codons(void) {
    TEST_IGNORE();
    perform_test("UUAUUG", (const char *[]){"Leucine", "Leucine"}, 2);
}

void test_three_codons(void) {
    TEST_IGNORE();
    perform_test("AUGUUUUGG", (const char *[]){"Methionine", "Phenylalanine", "Tryptophan"}, 3);
}

void test_stop_after_0_of_2(void) {
    TEST_IGNORE();
    perform_test("UAGUGG", NULL, 0);
}

void test_stop_after_1_of_2(void) {
    TEST_IGNORE();
    perform_test("UGGUAG", (const char *[]){"Tryptophan"}, 1);
}

void test_stop_after_2_of_3(void) {
    TEST_IGNORE();
    perform_test("AUGUUUUAA", (const char *[]){"Methionine", "Phenylalanine"}, 2);
}

void test_stop_after_1_of_3(void) {
    TEST_IGNORE();
    perform_test("UGGUAGUGG", (const char *[]){"Tryptophan"}, 1);
}

void test_stop_after_3_of_6(void) {
    TEST_IGNORE();
    perform_test("UGGUGUUAUUAAUGGUUU", (const char *[]){"Tryptophan", "Cysteine", "Tyrosine"}, 3);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_empty_sequence);
    RUN_TEST(test_empty_sequence);
    RUN_TEST(test_methionine);
    RUN_TEST(test_phenylalanine);
    RUN_TEST(test_phenylalanine_2);
    RUN_TEST(test_leucine);
    RUN_TEST(test_leucine_2);
    RUN_TEST(test_serine);
    RUN_TEST(test_serine_2);
    RUN_TEST(test_serine_3);
    RUN_TEST(test_serine_4);
    RUN_TEST(test_tyrosine);
    RUN_TEST(test_tyrosine_2);
    RUN_TEST(test_cysteine);
    RUN_TEST(test_cysteine_2);
    RUN_TEST(test_tryptophan);
    RUN_TEST(test_stop_codon);
    RUN_TEST(test_stop_codon_2);
    RUN_TEST(test_stop_codon_3);
    RUN_TEST(test_two_identical_codons);
    RUN_TEST(test_two_different_codons);
    RUN_TEST(test_three_codons);
    RUN_TEST(test_stop_after_0_of_2);
    RUN_TEST(test_stop_after_1_of_2);
    RUN_TEST(test_stop_after_2_of_3);
    RUN_TEST(test_stop_after_1_of_3);
    RUN_TEST(test_stop_after_3_of_6);
    return UNITY_END();
}
