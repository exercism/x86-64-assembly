#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 400

extern void recite(char *buffer, const char **strings);

void setUp(void) {
}

void tearDown(void) {
}

void test_zero_pieces(void) {
    const char *strings[] = {
        NULL,
    };
    const char *expected = "";
    char buffer[BUFFER_SIZE];

    recite(buffer, strings);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_one_piece(void) {
    TEST_IGNORE();
    const char *strings[] = {
        "nail",
        NULL,
    };
    const char *expected = "And all for the want of a nail.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, strings);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_two_pieces(void) {
    TEST_IGNORE();
    const char *strings[] = {
        "nail",
        "shoe",
        NULL,
    };
    const char *expected =
        "For want of a nail the shoe was lost.\n"
        "And all for the want of a nail.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, strings);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_three_pieces(void) {
    TEST_IGNORE();
    const char *strings[] = {
        "nail",
        "shoe",
        "horse",
        NULL,
    };
    const char *expected =
        "For want of a nail the shoe was lost.\n"
        "For want of a shoe the horse was lost.\n"
        "And all for the want of a nail.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, strings);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_full_proverb(void) {
    TEST_IGNORE();
    const char *strings[] = {
        "nail", "shoe", "horse", "rider", "message", "battle", "kingdom", NULL,
    };
    const char *expected =
        "For want of a nail the shoe was lost.\n"
        "For want of a shoe the horse was lost.\n"
        "For want of a horse the rider was lost.\n"
        "For want of a rider the message was lost.\n"
        "For want of a message the battle was lost.\n"
        "For want of a battle the kingdom was lost.\n"
        "And all for the want of a nail.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, strings);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_four_pieces_modernized(void) {
    TEST_IGNORE();
    const char *strings[] = {
        "pin", "gun", "soldier", "battle", NULL,
    };
    const char *expected =
        "For want of a pin the gun was lost.\n"
        "For want of a gun the soldier was lost.\n"
        "For want of a soldier the battle was lost.\n"
        "And all for the want of a pin.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, strings);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_zero_pieces);
    RUN_TEST(test_one_piece);
    RUN_TEST(test_two_pieces);
    RUN_TEST(test_three_pieces);
    RUN_TEST(test_full_proverb);
    RUN_TEST(test_four_pieces_modernized);
    return UNITY_END();
}
