// Version: 0

#include <string.h> 

#include "vendor/unity.h"

#define BUFFER_SIZE 0x100
char out[BUFFER_SIZE];

extern void abbreviate(const char* in, char* out);

void tearDown(void) {
    memset(out, 0, BUFFER_SIZE*sizeof(char)); 
}

void setUp(void) {
}

void test_basic(void) {
    const char *in = "Portable Network Graphics";
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("PNG", out);
}

void test_lowercase_words(void) {
    TEST_IGNORE();
    const char *in = "Ruby on Rails";
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("ROR", out);
}

void test_punctuation(void) {
    TEST_IGNORE();
    const char *in = "First In, First Out";
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("FIFO", out);
}

void test_all_caps_word(void) {
    TEST_IGNORE();
    const char *in = "GNU Image Manipulation Program";
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("GIMP", out);
}

void test_punctuation_without_whitespace(void) {
    TEST_IGNORE();
    const char *in = "Complementary metal-oxide semiconductor";
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("CMOS", out);
}

void test_very_long_abbreviation(void) {
    TEST_IGNORE();
    const char *in = "Rolling On The Floor Laughing So Hard That My Dogs Came Over And Licked Me";
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("ROTFLSHTMDCOALM", out);
}

void test_consecutive_delimiters(void) {
    TEST_IGNORE();
    const char *in = "Something - I made up from thin air";
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("SIMUFTA", out);
}

void test_apostrophes(void) {
    TEST_IGNORE();
    const char *in = "Halley's Comet";
    abbreviate(in, out);
    TEST_ASSERT_EQUAL_STRING("HC", out);
}

void test_underscore_emphasis(void) {
    TEST_IGNORE();
    const char *in = "The Road _Not_ Taken";
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
