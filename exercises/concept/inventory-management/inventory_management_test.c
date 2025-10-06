#include "vendor/unity.h"

#include <stdint.h>

extern uint32_t get_box_weight(uint16_t count_first, uint16_t weight_first, uint16_t count_second, uint16_t weight_second);
extern uint8_t max_number_of_boxes(uint8_t box_height);
extern int32_t items_to_be_moved(uint32_t remaining_items, uint32_t items_in_box);
extern int64_t calculate_payment(uint32_t boxes_moved, uint32_t num_trips, uint32_t lost_items, uint64_t value_of_each_lost_item,
                                 uint64_t upfront_payment);

void setUp(void) {
}

void tearDown(void) {
}

void test_weight_of_small_box() {
    TEST_ASSERT_EQUAL_UINT32(2700, get_box_weight(30, 40, 50, 20));
}

void test_weight_of_medium_box() {
    TEST_ASSERT_EQUAL_UINT32(6330, get_box_weight(15, 242, 1100, 2));
}

void test_weight_of_large_box() {
    TEST_ASSERT_EQUAL_UINT32(136993, get_box_weight(12, 5600, 133, 521));
}

void test_max_stack_for_small_box() {
    TEST_ASSERT_EQUAL_UINT8(10, max_number_of_boxes(30));
}

void test_max_stack_for_medium_box() {
    TEST_ASSERT_EQUAL_UINT8(3, max_number_of_boxes(85));
}

void test_max_stack_for_large_box() {
    TEST_ASSERT_EQUAL_UINT8(1, max_number_of_boxes(182));
}

void test_items_remaining_for_first_product() {
    TEST_ASSERT_EQUAL_INT64(76412, items_to_be_moved(76532, 120));
}

void test_items_remaining_for_second_product() {
    TEST_ASSERT_EQUAL_INT64(567890, items_to_be_moved(1234876, 666986));
}

void test_items_remaining_for_third_product() {
    TEST_ASSERT_EQUAL_INT64(0, items_to_be_moved(217, 217));
}

void test_items_remaining_accounting_error() {
    TEST_ASSERT_EQUAL_INT64(-567, items_to_be_moved(156, 723));
}

void test_payment_few_lost_items() {
    TEST_ASSERT_EQUAL_INT64(4058, calculate_payment(1000, 5, 21, 2, 2000));
}

void test_no_payment_too_many_lost_items() {
    TEST_ASSERT_EQUAL_INT64(-3970, calculate_payment(598, 2, 120, 45, 2000));
}

void test_payment_many_boxes() {
    TEST_ASSERT_EQUAL_INT64(441683, calculate_payment(163214, 183, 1931, 185, 57412));
}

void test_no_payment_everything_upfront() {
    TEST_ASSERT_EQUAL_INT64(0, calculate_payment(4523, 6, 120, 8, 22975));
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
