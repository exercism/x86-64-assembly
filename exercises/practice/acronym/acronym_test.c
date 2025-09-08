#include <string.h>

#include "vendor/unity.h"

#define BUFFER_SIZE 0x100

extern void abbreviate(const char *in, char *out);

void setUp(void) {
}

void tearDown(void) {
}

void test_basic(void) {
    const char *in = "Portable Network Graphics";
    char out[BUFFER_SIZE];
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("PNG", out);
}

void test_lowercase_words(void) {
    TEST_IGNORE();
    const char *in = "Ruby on Rails";
    char out[BUFFER_SIZE];
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("ROR", out);
}

void test_punctuation(void) {
    TEST_IGNORE();
    const char *in = "First In, First Out";
    char out[BUFFER_SIZE];
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("FIFO", out);
}

void test_all_caps_word(void) {
    TEST_IGNORE();
    const char *in = "GNU Image Manipulation Program";
    char out[BUFFER_SIZE];
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("GIMP", out);
}

void test_punctuation_without_whitespace(void) {
    TEST_IGNORE();
    const char *in = "Complementary metal-oxide semiconductor";
    char out[BUFFER_SIZE];
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("CMOS", out);
}

void test_very_long_abbreviation(void) {
    TEST_IGNORE();
    const char *in = "Rolling On The Floor Laughing So Hard That My Dogs Came Over And Licked Me";
    char out[BUFFER_SIZE];
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("ROTFLSHTMDCOALM", out);
}

void test_consecutive_delimiters(void) {
    TEST_IGNORE();
    const char *in = "Something - I made up from thin air";
    char out[BUFFER_SIZE];
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("SIMUFTA", out);
}

void test_apostrophes(void) {
    TEST_IGNORE();
    const char *in = "Halley's Comet";
    char out[BUFFER_SIZE];
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("HC", out);
}

void test_underscore_emphasis(void) {
    TEST_IGNORE();
    const char *in = "The Road _Not_ Taken";
    char out[BUFFER_SIZE];
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("TRNT", out);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_basic);
    RUN_TEST(test_lowercase_words);
    RUN_TEST(test_punctuation);
    RUN_TEST(test_all_caps_word);
    RUN_TEST(test_punctuation_without_whitespace);
    RUN_TEST(test_very_long_abbreviation);
    RUN_TEST(test_consecutive_delimiters);
    RUN_TEST(test_apostrophes);
    RUN_TEST(test_underscore_emphasis);
    return UNITY_END();
}
