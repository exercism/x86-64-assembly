#include "vendor/unity.h"

#include <stddef.h>

extern void find_anagrams(int *is_anagram, const char *candidates[], size_t num_candidates, const char *subject);

void setUp(void) {
}

void tearDown(void) {
}

void test_no_matches(void) {
    const char *candidates[] = {"hello", "world", "zombies", "pants"};
    const int expected[4] = {0, 0, 0, 0};
    int is_anagram[4] = {0};

    find_anagrams(is_anagram, candidates, 4, "diaper");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 4);
}

void test_detects_two_anagrams(void) {
    TEST_IGNORE();
    const char *candidates[] = {"lemons", "cherry", "melons"};
    const int expected[3] = {1, 0, 1};
    int is_anagram[3] = {0};

    find_anagrams(is_anagram, candidates, 3, "solemn");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 3);
}

void test_does_not_detect_anagram_subsets(void) {
    TEST_IGNORE();
    const char *candidates[] = {"dog", "goody"};
    const int expected[2] = {0, 0};
    int is_anagram[2] = {0};

    find_anagrams(is_anagram, candidates, 2, "good");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 2);
}

void test_detects_anagram(void) {
    TEST_IGNORE();
    const char *candidates[] = {"enlists", "google", "inlets", "banana"};
    const int expected[4] = {0, 0, 1, 0};
    int is_anagram[4] = {0};

    find_anagrams(is_anagram, candidates, 4, "listen");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 4);
}

void test_detects_three_anagrams(void) {
    TEST_IGNORE();
    const char *candidates[] = {"gallery", "ballerina", "regally", "clergy", "largely", "leading"};
    const int expected[6] = {1, 0, 1, 0, 1, 0};
    int is_anagram[6] = {0};

    find_anagrams(is_anagram, candidates, 6, "allergy");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 6);
}

void test_detects_multiple_anagrams_with_different_case(void) {
    TEST_IGNORE();
    const char *candidates[] = {"Eons", "ONES"};
    const int expected[2] = {1, 1};
    int is_anagram[2] = {0};

    find_anagrams(is_anagram, candidates, 2, "nose");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 2);
}

void test_does_not_detect_nonanagrams_with_identical_checksum(void) {
    TEST_IGNORE();
    const char *candidates[] = {"last"};
    const int expected[1] = {0};
    int is_anagram[1] = {0};

    find_anagrams(is_anagram, candidates, 1, "mass");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 1);
}

void test_detects_anagrams_caseinsensitively(void) {
    TEST_IGNORE();
    const char *candidates[] = {"cashregister", "Carthorse", "radishes"};
    const int expected[3] = {0, 1, 0};
    int is_anagram[3] = {0};

    find_anagrams(is_anagram, candidates, 3, "Orchestra");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 3);
}

void test_detects_anagrams_using_caseinsensitive_subject(void) {
    TEST_IGNORE();
    const char *candidates[] = {"cashregister", "carthorse", "radishes"};
    const int expected[3] = {0, 1, 0};
    int is_anagram[3] = {0};

    find_anagrams(is_anagram, candidates, 3, "Orchestra");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 3);
}

void test_detects_anagrams_using_caseinsensitive_possible_matches(void) {
    TEST_IGNORE();
    const char *candidates[] = {"cashregister", "Carthorse", "radishes"};
    const int expected[3] = {0, 1, 0};
    int is_anagram[3] = {0};

    find_anagrams(is_anagram, candidates, 3, "orchestra");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 3);
}

void test_does_not_detect_an_anagram_if_the_original_word_is_repeated(void) {
    TEST_IGNORE();
    const char *candidates[] = {"goGoGO"};
    const int expected[1] = {0};
    int is_anagram[1] = {0};

    find_anagrams(is_anagram, candidates, 1, "go");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 1);
}

void test_anagrams_must_use_all_letters_exactly_once(void) {
    TEST_IGNORE();
    const char *candidates[] = {"patter"};
    const int expected[1] = {0};
    int is_anagram[1] = {0};

    find_anagrams(is_anagram, candidates, 1, "tapper");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 1);
}

void test_words_are_not_anagrams_of_themselves_even_if_letter_case_is_completely_different(void) {
    TEST_IGNORE();
    const char *candidates[] = {"banana"};
    const int expected[1] = {0};
    int is_anagram[1] = {0};

    find_anagrams(is_anagram, candidates, 1, "BANANA");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 1);
}

void test_words_other_than_themselves_can_be_anagrams(void) {
    TEST_IGNORE();
    const char *candidates[] = {"LISTEN", "Silent"};
    const int expected[2] = {0, 1};
    int is_anagram[2] = {0};

    find_anagrams(is_anagram, candidates, 2, "LISTEN");

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, is_anagram, 2);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_no_matches);
    RUN_TEST(test_detects_two_anagrams);
    RUN_TEST(test_does_not_detect_anagram_subsets);
    RUN_TEST(test_detects_anagram);
    RUN_TEST(test_detects_three_anagrams);
    RUN_TEST(test_detects_multiple_anagrams_with_different_case);
    RUN_TEST(test_does_not_detect_nonanagrams_with_identical_checksum);
    RUN_TEST(test_detects_anagrams_caseinsensitively);
    RUN_TEST(test_detects_anagrams_using_caseinsensitive_subject);
    RUN_TEST(test_detects_anagrams_using_caseinsensitive_possible_matches);
    RUN_TEST(test_does_not_detect_an_anagram_if_the_original_word_is_repeated);
    RUN_TEST(test_anagrams_must_use_all_letters_exactly_once);
    RUN_TEST(test_words_are_not_anagrams_of_themselves_even_if_letter_case_is_completely_different);
    RUN_TEST(test_words_other_than_themselves_can_be_anagrams);
    return UNITY_END();
}
