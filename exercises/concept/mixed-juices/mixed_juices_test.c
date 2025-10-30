#include "vendor/unity.h"

#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern uint32_t time_to_make_juice(uint32_t ID);
extern uint32_t time_to_prepare(const uint32_t *IDs, uint32_t number_of_IDs);
extern uint32_t limes_to_cut(uint32_t wedges_needed, const uint8_t *limes, uint32_t number_of_limes);
extern uint32_t remaining_orders(uint32_t time_left, const uint32_t *IDs);

void setUp(void) {
}

void tearDown(void) {
}

void test_time_to_make_pure_strawberry_joy(void) {
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, time_to_make_juice(1), "The function was called with arguments: 1.");
}

void test_time_to_make_energizer(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(3, time_to_make_juice(2), "The function was called with arguments: 2.");
}

void test_time_to_make_green_garden(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(3, time_to_make_juice(3), "The function was called with arguments: 3.");
}

void test_time_to_make_tropical_island(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(4, time_to_make_juice(4), "The function was called with arguments: 4.");
}

void test_time_to_make_all_or_nothing(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(5, time_to_make_juice(5), "The function was called with arguments: 5.");
}

void test_time_to_make_feel_good(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(4, time_to_make_juice(6), "The function was called with arguments: 6.");
}

void test_time_to_make_todays_special(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(7, time_to_make_juice(7), "The function was called with arguments: 7.");
}

void test_time_to_make_clients_choice(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(10, time_to_make_juice(8), "The function was called with arguments: 8.");
}

void test_time_to_prepare_one_order(void) {
    TEST_IGNORE();
    const uint32_t IDs[] = {4};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(4, time_to_prepare(IDs, ARRAY_SIZE(IDs)), "The function was called with arguments: 4.");
}

void test_time_to_prepare_a_few_orders(void) {
    TEST_IGNORE();
    const uint32_t IDs[] = {2, 5, 6};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(12, time_to_prepare(IDs, ARRAY_SIZE(IDs)), "The function was called with arguments: 2, 5, 6.");
}

void test_time_to_prepare_many_orders(void) {
    TEST_IGNORE();
    const uint32_t IDs[] = {7, 4, 1, 5, 6, 6, 8, 2, 7};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(45, time_to_prepare(IDs, ARRAY_SIZE(IDs)),
                                     "The function was called with arguments: 7, 4, 1, 5, 6, 6, 8, 2, 7.");
}

void test_limes_to_cut_one_small(void) {
    TEST_IGNORE();
    const uint8_t limes[] = {'S'};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, limes_to_cut(6, limes, ARRAY_SIZE(limes)), "Number of wedges needed: 6. Limes: 'S'.");
}

void test_limes_to_cut_one_medium(void) {
    TEST_IGNORE();
    const uint8_t limes[] = {'M'};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, limes_to_cut(8, limes, ARRAY_SIZE(limes)), "Number of wedges needed: 8. Limes: 'M'.");
}

void test_limes_to_cut_one_large(void) {
    TEST_IGNORE();
    const uint8_t limes[] = {'L'};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, limes_to_cut(10, limes, ARRAY_SIZE(limes)), "Number of wedges needed: 10. Limes: 'L'.");
}

void test_limes_to_cut_two_smalls(void) {
    TEST_IGNORE();
    const uint8_t limes[] = {'S', 'S', 'M'};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(2, limes_to_cut(12, limes, ARRAY_SIZE(limes)), "Number of wedges needed: 12. Limes: 'S', 'S', 'M'.");
}

void test_limes_to_cut_one_small_one_medium(void) {
    TEST_IGNORE();
    const uint8_t limes[] = {'S', 'M', 'S', 'L'};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(2, limes_to_cut(14, limes, ARRAY_SIZE(limes)),
                                     "Number of wedges needed: 14. Limes: 'S', 'M', 'S', 'L'.");
}

void test_limes_to_cut_one_small_one_large(void) {
    TEST_IGNORE();
    const uint8_t limes[] = {'S', 'L', 'M', 'S'};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(2, limes_to_cut(16, limes, ARRAY_SIZE(limes)),
                                     "Number of wedges needed: 16. Limes: 'S', 'L', 'M', 'S'.");
}

void test_limes_to_cut_two_mediums(void) {
    TEST_IGNORE();
    const uint8_t limes[] = {'M', 'M', 'S', 'L'};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(2, limes_to_cut(16, limes, ARRAY_SIZE(limes)),
                                     "Number of wedges needed: 16. Limes: 'M', 'M', 'S', 'L'.");
}

void test_limes_to_cut_one_medium_one_large(void) {
    TEST_IGNORE();
    const uint8_t limes[] = {'M', 'L', 'M', 'S'};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(2, limes_to_cut(18, limes, ARRAY_SIZE(limes)),
                                     "Number of wedges needed: 18. Limes: 'M', 'L', 'M', 'S'.");
}

void test_limes_to_cut_not_exact(void) {
    TEST_IGNORE();
    const uint8_t limes[] = {'S', 'S', 'L', 'M', 'S'};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(4, limes_to_cut(25, limes, ARRAY_SIZE(limes)),
                                     "Number of wedges needed: 25. Limes: 'S', 'S', 'L', 'M', 'S'.");
}

void test_limes_to_cut_many_needed(void) {
    TEST_IGNORE();
    const uint8_t limes[] = {'S', 'M', 'L', 'M', 'L', 'S', 'L', 'M', 'S', 'M', 'S', 'L', 'M', 'L', 'S'};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(
        13, limes_to_cut(99, limes, ARRAY_SIZE(limes)),
        "Number of wedges needed: 99. Limes: 'S', 'M', 'L', 'M', 'L', 'S', 'L', 'M', 'S', 'M', 'S', 'L', 'M', 'L', 'S'.");
}

void test_remaining_orders_one_order(void) {
    TEST_IGNORE();
    const uint32_t IDs[] = {1, 5, 3};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, remaining_orders(1, IDs), "Time left: 1. Order IDs: 1, 5, 3.");
}

void test_remaining_orders_two_orders(void) {
    TEST_IGNORE();
    const uint32_t IDs[] = {6, 1, 3};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(2, remaining_orders(5, IDs), "Time left: 5. Order IDs: 6, 1, 3.");
}

void test_remaining_orders_three_orders(void) {
    TEST_IGNORE();
    const uint32_t IDs[] = {2, 5, 6, 7};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(3, remaining_orders(12, IDs), "Time left: 12. Order IDs: 2, 5, 6, 7.");
}

void test_remaining_orders_work_longer(void) {
    TEST_IGNORE();
    const uint32_t IDs[] = {6, 8, 3};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(2, remaining_orders(9, IDs), "Time left: 9. Order IDs: 6, 8, 3.");
}

void test_remaining_orders_many_orders_left(void) {
    TEST_IGNORE();
    const uint32_t IDs[] = {1, 5, 8, 2, 3, 1, 2, 7, 5, 6, 4};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(3, remaining_orders(7, IDs), "Time left: 7. Order IDs: 1, 5, 8, 2, 3, 1, 2, 7, 5, 6, 4.");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_time_to_make_pure_strawberry_joy);
    RUN_TEST(test_time_to_make_energizer);
    RUN_TEST(test_time_to_make_green_garden);
    RUN_TEST(test_time_to_make_tropical_island);
    RUN_TEST(test_time_to_make_all_or_nothing);
    RUN_TEST(test_time_to_make_feel_good);
    RUN_TEST(test_time_to_make_todays_special);
    RUN_TEST(test_time_to_make_clients_choice);
    RUN_TEST(test_time_to_prepare_one_order);
    RUN_TEST(test_time_to_prepare_a_few_orders);
    RUN_TEST(test_time_to_prepare_many_orders);
    RUN_TEST(test_limes_to_cut_one_small);
    RUN_TEST(test_limes_to_cut_one_medium);
    RUN_TEST(test_limes_to_cut_one_large);
    RUN_TEST(test_limes_to_cut_two_smalls);
    RUN_TEST(test_limes_to_cut_one_small_one_medium);
    RUN_TEST(test_limes_to_cut_one_small_one_large);
    RUN_TEST(test_limes_to_cut_two_mediums);
    RUN_TEST(test_limes_to_cut_one_medium_one_large);
    RUN_TEST(test_limes_to_cut_not_exact);
    RUN_TEST(test_limes_to_cut_many_needed);
    RUN_TEST(test_remaining_orders_one_order);
    RUN_TEST(test_remaining_orders_two_orders);
    RUN_TEST(test_remaining_orders_three_orders);
    RUN_TEST(test_remaining_orders_work_longer);
    RUN_TEST(test_remaining_orders_many_orders_left);
    return UNITY_END();
}
