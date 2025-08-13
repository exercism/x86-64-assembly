#include "vendor/unity.h"

#define BUFFER_SIZE 40

extern void truncate(char *buffer, const char *phrase);

void setUp(void) {
}

void tearDown(void) {
}

void test_english_language_short(void) {
    char buffer[BUFFER_SIZE];

    truncate(buffer, "Hi");
    TEST_ASSERT_EQUAL_STRING("Hi", buffer);
}

void test_english_language_long(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    truncate(buffer, "Hello there");
    TEST_ASSERT_EQUAL_STRING("Hello", buffer);
}

void test_german_language_short_broth(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    truncate(buffer, "brühe");
    TEST_ASSERT_EQUAL_STRING("brühe", buffer);
}

void test_german_language_long_bear_carpet__beards(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    truncate(buffer, "Bärteppich");
    TEST_ASSERT_EQUAL_STRING("Bärte", buffer);
}

void test_bulgarian_language_short_good(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    truncate(buffer, "Добър");
    TEST_ASSERT_EQUAL_STRING("Добър", buffer);
}

void test_greek_language_short_health(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    truncate(buffer, "υγειά");
    TEST_ASSERT_EQUAL_STRING("υγειά", buffer);
}

void test_maths_short(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    truncate(buffer, "a=πr²");
    TEST_ASSERT_EQUAL_STRING("a=πr²", buffer);
}

void test_maths_long(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    truncate(buffer, "∅⊊ℕ⊊ℤ⊊ℚ⊊ℝ⊊ℂ");
    TEST_ASSERT_EQUAL_STRING("∅⊊ℕ⊊ℤ", buffer);
}

void test_english_and_emoji_short(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    truncate(buffer, "Fly 🛫");
    TEST_ASSERT_EQUAL_STRING("Fly 🛫", buffer);
}

void test_emoji_short(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    truncate(buffer, "💇");
    TEST_ASSERT_EQUAL_STRING("💇", buffer);
}

void test_emoji_long(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    truncate(buffer, "❄🌡🤧🤒🏥🕰😀");
    TEST_ASSERT_EQUAL_STRING("❄🌡🤧🤒🏥", buffer);
}

void test_royal_flush(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    truncate(buffer, "🃎🂸🃅🃋🃍🃁🃊");
    TEST_ASSERT_EQUAL_STRING("🃎🂸🃅🃋🃍", buffer);
}

void test_ideograms(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    truncate(buffer, "二兎を追う者は一兎をも得ず");
    TEST_ASSERT_EQUAL_STRING("二兎を追う", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_english_language_short);
    RUN_TEST(test_english_language_long);
    RUN_TEST(test_german_language_short_broth);
    RUN_TEST(test_german_language_long_bear_carpet__beards);
    RUN_TEST(test_bulgarian_language_short_good);
    RUN_TEST(test_greek_language_short_health);
    RUN_TEST(test_maths_short);
    RUN_TEST(test_maths_long);
    RUN_TEST(test_english_and_emoji_short);
    RUN_TEST(test_emoji_short);
    RUN_TEST(test_emoji_long);
    RUN_TEST(test_royal_flush);
    RUN_TEST(test_ideograms);
    return UNITY_END();
}
