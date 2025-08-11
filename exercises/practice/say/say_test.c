#include "vendor/unity.h"

#include <stdint.h>

#define BUFFER_SIZE 240

extern void say(char *buffer, int64_t number);

void setUp(void) {
}

void tearDown(void) {
}

void test_zero(void) {
    char buffer[BUFFER_SIZE];
    say(buffer, 0);
    TEST_ASSERT_EQUAL_STRING("zero", buffer);
}

void test_one(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 1);
    TEST_ASSERT_EQUAL_STRING("one", buffer);
}

void test_fourteen(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 14);
    TEST_ASSERT_EQUAL_STRING("fourteen", buffer);
}

void test_twenty(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 20);
    TEST_ASSERT_EQUAL_STRING("twenty", buffer);
}

void test_twentytwo(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 22);
    TEST_ASSERT_EQUAL_STRING("twenty-two", buffer);
}

void test_thirty(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 30);
    TEST_ASSERT_EQUAL_STRING("thirty", buffer);
}

void test_ninetynine(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 99);
    TEST_ASSERT_EQUAL_STRING("ninety-nine", buffer);
}

void test_one_hundred(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 100);
    TEST_ASSERT_EQUAL_STRING("one hundred", buffer);
}

void test_one_hundred_twentythree(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 123);
    TEST_ASSERT_EQUAL_STRING("one hundred twenty-three", buffer);
}

void test_two_hundred(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 200);
    TEST_ASSERT_EQUAL_STRING("two hundred", buffer);
}

void test_nine_hundred_ninetynine(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 999);
    TEST_ASSERT_EQUAL_STRING("nine hundred ninety-nine", buffer);
}

void test_one_thousand(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 1000);
    TEST_ASSERT_EQUAL_STRING("one thousand", buffer);
}

void test_one_thousand_two_hundred_thirtyfour(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 1234);
    TEST_ASSERT_EQUAL_STRING("one thousand two hundred thirty-four", buffer);
}

void test_one_million(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 1000000);
    TEST_ASSERT_EQUAL_STRING("one million", buffer);
}

void test_one_million_two_thousand_three_hundred_fortyfive(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 1002345);
    TEST_ASSERT_EQUAL_STRING("one million two thousand three hundred forty-five", buffer);
}

void test_one_billion(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 1000000000);
    TEST_ASSERT_EQUAL_STRING("one billion", buffer);
}

void test_a_big_number(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 987654321123);
    TEST_ASSERT_EQUAL_STRING(
        "nine hundred eighty-seven billion six hundred fifty-four million three hundred twenty-one thousand one hundred twenty-three",
        buffer);
}

void test_numbers_below_zero_are_out_of_range(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, -1);
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_numbers_above_999999999999_are_out_of_range(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 1000000000000);
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_additional_big_number(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 19011016013);
    TEST_ASSERT_EQUAL_STRING("nineteen billion eleven million sixteen thousand thirteen", buffer);
}

void test_different_big_number(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 812000070017);
    TEST_ASSERT_EQUAL_STRING("eight hundred twelve billion seventy thousand seventeen", buffer);
}

void test_alternative_big_number(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    say(buffer, 60010015018);
    TEST_ASSERT_EQUAL_STRING("sixty billion ten million fifteen thousand eighteen", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_zero);
    RUN_TEST(test_one);
    RUN_TEST(test_fourteen);
    RUN_TEST(test_twenty);
    RUN_TEST(test_twentytwo);
    RUN_TEST(test_thirty);
    RUN_TEST(test_ninetynine);
    RUN_TEST(test_one_hundred);
    RUN_TEST(test_one_hundred_twentythree);
    RUN_TEST(test_two_hundred);
    RUN_TEST(test_nine_hundred_ninetynine);
    RUN_TEST(test_one_thousand);
    RUN_TEST(test_one_thousand_two_hundred_thirtyfour);
    RUN_TEST(test_one_million);
    RUN_TEST(test_one_million_two_thousand_three_hundred_fortyfive);
    RUN_TEST(test_one_billion);
    RUN_TEST(test_a_big_number);
    RUN_TEST(test_numbers_below_zero_are_out_of_range);
    RUN_TEST(test_numbers_above_999999999999_are_out_of_range);
    RUN_TEST(test_additional_big_number);
    RUN_TEST(test_different_big_number);
    RUN_TEST(test_alternative_big_number);
    return UNITY_END();
}
