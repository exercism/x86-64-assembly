// Version: 0

#include "vendor/unity.h"

#define BUFFER_SIZE 60

extern void commands(char *buffer, int number);

void setUp(void) {
}

void tearDown(void) {
}

void test_wink_for_1(void) {
    char buffer[BUFFER_SIZE];

    commands(buffer, 1);
    TEST_ASSERT_EQUAL_STRING("wink", buffer);
}

void test_double_blink_for_10(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    commands(buffer, 2);
    TEST_ASSERT_EQUAL_STRING("double blink", buffer);
}

void test_close_your_eyes_for_100(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    commands(buffer, 4);
    TEST_ASSERT_EQUAL_STRING("close your eyes", buffer);
}

void test_jump_for_1000(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    commands(buffer, 8);
    TEST_ASSERT_EQUAL_STRING("jump", buffer);
}

void test_combine_two_actions(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    commands(buffer, 3);
    TEST_ASSERT_EQUAL_STRING("wink, double blink", buffer);
}

void test_reverse_two_actions(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    commands(buffer, 19);
    TEST_ASSERT_EQUAL_STRING("double blink, wink", buffer);
}

void test_reversing_one_action_gives_the_same_action(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    commands(buffer, 24);
    TEST_ASSERT_EQUAL_STRING("jump", buffer);
}

void test_reversing_no_actions_still_gives_no_actions(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    commands(buffer, 16);
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_all_possible_actions(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    commands(buffer, 15);
    TEST_ASSERT_EQUAL_STRING("wink, double blink, close your eyes, jump", buffer);
}

void test_reverse_all_possible_actions(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    commands(buffer, 31);
    TEST_ASSERT_EQUAL_STRING("jump, close your eyes, double blink, wink", buffer);
}

void test_do_nothing_for_zero(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    commands(buffer, 0);
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_wink_for_1);
    RUN_TEST(test_double_blink_for_10);
    RUN_TEST(test_close_your_eyes_for_100);
    RUN_TEST(test_jump_for_1000);
    RUN_TEST(test_combine_two_actions);
    RUN_TEST(test_reverse_two_actions);
    RUN_TEST(test_reversing_one_action_gives_the_same_action);
    RUN_TEST(test_reversing_no_actions_still_gives_no_actions);
    RUN_TEST(test_all_possible_actions);
    RUN_TEST(test_reverse_all_possible_actions);
    RUN_TEST(test_do_nothing_for_zero);
    return UNITY_END();
}
