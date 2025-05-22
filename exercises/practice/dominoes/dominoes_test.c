#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef struct {
    uint16_t first;
    uint16_t second;
} domino_t;

extern int can_chain(size_t domino_count, const domino_t *dominoes);

void setUp(void) {
}

void tearDown(void) {
}

void test_empty_input__empty_output(void) {
    TEST_ASSERT_TRUE(can_chain(0, NULL));
}

void test_singleton_input__singleton_output(void) {
    TEST_IGNORE();
    const domino_t dominoes[] = {{1, 1}};
    TEST_ASSERT_TRUE(can_chain(ARRAY_SIZE(dominoes), dominoes));
}

void test_singleton_that_cant_be_chained(void) {
    TEST_IGNORE();
    const domino_t dominoes[] = {{1, 2}};
    TEST_ASSERT_FALSE(can_chain(ARRAY_SIZE(dominoes), dominoes));
}

void test_three_elements(void) {
    TEST_IGNORE();
    const domino_t dominoes[] = {{1, 2}, {3, 1}, {2, 3}};
    TEST_ASSERT_TRUE(can_chain(ARRAY_SIZE(dominoes), dominoes));
}

void test_can_reverse_dominoes(void) {
    TEST_IGNORE();
    const domino_t dominoes[] = {{1, 2}, {1, 3}, {2, 3}};
    TEST_ASSERT_TRUE(can_chain(ARRAY_SIZE(dominoes), dominoes));
}

void test_cant_be_chained(void) {
    TEST_IGNORE();
    const domino_t dominoes[] = {{1, 2}, {4, 1}, {2, 3}};
    TEST_ASSERT_FALSE(can_chain(ARRAY_SIZE(dominoes), dominoes));
}

void test_disconnected__simple(void) {
    TEST_IGNORE();
    const domino_t dominoes[] = {{1, 1}, {2, 2}};
    TEST_ASSERT_FALSE(can_chain(ARRAY_SIZE(dominoes), dominoes));
}

void test_disconnected__double_loop(void) {
    TEST_IGNORE();
    const domino_t dominoes[] = {{1, 2}, {2, 1}, {3, 4}, {4, 3}};
    TEST_ASSERT_FALSE(can_chain(ARRAY_SIZE(dominoes), dominoes));
}

void test_disconnected__single_isolated(void) {
    TEST_IGNORE();
    const domino_t dominoes[] = {{1, 2}, {2, 3}, {3, 1}, {4, 4}};
    TEST_ASSERT_FALSE(can_chain(ARRAY_SIZE(dominoes), dominoes));
}

void test_need_backtrack(void) {
    TEST_IGNORE();
    const domino_t dominoes[] = {{1, 2}, {2, 3}, {3, 1}, {2, 4}, {2, 4}};
    TEST_ASSERT_TRUE(can_chain(ARRAY_SIZE(dominoes), dominoes));
}

void test_separate_loops(void) {
    TEST_IGNORE();
    const domino_t dominoes[] = {{1, 2}, {2, 3}, {3, 1}, {1, 1}, {2, 2}, {3, 3}};
    TEST_ASSERT_TRUE(can_chain(ARRAY_SIZE(dominoes), dominoes));
}

void test_nine_elements(void) {
    TEST_IGNORE();
    const domino_t dominoes[] = {{1, 2}, {5, 3}, {3, 1}, {1, 2}, {2, 4}, {1, 6}, {2, 3}, {3, 4}, {5, 6}};
    TEST_ASSERT_TRUE(can_chain(ARRAY_SIZE(dominoes), dominoes));
}

void test_separate_threedomino_loops(void) {
    TEST_IGNORE();
    const domino_t dominoes[] = {{1, 2}, {2, 3}, {3, 1}, {4, 5}, {5, 6}, {6, 4}};
    TEST_ASSERT_FALSE(can_chain(ARRAY_SIZE(dominoes), dominoes));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_empty_input__empty_output);
    RUN_TEST(test_singleton_input__singleton_output);
    RUN_TEST(test_singleton_that_cant_be_chained);
    RUN_TEST(test_three_elements);
    RUN_TEST(test_can_reverse_dominoes);
    RUN_TEST(test_cant_be_chained);
    RUN_TEST(test_disconnected__simple);
    RUN_TEST(test_disconnected__double_loop);
    RUN_TEST(test_disconnected__single_isolated);
    RUN_TEST(test_need_backtrack);
    RUN_TEST(test_separate_loops);
    RUN_TEST(test_nine_elements);
    RUN_TEST(test_separate_threedomino_loops);
    return UNITY_END();
}
