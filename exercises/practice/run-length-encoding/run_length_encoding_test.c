// Version: 1.0.0

#include "vendor/unity.h"

#define BUFFER_SIZE 256

extern void encode(char *buffer, const char *string);
extern void decode(char *buffer, const char *string);

void setUp(void) {
}

void tearDown(void) {
}

void test_encode_empty_string(void) {
    char buffer[BUFFER_SIZE];

    encode(buffer, "");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_encode_single_characters_only_are_encoded_without_count(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "XYZ");
    TEST_ASSERT_EQUAL_STRING("XYZ", buffer);
}

void test_encode_string_with_no_single_characters(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "AABBBCCCC");
    TEST_ASSERT_EQUAL_STRING("2A3B4C", buffer);
}

void test_encode_single_characters_mixed_with_repeated_characters(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWB");
    TEST_ASSERT_EQUAL_STRING("12WB12W3B24WB", buffer);
}

void test_encode_multiple_whitespace_mixed_in_string(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "  hsqq qww  ");
    TEST_ASSERT_EQUAL_STRING("2 hs2q q2w2 ", buffer);
}

void test_encode_lowercase_characters(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer, "aabbbcccc");
    TEST_ASSERT_EQUAL_STRING("2a3b4c", buffer);
}

void test_encode_long_run(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    encode(buffer,
           "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
           ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
    TEST_ASSERT_EQUAL_STRING("123:", buffer);
}

void test_decode_empty_string(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_decode_single_characters_only(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "XYZ");
    TEST_ASSERT_EQUAL_STRING("XYZ", buffer);
}

void test_decode_string_with_no_single_characters(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "2A3B4C");
    TEST_ASSERT_EQUAL_STRING("AABBBCCCC", buffer);
}

void test_decode_single_characters_with_repeated_characters(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "12WB12W3B24WB");
    TEST_ASSERT_EQUAL_STRING("WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWB", buffer);
}

void test_decode_multiple_whitespace_mixed_in_string(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "2 hs2q q2w2 ");
    TEST_ASSERT_EQUAL_STRING("  hsqq qww  ", buffer);
}

void test_decode_lowercase_string(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    decode(buffer, "2a3b4c");
    TEST_ASSERT_EQUAL_STRING("aabbbcccc", buffer);
}

void test_consistency_encode_followed_by_decode_gives_original_string(void) {
    TEST_IGNORE();
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];

    encode(buffer1, "zzz ZZ  zZ");
    decode(buffer2, buffer1);
    TEST_ASSERT_EQUAL_STRING("zzz ZZ  zZ", buffer2);
}

void test_consistency_with_punctuation(void) {
    TEST_IGNORE();
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];

    encode(buffer1, "\t\t///::::\xB0@@@[[```{{{{");
    decode(buffer2, buffer1);
    TEST_ASSERT_EQUAL_STRING("\t\t///::::\xB0@@@[[```{{{{", buffer2);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_encode_empty_string);
    RUN_TEST(test_encode_single_characters_only_are_encoded_without_count);
    RUN_TEST(test_encode_string_with_no_single_characters);
    RUN_TEST(test_encode_single_characters_mixed_with_repeated_characters);
    RUN_TEST(test_encode_multiple_whitespace_mixed_in_string);
    RUN_TEST(test_encode_lowercase_characters);
    RUN_TEST(test_encode_long_run);
    RUN_TEST(test_decode_empty_string);
    RUN_TEST(test_decode_single_characters_only);
    RUN_TEST(test_decode_string_with_no_single_characters);
    RUN_TEST(test_decode_single_characters_with_repeated_characters);
    RUN_TEST(test_decode_multiple_whitespace_mixed_in_string);
    RUN_TEST(test_decode_lowercase_string);
    RUN_TEST(test_consistency_encode_followed_by_decode_gives_original_string);
    RUN_TEST(test_consistency_with_punctuation);
    return UnityEnd();
}
