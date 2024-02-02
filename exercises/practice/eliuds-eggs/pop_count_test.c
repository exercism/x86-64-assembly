// Version: 1.0.0

#include "vendor/unity.h"

extern int egg_count(int number);

void setUp(void) {
}

void tearDown(void) {
}

void test_0_eggs(void) {
    TEST_ASSERT_EQUAL_INT(0, egg_count(0));
}

void test_1_egg(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(1, egg_count(16));
}

void test_4_eggs(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(4, egg_count(89));
}

void test_13_eggs(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(13, egg_count(2000000000));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_0_eggs);
    RUN_TEST(test_1_egg);
    RUN_TEST(test_4_eggs);
    RUN_TEST(test_13_eggs);
    return UNITY_END();
}
