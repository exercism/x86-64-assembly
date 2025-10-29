#include "vendor/unity.h"

#include <stdint.h>

extern uint32_t get_box_weight(uint16_t count_first, uint16_t weight_first, uint16_t count_second, uint16_t weight_second);
extern uint8_t max_number_of_boxes(uint8_t box_height);
extern int32_t items_to_be_moved(uint32_t remaining_items, uint32_t items_in_box);
extern int64_t calculate_payment(uint64_t upfront_payment, uint32_t boxes_moved, uint32_t num_trips, uint32_t lost_items,
                                 uint64_t value_of_each_lost_item, uint8_t num_of_workers);

void setUp(void) {
}

void tearDown(void) {
}

void test_weight_of_small_box(void) {
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(2700, get_box_weight(30, 40, 50, 20), "The function was called with arguments: 30, 40, 50, 20.");
}

void test_weight_of_medium_box(void) {
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(6330, get_box_weight(15, 242, 1100, 2), "The function was called with arguments: 15, 242, 1100, 2.");
}

void test_weight_of_large_box(void) {
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(136993, get_box_weight(12, 5600, 133, 521),
                                     "The function was called with arguments: 12, 5600, 133, 521.");
}

void test_max_stack_for_small_box(void) {
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(10, max_number_of_boxes(30), "The function was called with argument: 30.");
}

void test_max_stack_for_medium_box(void) {
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(3, max_number_of_boxes(85), "The function was called with argument: 85.");
}

void test_max_stack_for_large_box(void) {
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(1, max_number_of_boxes(182), "The function was called with argument: 182");
}

void test_items_remaining_for_first_product(void) {
    TEST_ASSERT_EQUAL_INT64_MESSAGE(76412, items_to_be_moved(76532, 120), "The function was called with arguments: 76532, 120.");
}

void test_items_remaining_for_second_product(void) {
    TEST_ASSERT_EQUAL_INT64_MESSAGE(567890, items_to_be_moved(1234876, 666986), "The function was called with arguments: 1234876, 666986.");
}

void test_items_remaining_for_third_product(void) {
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, items_to_be_moved(217, 217), "The function was called with arguments: 217, 217.");
}

void test_items_remaining_accounting_error(void) {
    TEST_ASSERT_EQUAL_INT64_MESSAGE(-567, items_to_be_moved(156, 723), "The function was called with arguments: 156, 723.");
}

void test_payment_few_lost_items(void) {
    TEST_ASSERT_EQUAL_INT64_MESSAGE(2029, calculate_payment(2000, 1000, 5, 21, 2, 1),
                                    "The function was called with arguments: 2000, 1000, 5, 21, 2, 1.");
}

void test_no_payment_too_many_lost_items(void) {
    TEST_ASSERT_EQUAL_INT64_MESSAGE(-794, calculate_payment(2000, 598, 2, 120, 45, 4),
                                    "The function was called with arguments: 2000, 598, 2, 120, 45, 4.");
}

void test_payment_many_boxes(void) {
    TEST_ASSERT_EQUAL_INT64_MESSAGE(2123, calculate_payment(57412, 163214, 183, 1931, 185, 216),
                                    "The function was called with arguments: 57412, 163214, 183, 1931, 185, 216.");
}

void test_no_payment_everything_upfront(void) {
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, calculate_payment(22975, 4523, 6, 120, 8, 5),
                                    "The function was called with arguments: 22975, 4523, 6, 120, 8, 5.");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_weight_of_small_box);
    RUN_TEST(test_weight_of_medium_box);
    RUN_TEST(test_weight_of_large_box);
    RUN_TEST(test_max_stack_for_small_box);
    RUN_TEST(test_max_stack_for_medium_box);
    RUN_TEST(test_max_stack_for_large_box);
    RUN_TEST(test_items_remaining_for_first_product);
    RUN_TEST(test_items_remaining_for_second_product);
    RUN_TEST(test_items_remaining_for_third_product);
    RUN_TEST(test_items_remaining_accounting_error);
    RUN_TEST(test_payment_few_lost_items);
    RUN_TEST(test_no_payment_too_many_lost_items);
    RUN_TEST(test_payment_many_boxes);
    RUN_TEST(test_no_payment_everything_upfront);
    return UNITY_END();
}
