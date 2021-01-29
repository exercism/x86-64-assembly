// Version: 2.0.0

#include "vendor/unity.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

enum item {
    EGGS,
    PEANUTS,
    SHELLFISH,
    STRAWBERRIES,
    TOMATOES,
    CHOCOLATE,
    POLLEN,
    CATS,
    MAX_ITEMS
};

struct item_list {
    int size;
    enum item items[MAX_ITEMS];
};

extern int allergic_to(enum item item, unsigned int score);
extern void list(unsigned int score, struct item_list *list);

void setUp(void) {
}

void tearDown(void) {
}

void test_eggs_not_allergic_to_anything(void) {
    TEST_ASSERT_FALSE(allergic_to(EGGS, 0));
}

void test_allergic_only_to_eggs(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(EGGS, 1));
}

void test_allergic_to_eggs_and_something_else(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(EGGS, 3));
}

void test_allergic_to_something_but_not_eggs(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(EGGS, 2));
}

void test_eggs_allergic_to_everything(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(EGGS, 255));
}

void test_peanuts_not_allergic_to_anything(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(PEANUTS, 0));
}

void test_allergic_only_to_peanuts(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(PEANUTS, 2));
}

void test_allergic_to_peanuts_and_something_else(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(PEANUTS, 7));
}

void test_allergic_to_something_but_not_peanuts(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(PEANUTS, 5));
}

void test_peanuts_allergic_to_everything(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(PEANUTS, 255));
}

void test_shellfish_not_allergic_to_anything(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(SHELLFISH, 0));
}

void test_allergic_only_to_shellfish(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(SHELLFISH, 4));
}

void test_allergic_to_shellfish_and_something_else(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(SHELLFISH, 14));
}

void test_allergic_to_something_but_not_shellfish(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(SHELLFISH, 10));
}

void test_shellfish_allergic_to_everything(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(SHELLFISH, 255));
}

void test_strawberries_not_allergic_to_anything(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(STRAWBERRIES, 0));
}

void test_allergic_only_to_strawberries(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(STRAWBERRIES, 8));
}

void test_allergic_to_strawberries_and_something_else(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(STRAWBERRIES, 28));
}

void test_allergic_to_something_but_not_strawberries(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(STRAWBERRIES, 20));
}

void test_strawberries_allergic_to_everything(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(STRAWBERRIES, 255));
}

void test_tomatoes_not_allergic_to_anything(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(TOMATOES, 0));
}

void test_allergic_only_to_tomatoes(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(TOMATOES, 16));
}

void test_allergic_to_tomatoes_and_something_else(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(TOMATOES, 56));
}

void test_allergic_to_something_but_not_tomatoes(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(TOMATOES, 40));
}

void test_tomatoes_allergic_to_everything(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(TOMATOES, 255));
}

void test_chocolate_not_allergic_to_anything(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(CHOCOLATE, 0));
}

void test_allergic_only_to_chocolate(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(CHOCOLATE, 32));
}

void test_allergic_to_chocolate_and_something_else(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(CHOCOLATE, 112));
}

void test_allergic_to_something_but_not_chocolate(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(CHOCOLATE, 80));
}

void test_chocolate_allergic_to_everything(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(CHOCOLATE, 255));
}

void test_pollen_not_allergic_to_anything(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(POLLEN, 0));
}

void test_allergic_only_to_pollen(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(POLLEN, 64));
}

void test_allergic_to_pollen_and_something_else(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(POLLEN, 224));
}

void test_allergic_to_something_but_not_pollen(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(POLLEN, 160));
}

void test_pollen_allergic_to_everything(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(POLLEN, 255));
}

void test_cats_not_allergic_to_anything(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(CATS, 0));
}

void test_allergic_only_to_cats(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(CATS, 128));
}

void test_allergic_to_cats_and_something_else(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(CATS, 192));
}

void test_allergic_to_something_but_not_cats(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(allergic_to(CATS, 64));
}

void test_cats_allergic_to_everything(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(allergic_to(CATS, 255));
}

void test_no_allergies(void) {
    TEST_IGNORE();
    struct item_list item_list;

    list(0, &item_list);
    TEST_ASSERT_EQUAL_INT(0, item_list.size);
}

void test_just_eggs(void) {
    TEST_IGNORE();
    int expected[] = {EGGS};
    struct item_list item_list;

    list(1, &item_list);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), item_list.size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, item_list.items, item_list.size);
}

void test_just_peanuts(void) {
    TEST_IGNORE();
    int expected[] = {PEANUTS};
    struct item_list item_list;

    list(2, &item_list);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), item_list.size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, item_list.items, item_list.size);
}

void test_just_strawberries(void) {
    TEST_IGNORE();
    int expected[] = {STRAWBERRIES};
    struct item_list item_list;

    list(8, &item_list);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), item_list.size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, item_list.items, item_list.size);
}

void test_eggs_and_peanuts(void) {
    TEST_IGNORE();
    int expected[] = {EGGS, PEANUTS};
    struct item_list item_list;

    list(3, &item_list);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), item_list.size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, item_list.items, item_list.size);
}

void test_more_than_eggs_but_not_peanuts(void) {
    TEST_IGNORE();
    int expected[] = {EGGS, SHELLFISH};
    struct item_list item_list;

    list(5, &item_list);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), item_list.size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, item_list.items, item_list.size);
}

void test_lots_of_stuff(void) {
    TEST_IGNORE();
    int expected[] = {STRAWBERRIES, TOMATOES, CHOCOLATE, POLLEN, CATS};
    struct item_list item_list;

    list(248, &item_list);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), item_list.size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, item_list.items, item_list.size);
}

void test_everything(void) {
    TEST_IGNORE();
    int expected[] = {EGGS, PEANUTS, SHELLFISH, STRAWBERRIES, TOMATOES, CHOCOLATE, POLLEN, CATS};
    struct item_list item_list;

    list(255, &item_list);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), item_list.size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, item_list.items, item_list.size);
}

void test_no_allergen_score_parts(void) {
    TEST_IGNORE();
    int expected[] = {EGGS, SHELLFISH, STRAWBERRIES, TOMATOES, CHOCOLATE, POLLEN, CATS};
    struct item_list item_list;

    list(509, &item_list);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), item_list.size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, item_list.items, item_list.size);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_eggs_not_allergic_to_anything);
    RUN_TEST(test_allergic_only_to_eggs);
    RUN_TEST(test_allergic_to_eggs_and_something_else);
    RUN_TEST(test_allergic_to_something_but_not_eggs);
    RUN_TEST(test_eggs_allergic_to_everything);
    RUN_TEST(test_peanuts_not_allergic_to_anything);
    RUN_TEST(test_allergic_only_to_peanuts);
    RUN_TEST(test_allergic_to_peanuts_and_something_else);
    RUN_TEST(test_allergic_to_something_but_not_peanuts);
    RUN_TEST(test_peanuts_allergic_to_everything);
    RUN_TEST(test_shellfish_not_allergic_to_anything);
    RUN_TEST(test_allergic_only_to_shellfish);
    RUN_TEST(test_allergic_to_shellfish_and_something_else);
    RUN_TEST(test_allergic_to_something_but_not_shellfish);
    RUN_TEST(test_shellfish_allergic_to_everything);
    RUN_TEST(test_strawberries_not_allergic_to_anything);
    RUN_TEST(test_allergic_only_to_strawberries);
    RUN_TEST(test_allergic_to_strawberries_and_something_else);
    RUN_TEST(test_allergic_to_something_but_not_strawberries);
    RUN_TEST(test_strawberries_allergic_to_everything);
    RUN_TEST(test_tomatoes_not_allergic_to_anything);
    RUN_TEST(test_allergic_only_to_tomatoes);
    RUN_TEST(test_allergic_to_tomatoes_and_something_else);
    RUN_TEST(test_allergic_to_something_but_not_tomatoes);
    RUN_TEST(test_tomatoes_allergic_to_everything);
    RUN_TEST(test_chocolate_not_allergic_to_anything);
    RUN_TEST(test_allergic_only_to_chocolate);
    RUN_TEST(test_allergic_to_chocolate_and_something_else);
    RUN_TEST(test_allergic_to_something_but_not_chocolate);
    RUN_TEST(test_chocolate_allergic_to_everything);
    RUN_TEST(test_pollen_not_allergic_to_anything);
    RUN_TEST(test_allergic_only_to_pollen);
    RUN_TEST(test_allergic_to_pollen_and_something_else);
    RUN_TEST(test_allergic_to_something_but_not_pollen);
    RUN_TEST(test_pollen_allergic_to_everything);
    RUN_TEST(test_cats_not_allergic_to_anything);
    RUN_TEST(test_allergic_only_to_cats);
    RUN_TEST(test_allergic_to_cats_and_something_else);
    RUN_TEST(test_allergic_to_something_but_not_cats);
    RUN_TEST(test_cats_allergic_to_everything);
    RUN_TEST(test_no_allergies);
    RUN_TEST(test_just_eggs);
    RUN_TEST(test_just_peanuts);
    RUN_TEST(test_just_strawberries);
    RUN_TEST(test_eggs_and_peanuts);
    RUN_TEST(test_more_than_eggs_but_not_peanuts);
    RUN_TEST(test_lots_of_stuff);
    RUN_TEST(test_everything);
    RUN_TEST(test_no_allergen_score_parts);
    return UNITY_END();
}
