#include "vendor/unity.h"

#define BUFFER_SIZE 100
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern void ciphertext(char buffer[], const char *plaintext);

void setUp(void) {
}

void tearDown(void) {
}

void test_empty_plaintext_results_in_an_empty_ciphertext(void) {
    char buffer[BUFFER_SIZE];

    ciphertext(buffer, "");

    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_normalization_results_in_empty_plaintext(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];

    ciphertext(buffer, "... --- ...");

    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_lowercase(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];

    ciphertext(buffer, "A");

    TEST_ASSERT_EQUAL_STRING("a", buffer);
}

void test_remove_spaces(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];

    ciphertext(buffer, "  b ");

    TEST_ASSERT_EQUAL_STRING("b", buffer);
}

void test_remove_punctuation(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];

    ciphertext(buffer, "@1,%!");

    TEST_ASSERT_EQUAL_STRING("1", buffer);
}

void test_9_character_plaintext_results_in_3_chunks_of_3_characters(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];

    ciphertext(buffer, "This is fun!");

    TEST_ASSERT_EQUAL_STRING("tsf hiu isn", buffer);
}

void test_8_character_plaintext_results_in_3_chunks_the_last_one_with_a_trailing_space(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];

    ciphertext(buffer, "Chill out.");

    TEST_ASSERT_EQUAL_STRING("clu hlt io ", buffer);
}

void test_54_character_plaintext_results_in_8_chunks_the_last_two_with_trailing_spaces(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];

    ciphertext(buffer, "If man was meant to stay on the ground, god would have given us roots.");

    TEST_ASSERT_EQUAL_STRING("imtgdvs fearwer mayoogo anouuio ntnnlvt wttddes aohghn  sseoau ", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_empty_plaintext_results_in_an_empty_ciphertext);
    RUN_TEST(test_normalization_results_in_empty_plaintext);
    RUN_TEST(test_lowercase);
    RUN_TEST(test_remove_spaces);
    RUN_TEST(test_remove_punctuation);
    RUN_TEST(test_9_character_plaintext_results_in_3_chunks_of_3_characters);
    RUN_TEST(test_8_character_plaintext_results_in_3_chunks_the_last_one_with_a_trailing_space);
    RUN_TEST(test_54_character_plaintext_results_in_8_chunks_the_last_two_with_trailing_spaces);
    return UNITY_END();
}
