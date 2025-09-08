#include "vendor/unity.h"

#include "stdint.h"
#include "stddef.h"

#define BUFFER_SIZE 20
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern int32_t latest(size_t scores_count, const int32_t *scores);
extern int32_t personal_best(size_t scores_count, const int32_t *scores);
extern size_t personal_top_three(int32_t *buffer, const int32_t *scores, size_t scores_count);

void setUp(void) {
}

void tearDown(void) {
}

void test_list_of_scores(void) {
}

void test_latest_score(void) {
    TEST_IGNORE();
    const int32_t scores[] = {100, 0, 90, 30};
    TEST_ASSERT_EQUAL_INT32(30, latest(ARRAY_SIZE(scores), scores));
}

void test_personal_best(void) {
    TEST_IGNORE();
    const int32_t scores[] = {40, 100, 70};
    TEST_ASSERT_EQUAL_INT32(100, personal_best(ARRAY_SIZE(scores), scores));
}

void test_personal_top_three_from_a_list_of_scores(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];
    const int32_t scores[] = {10, 30, 90, 30, 100, 20, 10, 0, 30, 40, 40, 70, 70};
    const int32_t expected[] = {100, 90, 70};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), personal_top_three(buffer, scores, ARRAY_SIZE(scores)));
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_personal_top_highest_to_lowest(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];
    const int32_t scores[] = {20, 10, 30};
    const int32_t expected[] = {30, 20, 10};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), personal_top_three(buffer, scores, ARRAY_SIZE(scores)));
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_personal_top_when_there_is_a_tie(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];
    const int32_t scores[] = {40, 20, 40, 30};
    const int32_t expected[] = {40, 40, 30};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), personal_top_three(buffer, scores, ARRAY_SIZE(scores)));
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_personal_top_when_there_are_less_than_3(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];
    const int32_t scores[] = {30, 70};
    const int32_t expected[] = {70, 30};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), personal_top_three(buffer, scores, ARRAY_SIZE(scores)));
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_personal_top_when_there_is_only_one(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];
    const int32_t scores[] = {40};
    const int32_t expected[] = {40};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), personal_top_three(buffer, scores, ARRAY_SIZE(scores)));
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_of_scores);
    RUN_TEST(test_latest_score);
    RUN_TEST(test_personal_best);
    RUN_TEST(test_personal_top_three_from_a_list_of_scores);
    RUN_TEST(test_personal_top_highest_to_lowest);
    RUN_TEST(test_personal_top_when_there_is_a_tie);
    RUN_TEST(test_personal_top_when_there_are_less_than_3);
    RUN_TEST(test_personal_top_when_there_is_only_one);
    return UNITY_END();
}
