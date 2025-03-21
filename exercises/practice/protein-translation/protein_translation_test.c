// Version: 0

#include "vendor/unity.h"

extern const char **proteins(const char *rna, const char **buffer);

void setUp(void) {
}

void tearDown(void) {
}

void test_empty_rna_sequence_results_in_no_proteins(void) {

    const char *buffer[10];
    const char **names = proteins("", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(0, size);
}

void test_methionine_rna_sequence(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("AUG", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Methionine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_phenylalanine_rna_sequence_1(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UUU", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Phenylalanine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_phenylalanine_rna_sequence_2(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UUC", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Phenylalanine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_leucine_rna_sequence_1(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UUA", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Leucine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_leucine_rna_sequence_2(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UUG", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Leucine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_serine_rna_sequence_1(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UCU", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Serine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_serine_rna_sequence_2(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UCC", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Serine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_serine_rna_sequence_3(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UCA", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Serine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_serine_rna_sequence_4(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UCG", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Serine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_tyrosine_rna_sequence_1(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UAU", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Tyrosine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_tyrosine_rna_sequence_2(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UAC", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Tyrosine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_cysteine_rna_sequence_1(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UGU", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Cysteine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_cysteine_rna_sequence_2(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UGC", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Cysteine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_tryptophan_rna_sequence(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UGG", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Tryptophan"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_stop_codon_rna_sequence_1(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UAA", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(0, size);
}

void test_stop_codon_rna_sequence_2(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UAG", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(0, size);
}

void test_stop_codon_rna_sequence_3(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UGA", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(0, size);
}

void test_sequence_of_two_protein_codons_translates_into_proteins(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UUUUUU", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(2, size);

    const char *expected[] = {"Phenylalanine", "Phenylalanine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_sequence_of_two_different_protein_codons_translates_into_proteins(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UUAUUG", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(2, size);

    const char *expected[] = {"Leucine", "Leucine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_translate_rna_strand_into_correct_protein_list(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("AUGUUUUGG", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(3, size);

    const char *expected[] = {"Methionine", "Phenylalanine", "Tryptophan"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_translation_stops_if_stop_codon_at_beginning_of_sequence(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UAGUGG", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(0, size);
}

void test_translation_stops_if_stop_codon_at_end_of_twocodon_sequence(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UGGUAG", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Tryptophan"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_translation_stops_if_stop_codon_at_end_of_threecodon_sequence(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("AUGUUUUAA", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(2, size);

    const char *expected[] = {"Methionine", "Phenylalanine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_translation_stops_if_stop_codon_in_middle_of_threecodon_sequence(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UGGUAGUGG", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(1, size);

    const char *expected[] = {"Tryptophan"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_translation_stops_if_stop_codon_in_middle_of_sixcodon_sequence(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UGGUGUUAUUAAUGGUUU", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(3, size);

    const char *expected[] = {"Tryptophan", "Cysteine", "Tyrosine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_sequence_of_two_nonstop_codons_does_not_translate_to_a_stop_codon(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("AUGAUG", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(2, size);

    const char *expected[] = {"Methionine", "Methionine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

void test_unknown_amino_acids_not_part_of_a_codon_cant_translate(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("XYZ", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(0, size);
}

void test_incomplete_rna_sequence_can_translate_if_valid_until_a_stop_codon(void) {
    TEST_IGNORE();

    const char *buffer[10];
    const char **names = proteins("UUCUUCUAAUGGU", buffer);

    int size;
    for (size = 0; names[size]; size++) {}
    TEST_ASSERT_EQUAL_INT(2, size);

    const char *expected[] = {"Phenylalanine", "Phenylalanine"};
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, names, size);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_empty_rna_sequence_results_in_no_proteins);
    RUN_TEST(test_methionine_rna_sequence);
    RUN_TEST(test_phenylalanine_rna_sequence_1);
    RUN_TEST(test_phenylalanine_rna_sequence_2);
    RUN_TEST(test_leucine_rna_sequence_1);
    RUN_TEST(test_leucine_rna_sequence_2);
    RUN_TEST(test_serine_rna_sequence_1);
    RUN_TEST(test_serine_rna_sequence_2);
    RUN_TEST(test_serine_rna_sequence_3);
    RUN_TEST(test_serine_rna_sequence_4);
    RUN_TEST(test_tyrosine_rna_sequence_1);
    RUN_TEST(test_tyrosine_rna_sequence_2);
    RUN_TEST(test_cysteine_rna_sequence_1);
    RUN_TEST(test_cysteine_rna_sequence_2);
    RUN_TEST(test_tryptophan_rna_sequence);
    RUN_TEST(test_stop_codon_rna_sequence_1);
    RUN_TEST(test_stop_codon_rna_sequence_2);
    RUN_TEST(test_stop_codon_rna_sequence_3);
    RUN_TEST(test_sequence_of_two_protein_codons_translates_into_proteins);
    RUN_TEST(test_sequence_of_two_different_protein_codons_translates_into_proteins);
    RUN_TEST(test_translate_rna_strand_into_correct_protein_list);
    RUN_TEST(test_translation_stops_if_stop_codon_at_beginning_of_sequence);
    RUN_TEST(test_translation_stops_if_stop_codon_at_end_of_twocodon_sequence);
    RUN_TEST(test_translation_stops_if_stop_codon_at_end_of_threecodon_sequence);
    RUN_TEST(test_translation_stops_if_stop_codon_in_middle_of_threecodon_sequence);
    RUN_TEST(test_translation_stops_if_stop_codon_in_middle_of_sixcodon_sequence);
    RUN_TEST(test_sequence_of_two_nonstop_codons_does_not_translate_to_a_stop_codon);
    RUN_TEST(test_unknown_amino_acids_not_part_of_a_codon_cant_translate);
    RUN_TEST(test_incomplete_rna_sequence_can_translate_if_valid_until_a_stop_codon);
    return UNITY_END();
}
