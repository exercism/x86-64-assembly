
#include "vendor/unity.h"

#include <stdint.h>

extern double daily_rate(double hourly_rate);
extern double apply_discount(double price, double discount);
extern uint64_t monthly_rate(double hourly_rate, double discount);
extern uint32_t days_in_budget(uint64_t budget, double hourly_rate, double discount);

void setUp(void) {
}

void tearDown(void) {
}

void test_daily_rate_is_hourly_times_8(void) {
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(400.0, daily_rate(50), "The function was called with arguments: 50.");
}

void test_daily_rate_always_returns_double(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(480.0, daily_rate(60), "The function was called with arguments: 60.");
}

void test_daily_rate_does_not_round(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(440.8, daily_rate(55.1), "The function was called with arguments: 55.1.");
}

void test_apply_discount_10_percent(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(126.0, apply_discount(140.0, 10.0), "The function was called with arguments: 140.0, 10.0.");
}

void test_apply_discount_does_not_round(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(96.11015, apply_discount(111.11, 13.5), "The function was called with arguments: 111.11, 13.5.");
}

void test_monthly_rate_is_daily_rate_times_22(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(10912, monthly_rate(62.0, 0.0), "The function was called with arguments: 62.0, 0.0.");
}

void test_monthly_rate_is_rounded_up_1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(11053, monthly_rate(62.8, 0.0), "The function was called with arguments: 62.8, 0.0.");
}

void test_monthly_rate_is_rounded_up_2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(11476, monthly_rate(65.2, 0.0), "The function was called with arguments: 65.2, 0.0.");
}

void test_monthly_rate_gives_a_discount(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(10377, monthly_rate(67.0, 12.0), "The function was called with arguments: 67.0, 12.0.");
}

void test_days_in_budget_is_budget_divided_by_daily_rate(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(4, days_in_budget(1600, 50.0, 0.0), "The function was called with arguments: 1600, 50.0, 0.0.");
}

void test_days_in_budget_rounds_down_1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(9, days_in_budget(4390, 55.0, 0.0), "The function was called with arguments: 4390, 55.0, 0.0.");
}

void test_days_in_budget_rounds_down_2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(10, days_in_budget(4480, 55.0, 0.0), "The function was called with arguments: 4480, 55.0, 0.0.");
}

void test_days_in_budget_applies_discount(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, days_in_budget(480, 70.0, 20.0), "The function was called with arguments: 480, 70.0, 20.0.");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_daily_rate_is_hourly_times_8);
    RUN_TEST(test_daily_rate_always_returns_double);
    RUN_TEST(test_daily_rate_does_not_round);
    RUN_TEST(test_apply_discount_10_percent);
    RUN_TEST(test_apply_discount_does_not_round);
    RUN_TEST(test_monthly_rate_is_daily_rate_times_22);
    RUN_TEST(test_monthly_rate_is_rounded_up_1);
    RUN_TEST(test_monthly_rate_is_rounded_up_2);
    RUN_TEST(test_monthly_rate_gives_a_discount);
    RUN_TEST(test_days_in_budget_is_budget_divided_by_daily_rate);
    RUN_TEST(test_days_in_budget_rounds_down_1);
    RUN_TEST(test_days_in_budget_rounds_down_2);
    RUN_TEST(test_days_in_budget_applies_discount);
    return UNITY_END();
}
