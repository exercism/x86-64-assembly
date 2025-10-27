#include "vendor/unity.h"

#include <stdint.h>

enum currency_t {
    GBP,
    EUR,
    JPY,
    AUD,
    BRL,
    CNY,
    CAD,
    INR
};

static const double value_in_US_dollars[] = {1.33329, 1.16443, 0.00654374, 0.650888, 0.185577, 0.140420, 0.714142, 0.0113863};

extern void stringify_currency(char *buffer, enum currency_t currency);
extern double exchange_rate(enum currency_t domestic_currency, enum currency_t foreign_currency, const double *value_in_US_dollars);
extern uint64_t get_value_of_bills(unsigned long long denomination, unsigned short number_of_bills);
extern unsigned int get_number_of_bills(float amount, unsigned long long denomination);
extern uint32_t exchangeable_value(float budget, double exchange_rate, uint8_t spread, unsigned long long denomination);

void setUp(void) {
}

void tearDown(void) {
}

void test_stringify_currencies(void) {
    char buffer[4];
    stringify_currency(buffer, GBP);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("GBP", buffer, "Currency: GBP.");
    stringify_currency(buffer, AUD);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("AUD", buffer, "Currency: AUD.");
    stringify_currency(buffer, JPY);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("JPY", buffer, "Currency: JPY.");
    stringify_currency(buffer, CNY);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("CNY", buffer, "Currency: CNY.");
    stringify_currency(buffer, EUR);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("EUR", buffer, "Currency: EUR.");
    stringify_currency(buffer, INR);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("INR", buffer, "Currency: INR.");
    stringify_currency(buffer, CAD);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("CAD", buffer, "Currency: CAD.");
    stringify_currency(buffer, BRL);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("BRL", buffer, "Currency: BRL.");
}

void test_exchange_rates(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(203.7504546329775, exchange_rate(JPY, GBP, value_in_US_dollars),
                                     "Domestic Currency: JPY; Foreign Currency: GBP.");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(0.01594402793842121, exchange_rate(CAD, INR, value_in_US_dollars),
                                     "Domestic Currency: CAD; Foreign Currency: INR.");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(3.5073742974614315, exchange_rate(BRL, AUD, value_in_US_dollars),
                                     "Domestic Currency: BRL; Foreign Currency: AUD.");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(0.12059119053957729, exchange_rate(EUR, CNY, value_in_US_dollars),
                                     "Domestic Currency: EUR; Foreign Currency: CNY.");
}

void test_value_of_bills(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(6400000000, get_value_of_bills(5000000, 1280), "Denomination: 5000000; number of bills: 1280.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(18000, get_value_of_bills(50, 360), "Denomination: 50; number of bills: 360.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(40000, get_value_of_bills(200, 200), "Denomination: 200; number of bills: 200.");
}

void test_number_of_bills(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(3, get_number_of_bills(163271, 50000), "Amount: 163271; Denomination: 50000.");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(54, get_number_of_bills(54361, 1000), "Amount: 54361; Denomination: 1000.");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(63, get_number_of_bills(127.99, 2), "Amount: 127.99; Denomination: 2.");
}

void test_exchangeable_values(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(8568, exchangeable_value(100000, 10.61, 10, 1),
                                     "Budget: 100000; Exchange Rate: 10.61; Spread: 10; Denomination: 1.");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1400, exchangeable_value(1500, 0.84, 25, 40),
                                     "Budget: 1500; Exchange Rate: 0.84; Spread: 25; Denomination: 40.");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(0, exchangeable_value(470000, 1050, 30, 10000000000),
                                     "Budget: 470000; Exchange Rate: 1050; Spread: 30; Denomination: 10000000000.");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(363300, exchangeable_value(425.33, 0.0009, 30, 700),
                                     "Budget: 425.33; Exchange Rate: 0.0009; Spread: 30; Denomination: 700.");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_stringify_currencies);
    RUN_TEST(test_exchange_rates);
    RUN_TEST(test_value_of_bills);
    RUN_TEST(test_number_of_bills);
    RUN_TEST(test_exchangeable_values);
    return UNITY_END();
}
