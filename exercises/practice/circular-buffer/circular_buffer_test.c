#include "vendor/unity.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

extern void create_buffer(size_t capacity);
extern bool read_buffer(int32_t *output);
extern bool write_buffer(int32_t input);
extern void clear_buffer(void);
extern void overwrite_buffer(int32_t input);
extern void delete_buffer(void);

void setUp(void) {
}

void tearDown(void) {
}

void test_reading_empty_buffer_should_fail(void) {
    create_buffer(1);
    int32_t output_1;
    TEST_ASSERT_EQUAL(false, read_buffer(&output_1));
    delete_buffer();
}

void test_can_read_an_item_just_written(void) {
    TEST_IGNORE();
    create_buffer(1);
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    int32_t output_1;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_1));
    TEST_ASSERT_EQUAL(1, output_1);
    delete_buffer();
}

void test_each_item_may_only_be_read_once(void) {
    TEST_IGNORE();
    create_buffer(1);
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    int32_t output_1;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_1));
    TEST_ASSERT_EQUAL(1, output_1);
    int32_t output_2;
    TEST_ASSERT_EQUAL(false, read_buffer(&output_2));
    delete_buffer();
}

void test_items_are_read_in_the_order_they_are_written(void) {
    TEST_IGNORE();
    create_buffer(2);
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    TEST_ASSERT_EQUAL(true, write_buffer(2));
    int32_t output_1;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_1));
    TEST_ASSERT_EQUAL(1, output_1);
    int32_t output_2;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_2));
    TEST_ASSERT_EQUAL(2, output_2);
    delete_buffer();
}

void test_full_buffer_cant_be_written_to(void) {
    TEST_IGNORE();
    create_buffer(1);
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    TEST_ASSERT_EQUAL(false, write_buffer(2));
    delete_buffer();
}

void test_a_read_frees_up_capacity_for_another_write(void) {
    TEST_IGNORE();
    create_buffer(1);
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    int32_t output_1;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_1));
    TEST_ASSERT_EQUAL(1, output_1);
    TEST_ASSERT_EQUAL(true, write_buffer(2));
    int32_t output_2;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_2));
    TEST_ASSERT_EQUAL(2, output_2);
    delete_buffer();
}

void test_read_position_is_maintained_even_across_multiple_writes(void) {
    TEST_IGNORE();
    create_buffer(3);
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    TEST_ASSERT_EQUAL(true, write_buffer(2));
    int32_t output_1;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_1));
    TEST_ASSERT_EQUAL(1, output_1);
    TEST_ASSERT_EQUAL(true, write_buffer(3));
    int32_t output_2;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_2));
    TEST_ASSERT_EQUAL(2, output_2);
    int32_t output_3;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_3));
    TEST_ASSERT_EQUAL(3, output_3);
    delete_buffer();
}

void test_items_cleared_out_of_buffer_cant_be_read(void) {
    TEST_IGNORE();
    create_buffer(1);
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    clear_buffer();
    int32_t output_1;
    TEST_ASSERT_EQUAL(false, read_buffer(&output_1));
    delete_buffer();
}

void test_clear_frees_up_capacity_for_another_write(void) {
    TEST_IGNORE();
    create_buffer(1);
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    clear_buffer();
    TEST_ASSERT_EQUAL(true, write_buffer(2));
    int32_t output_1;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_1));
    TEST_ASSERT_EQUAL(2, output_1);
    delete_buffer();
}

void test_clear_does_nothing_on_empty_buffer(void) {
    TEST_IGNORE();
    create_buffer(1);
    clear_buffer();
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    int32_t output_1;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_1));
    TEST_ASSERT_EQUAL(1, output_1);
    delete_buffer();
}

void test_overwrite_acts_like_write_on_nonfull_buffer(void) {
    TEST_IGNORE();
    create_buffer(2);
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    overwrite_buffer(2);
    int32_t output_1;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_1));
    TEST_ASSERT_EQUAL(1, output_1);
    int32_t output_2;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_2));
    TEST_ASSERT_EQUAL(2, output_2);
    delete_buffer();
}

void test_overwrite_replaces_the_oldest_item_on_full_buffer(void) {
    TEST_IGNORE();
    create_buffer(2);
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    TEST_ASSERT_EQUAL(true, write_buffer(2));
    overwrite_buffer(3);
    int32_t output_1;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_1));
    TEST_ASSERT_EQUAL(2, output_1);
    int32_t output_2;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_2));
    TEST_ASSERT_EQUAL(3, output_2);
    delete_buffer();
}

void test_overwrite_replaces_the_oldest_item_remaining_in_buffer_following_a_read(void) {
    TEST_IGNORE();
    create_buffer(3);
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    TEST_ASSERT_EQUAL(true, write_buffer(2));
    TEST_ASSERT_EQUAL(true, write_buffer(3));
    int32_t output_1;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_1));
    TEST_ASSERT_EQUAL(1, output_1);
    TEST_ASSERT_EQUAL(true, write_buffer(4));
    overwrite_buffer(5);
    int32_t output_2;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_2));
    TEST_ASSERT_EQUAL(3, output_2);
    int32_t output_3;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_3));
    TEST_ASSERT_EQUAL(4, output_3);
    int32_t output_4;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_4));
    TEST_ASSERT_EQUAL(5, output_4);
    delete_buffer();
}

void test_initial_clear_does_not_affect_wrapping_around(void) {
    TEST_IGNORE();
    create_buffer(2);
    clear_buffer();
    TEST_ASSERT_EQUAL(true, write_buffer(1));
    TEST_ASSERT_EQUAL(true, write_buffer(2));
    overwrite_buffer(3);
    overwrite_buffer(4);
    int32_t output_1;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_1));
    TEST_ASSERT_EQUAL(3, output_1);
    int32_t output_2;
    TEST_ASSERT_EQUAL(true, read_buffer(&output_2));
    TEST_ASSERT_EQUAL(4, output_2);
    int32_t output_3;
    TEST_ASSERT_EQUAL(false, read_buffer(&output_3));
    delete_buffer();
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_reading_empty_buffer_should_fail);
    RUN_TEST(test_can_read_an_item_just_written);
    RUN_TEST(test_each_item_may_only_be_read_once);
    RUN_TEST(test_items_are_read_in_the_order_they_are_written);
    RUN_TEST(test_full_buffer_cant_be_written_to);
    RUN_TEST(test_a_read_frees_up_capacity_for_another_write);
    RUN_TEST(test_read_position_is_maintained_even_across_multiple_writes);
    RUN_TEST(test_items_cleared_out_of_buffer_cant_be_read);
    RUN_TEST(test_clear_frees_up_capacity_for_another_write);
    RUN_TEST(test_clear_does_nothing_on_empty_buffer);
    RUN_TEST(test_overwrite_acts_like_write_on_nonfull_buffer);
    RUN_TEST(test_overwrite_replaces_the_oldest_item_on_full_buffer);
    RUN_TEST(test_overwrite_replaces_the_oldest_item_remaining_in_buffer_following_a_read);
    RUN_TEST(test_initial_clear_does_not_affect_wrapping_around);
    return UNITY_END();
}
