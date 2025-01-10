#include "vendor/unity.h"

#define BUFFER_SIZE 4000

extern void recite(char *buffer, int start_bottles, int take_down);

void setUp(void) {
}

void tearDown(void) {
}

void test_first_generic_verse(void) {
    char buffer[BUFFER_SIZE];

    recite(buffer, 10, 1);
    const char expected[] =
        "Ten green bottles hanging on the wall,\n"
        "Ten green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be nine green bottles hanging on the wall.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_last_generic_verse(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 3, 1);
    const char expected[] =
        "Three green bottles hanging on the wall,\n"
        "Three green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be two green bottles hanging on the wall.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_with_2_bottles(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 2, 1);
    const char expected[] =
        "Two green bottles hanging on the wall,\n"
        "Two green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be one green bottle hanging on the wall.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_with_1_bottle(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 1, 1);
    const char expected[] =
        "One green bottle hanging on the wall,\n"
        "One green bottle hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be no green bottles hanging on the wall.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_first_two_verses(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 10, 2);
    const char expected[] =
        "Ten green bottles hanging on the wall,\n"
        "Ten green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be nine green bottles hanging on the wall.\n"
        "\n"
        "Nine green bottles hanging on the wall,\n"
        "Nine green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be eight green bottles hanging on the wall.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_last_three_verses(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 3, 3);
    const char expected[] =
        "Three green bottles hanging on the wall,\n"
        "Three green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be two green bottles hanging on the wall.\n"
        "\n"
        "Two green bottles hanging on the wall,\n"
        "Two green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be one green bottle hanging on the wall.\n"
        "\n"
        "One green bottle hanging on the wall,\n"
        "One green bottle hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be no green bottles hanging on the wall.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_all_verses(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 10, 10);
    const char expected[] =
        "Ten green bottles hanging on the wall,\n"
        "Ten green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be nine green bottles hanging on the wall.\n"
        "\n"
        "Nine green bottles hanging on the wall,\n"
        "Nine green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be eight green bottles hanging on the wall.\n"
        "\n"
        "Eight green bottles hanging on the wall,\n"
        "Eight green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be seven green bottles hanging on the wall.\n"
        "\n"
        "Seven green bottles hanging on the wall,\n"
        "Seven green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be six green bottles hanging on the wall.\n"
        "\n"
        "Six green bottles hanging on the wall,\n"
        "Six green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be five green bottles hanging on the wall.\n"
        "\n"
        "Five green bottles hanging on the wall,\n"
        "Five green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be four green bottles hanging on the wall.\n"
        "\n"
        "Four green bottles hanging on the wall,\n"
        "Four green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be three green bottles hanging on the wall.\n"
        "\n"
        "Three green bottles hanging on the wall,\n"
        "Three green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be two green bottles hanging on the wall.\n"
        "\n"
        "Two green bottles hanging on the wall,\n"
        "Two green bottles hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be one green bottle hanging on the wall.\n"
        "\n"
        "One green bottle hanging on the wall,\n"
        "One green bottle hanging on the wall,\n"
        "And if one green bottle should accidentally fall,\n"
        "There'll be no green bottles hanging on the wall.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_first_generic_verse);
    RUN_TEST(test_last_generic_verse);
    RUN_TEST(test_verse_with_2_bottles);
    RUN_TEST(test_verse_with_1_bottle);
    RUN_TEST(test_first_two_verses);
    RUN_TEST(test_last_three_verses);
    RUN_TEST(test_all_verses);
    return UNITY_END();
}
