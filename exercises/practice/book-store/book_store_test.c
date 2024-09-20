// Version: 0

#include "stdint.h"
#include "vendor/unity.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern int64_t total(int64_t count, const int16_t *basket);

void setUp(void) {
}

void tearDown(void) {
}

void test_only_a_single_book(void) {
    int16_t basket[] = {1};
    TEST_ASSERT_EQUAL_INT(800, total(ARRAY_SIZE(basket), basket));
}

void test_two_of_the_same_book(void) {
    TEST_IGNORE();
    int16_t basket[] = {2, 2};
    TEST_ASSERT_EQUAL_INT(1600, total(ARRAY_SIZE(basket), basket));
}

void test_empty_basket(void) {
    TEST_IGNORE();
    const int16_t* basket = NULL;
    TEST_ASSERT_EQUAL_INT(0, total(0, basket));
}

void test_two_different_books(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 2};
    TEST_ASSERT_EQUAL_INT(1520, total(ARRAY_SIZE(basket), basket));
}

void test_three_different_books(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 2, 3};
    TEST_ASSERT_EQUAL_INT(2160, total(ARRAY_SIZE(basket), basket));
}

void test_four_different_books(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 2, 3, 4};
    TEST_ASSERT_EQUAL_INT(2560, total(ARRAY_SIZE(basket), basket));
}

void test_five_different_books(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT(3000, total(ARRAY_SIZE(basket), basket));
}

void test_two_groups_of_four_is_cheaper_than_group_of_five_plus_group_of_three(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 1, 2, 2, 3, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT(5120, total(ARRAY_SIZE(basket), basket));
}

void test_two_groups_of_four_is_cheaper_than_groups_of_five_and_three(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 1, 2, 3, 4, 4, 5, 5};
    TEST_ASSERT_EQUAL_INT(5120, total(ARRAY_SIZE(basket), basket));
}

void test_group_of_four_plus_group_of_two_is_cheaper_than_two_groups_of_three(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 1, 2, 2, 3, 4};
    TEST_ASSERT_EQUAL_INT(4080, total(ARRAY_SIZE(basket), basket));
}

void test_two_each_of_first_four_books_and_one_copy_each_of_rest(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 1, 2, 2, 3, 3, 4, 4, 5};
    TEST_ASSERT_EQUAL_INT(5560, total(ARRAY_SIZE(basket), basket));
}

void test_two_copies_of_each_book(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
    TEST_ASSERT_EQUAL_INT(6000, total(ARRAY_SIZE(basket), basket));
}

void test_three_copies_of_first_book_and_two_each_of_remaining(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 1};
    TEST_ASSERT_EQUAL_INT(6800, total(ARRAY_SIZE(basket), basket));
}

void test_three_each_of_first_two_books_and_two_each_of_remaining_books(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 1, 2};
    TEST_ASSERT_EQUAL_INT(7520, total(ARRAY_SIZE(basket), basket));
}

void test_four_groups_of_four_are_cheaper_than_two_groups_each_of_five_and_three(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 1, 2, 2, 3, 3, 4, 5, 1, 1, 2, 2, 3, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT(10240, total(ARRAY_SIZE(basket), basket));
}

void test_check_that_groups_of_four_are_created_properly_even_when_there_are_more_groups_of_three_than_groups_of_five(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 5, 5};
    TEST_ASSERT_EQUAL_INT(14560, total(ARRAY_SIZE(basket), basket));
}

void test_one_group_of_one_and_four_is_cheaper_than_one_group_of_two_and_three(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 1, 2, 3, 4};
    TEST_ASSERT_EQUAL_INT(3360, total(ARRAY_SIZE(basket), basket));
}

void test_one_group_of_one_and_two_plus_three_groups_of_four_is_cheaper_than_one_group_of_each_size(void) {
    TEST_IGNORE();
    int16_t basket[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5};
    TEST_ASSERT_EQUAL_INT(10000, total(ARRAY_SIZE(basket), basket));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_only_a_single_book);
    RUN_TEST(test_two_of_the_same_book);
    RUN_TEST(test_empty_basket);
    RUN_TEST(test_two_different_books);
    RUN_TEST(test_three_different_books);
    RUN_TEST(test_four_different_books);
    RUN_TEST(test_five_different_books);
    RUN_TEST(test_two_groups_of_four_is_cheaper_than_group_of_five_plus_group_of_three);
    RUN_TEST(test_two_groups_of_four_is_cheaper_than_groups_of_five_and_three);
    RUN_TEST(test_group_of_four_plus_group_of_two_is_cheaper_than_two_groups_of_three);
    RUN_TEST(test_two_each_of_first_four_books_and_one_copy_each_of_rest);
    RUN_TEST(test_two_copies_of_each_book);
    RUN_TEST(test_three_copies_of_first_book_and_two_each_of_remaining);
    RUN_TEST(test_three_each_of_first_two_books_and_two_each_of_remaining_books);
    RUN_TEST(test_four_groups_of_four_are_cheaper_than_two_groups_each_of_five_and_three);
    RUN_TEST(test_check_that_groups_of_four_are_created_properly_even_when_there_are_more_groups_of_three_than_groups_of_five);
    RUN_TEST(test_one_group_of_one_and_four_is_cheaper_than_one_group_of_two_and_three);
    RUN_TEST(test_one_group_of_one_and_two_plus_three_groups_of_four_is_cheaper_than_one_group_of_each_size);
    return UNITY_END();
}
