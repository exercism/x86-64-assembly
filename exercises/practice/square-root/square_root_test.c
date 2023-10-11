// Version: 1.0.0

#include "vendor/unity.h"

extern int square_root(int radicand);

void setUp(void) {
}

void tearDown(void) {
}

void test_root_of_1(void) {
    TEST_ASSERT_EQUAL_INT(1, square_root(1));
}

void test_root_of_4(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(2, square_root(4));
}

void test_root_of_25(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(5, square_root(25));
}

void test_root_of_81(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(9, square_root(81));
}

void test_root_of_196(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(14, square_root(196));
}

void test_root_of_65025(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(255, square_root(65025));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_root_of_1);
    RUN_TEST(test_root_of_4);
    RUN_TEST(test_root_of_25);
    RUN_TEST(test_root_of_81);
    RUN_TEST(test_root_of_196);
    RUN_TEST(test_root_of_65025);
    return UNITY_END();
}
