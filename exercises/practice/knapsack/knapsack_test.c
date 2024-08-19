// Version: 0

#include "stdint.h"
#include "vendor/unity.h"

typedef struct {
    uint32_t value;
    uint32_t weight;
} Item;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern uint32_t maximumValue(Item *items, uint32_t count, uint32_t maxWeight);

void setUp(void) {
}

void tearDown(void) {
}

void test_no_items(void) {
    TEST_ASSERT_EQUAL_UINT32(0, maximumValue(NULL, 0, 100));
}

void test_one_item_too_heavy(void) {
    TEST_IGNORE();
    Item items[1] = {
        {1, 100}
    };
    TEST_ASSERT_EQUAL_UINT32(0, maximumValue(items, ARRAY_SIZE(items), 10));
}

void test_five_items_cannot_be_greedy_by_weight(void) {
    TEST_IGNORE();
    Item items[5] = {
        {5, 2},
        {5, 2},
        {5, 2},
        {5, 2},
        {21, 10}
    };
    TEST_ASSERT_EQUAL_UINT32(21, maximumValue(items, ARRAY_SIZE(items), 10));
}

void test_five_items_cannot_be_greedy_by_value(void) {
    TEST_IGNORE();
    Item items[5] = {
        {20, 2},
        {20, 2},
        {20, 2},
        {20, 2},
        {50, 10}
    };
    TEST_ASSERT_EQUAL_UINT32(80, maximumValue(items, ARRAY_SIZE(items), 10));
}

void test_example_knapsack(void) {
    TEST_IGNORE();
    Item items[4] = {
        {10, 5},
        {40, 4},
        {30, 6},
        {50, 4}
    };
    TEST_ASSERT_EQUAL_UINT32(90, maximumValue(items, ARRAY_SIZE(items), 10));
}

void test_8_items(void) {
    TEST_IGNORE();
    Item items[8] = {
        {350, 25},
        {400, 35},
        {450, 45},
        {20, 5},
        {70, 25},
        {8, 3},
        {5, 2},
        {5, 2}
    };
    TEST_ASSERT_EQUAL_UINT32(900, maximumValue(items, ARRAY_SIZE(items), 104));
}

void test_15_items(void) {
    TEST_IGNORE();
    Item items[15] = {
        {135, 70},
        {139, 73},
        {149, 77},
        {150, 80},
        {156, 82},
        {163, 87},
        {173, 90},
        {184, 94},
        {192, 98},
        {201, 106},
        {210, 110},
        {214, 113},
        {221, 115},
        {229, 118},
        {240, 120}
    };
    TEST_ASSERT_EQUAL_UINT32(1458, maximumValue(items, ARRAY_SIZE(items), 750));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_no_items);
    RUN_TEST(test_one_item_too_heavy);
    RUN_TEST(test_five_items_cannot_be_greedy_by_weight);
    RUN_TEST(test_five_items_cannot_be_greedy_by_value);
    RUN_TEST(test_example_knapsack);
    RUN_TEST(test_8_items);
    RUN_TEST(test_15_items);
    return UNITY_END();
}
