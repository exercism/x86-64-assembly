#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>
#include <stdlib.h>

#define BUFFER_SIZE 32
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

typedef struct box_t box_t;

typedef enum {
    NONE = 0,
    VALUE,
    BOX
} type_t;

typedef struct {
    size_t size;
    box_t *boxes;
} array_t;

struct box_t {
    type_t tag;
    union {
        int64_t value;
        array_t array;
    } contents;
};

extern size_t flatten(int64_t buffer[], const box_t *box);

void setUp(void) {
}

void tearDown(void) {
}

void test_empty(void) {
    void *objs[100];
    size_t num_obj = 0;

    box_t box;
    box.tag = BOX;
    box.contents.array.size = 0;

    alignas(32) int64_t buffer[BUFFER_SIZE];
    const size_t length = flatten(buffer, &box);
    for (size_t i = num_obj; i-- > 0;) {
        free(objs[i]);
        objs[i] = NULL;
    }

    TEST_ASSERT_EQUAL_UINT64(0, length);
}

void test_no_nesting(void) {
    TEST_IGNORE();
    void *objs[100];
    size_t num_obj = 0;

    box_t box;
    box.tag = BOX;
    box.contents.array.size = 3;
    box.contents.array.boxes = calloc(3, sizeof(box_t));
    objs[num_obj++] = (void *)box.contents.array.boxes;

    box_t *c1 = box.contents.array.boxes;
    c1[0].tag = VALUE;
    c1[0].contents.value = 0;
    c1[1].tag = VALUE;
    c1[1].contents.value = 1;
    c1[2].tag = VALUE;
    c1[2].contents.value = 2;

    alignas(32) int64_t buffer[BUFFER_SIZE];
    const size_t length = flatten(buffer, &box);
    for (size_t i = num_obj; i-- > 0;) {
        free(objs[i]);
        objs[i] = NULL;
    }

    const int64_t expected[] = {0, 1, 2};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_flattens_a_nested_array(void) {
    TEST_IGNORE();
    void *objs[100];
    size_t num_obj = 0;

    box_t box;
    box.tag = BOX;
    box.contents.array.size = 1;
    box.contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)box.contents.array.boxes;

    box_t *c1 = box.contents.array.boxes;
    c1[0].tag = BOX;
    c1[0].contents.array.size = 1;
    c1[0].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c1[0].contents.array.boxes;

    box_t *c2 = c1[0].contents.array.boxes;
    c2[0].tag = BOX;
    c2[0].contents.array.size = 0;

    alignas(32) int64_t buffer[BUFFER_SIZE];
    const size_t length = flatten(buffer, &box);
    for (size_t i = num_obj; i-- > 0;) {
        free(objs[i]);
        objs[i] = NULL;
    }

    TEST_ASSERT_EQUAL_UINT64(0, length);
}

void test_flattens_array_with_just_integers_present(void) {
    TEST_IGNORE();
    void *objs[100];
    size_t num_obj = 0;

    box_t box;
    box.tag = BOX;
    box.contents.array.size = 3;
    box.contents.array.boxes = calloc(3, sizeof(box_t));
    objs[num_obj++] = (void *)box.contents.array.boxes;

    box_t *c1 = box.contents.array.boxes;
    c1[0].tag = VALUE;
    c1[0].contents.value = 1;
    c1[1].tag = BOX;
    c1[1].contents.array.size = 6;
    c1[1].contents.array.boxes = calloc(6, sizeof(box_t));
    objs[num_obj++] = (void *)c1[1].contents.array.boxes;

    box_t *c2 = c1[1].contents.array.boxes;
    c2[0].tag = VALUE;
    c2[0].contents.value = 2;
    c2[1].tag = VALUE;
    c2[1].contents.value = 3;
    c2[2].tag = VALUE;
    c2[2].contents.value = 4;
    c2[3].tag = VALUE;
    c2[3].contents.value = 5;
    c2[4].tag = VALUE;
    c2[4].contents.value = 6;
    c2[5].tag = VALUE;
    c2[5].contents.value = 7;

    c1[2].tag = VALUE;
    c1[2].contents.value = 8;

    alignas(32) int64_t buffer[BUFFER_SIZE];
    const size_t length = flatten(buffer, &box);
    for (size_t i = num_obj; i-- > 0;) {
        free(objs[i]);
        objs[i] = NULL;
    }

    const int64_t expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_5_level_nesting(void) {
    TEST_IGNORE();
    void *objs[100];
    size_t num_obj = 0;

    box_t box;
    box.tag = BOX;
    box.contents.array.size = 4;
    box.contents.array.boxes = calloc(4, sizeof(box_t));
    objs[num_obj++] = (void *)box.contents.array.boxes;

    box_t *c1 = box.contents.array.boxes;
    c1[0].tag = VALUE;
    c1[0].contents.value = 0;
    c1[1].tag = VALUE;
    c1[1].contents.value = 2;
    c1[2].tag = BOX;
    c1[2].contents.array.size = 5;
    c1[2].contents.array.boxes = calloc(5, sizeof(box_t));
    objs[num_obj++] = (void *)c1[2].contents.array.boxes;

    box_t *c2 = c1[2].contents.array.boxes;
    c2[0].tag = BOX;
    c2[0].contents.array.size = 2;
    c2[0].contents.array.boxes = calloc(2, sizeof(box_t));
    objs[num_obj++] = (void *)c2[0].contents.array.boxes;

    box_t *c3 = c2[0].contents.array.boxes;
    c3[0].tag = VALUE;
    c3[0].contents.value = 2;
    c3[1].tag = VALUE;
    c3[1].contents.value = 3;

    c2[1].tag = VALUE;
    c2[1].contents.value = 8;
    c2[2].tag = VALUE;
    c2[2].contents.value = 100;
    c2[3].tag = VALUE;
    c2[3].contents.value = 4;
    c2[4].tag = BOX;
    c2[4].contents.array.size = 1;
    c2[4].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c2[4].contents.array.boxes;

    box_t *c4 = c2[4].contents.array.boxes;
    c4[0].tag = BOX;
    c4[0].contents.array.size = 1;
    c4[0].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c4[0].contents.array.boxes;

    box_t *c5 = c4[0].contents.array.boxes;
    c5[0].tag = BOX;
    c5[0].contents.array.size = 1;
    c5[0].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c5[0].contents.array.boxes;

    box_t *c6 = c5[0].contents.array.boxes;
    c6[0].tag = VALUE;
    c6[0].contents.value = 50;

    c1[3].tag = VALUE;
    c1[3].contents.value = -2;

    alignas(32) int64_t buffer[BUFFER_SIZE];
    const size_t length = flatten(buffer, &box);
    for (size_t i = num_obj; i-- > 0;) {
        free(objs[i]);
        objs[i] = NULL;
    }

    const int64_t expected[] = {0, 2, 2, 3, 8, 100, 4, 50, -2};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_6_level_nesting(void) {
    TEST_IGNORE();
    void *objs[100];
    size_t num_obj = 0;

    box_t box;
    box.tag = BOX;
    box.contents.array.size = 3;
    box.contents.array.boxes = calloc(3, sizeof(box_t));
    objs[num_obj++] = (void *)box.contents.array.boxes;

    box_t *c1 = box.contents.array.boxes;
    c1[0].tag = VALUE;
    c1[0].contents.value = 1;
    c1[1].tag = BOX;
    c1[1].contents.array.size = 5;
    c1[1].contents.array.boxes = calloc(5, sizeof(box_t));
    objs[num_obj++] = (void *)c1[1].contents.array.boxes;

    box_t *c2 = c1[1].contents.array.boxes;
    c2[0].tag = VALUE;
    c2[0].contents.value = 2;
    c2[1].tag = BOX;
    c2[1].contents.array.size = 1;
    c2[1].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c2[1].contents.array.boxes;

    box_t *c3 = c2[1].contents.array.boxes;
    c3[0].tag = BOX;
    c3[0].contents.array.size = 1;
    c3[0].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c3[0].contents.array.boxes;

    box_t *c4 = c3[0].contents.array.boxes;
    c4[0].tag = VALUE;
    c4[0].contents.value = 3;

    c2[2].tag = BOX;
    c2[2].contents.array.size = 2;
    c2[2].contents.array.boxes = calloc(2, sizeof(box_t));
    objs[num_obj++] = (void *)c2[2].contents.array.boxes;

    box_t *c5 = c2[2].contents.array.boxes;
    c5[0].tag = VALUE;
    c5[0].contents.value = 4;
    c5[1].tag = BOX;
    c5[1].contents.array.size = 1;
    c5[1].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c5[1].contents.array.boxes;

    box_t *c6 = c5[1].contents.array.boxes;
    c6[0].tag = BOX;
    c6[0].contents.array.size = 1;
    c6[0].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c6[0].contents.array.boxes;

    box_t *c7 = c6[0].contents.array.boxes;
    c7[0].tag = VALUE;
    c7[0].contents.value = 5;

    c2[3].tag = VALUE;
    c2[3].contents.value = 6;
    c2[4].tag = VALUE;
    c2[4].contents.value = 7;

    c1[2].tag = VALUE;
    c1[2].contents.value = 8;

    alignas(32) int64_t buffer[BUFFER_SIZE];
    const size_t length = flatten(buffer, &box);
    for (size_t i = num_obj; i-- > 0;) {
        free(objs[i]);
        objs[i] = NULL;
    }

    const int64_t expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_null_values_are_omitted_from_the_final_result(void) {
    TEST_IGNORE();
    void *objs[100];
    size_t num_obj = 0;

    box_t box;
    box.tag = BOX;
    box.contents.array.size = 3;
    box.contents.array.boxes = calloc(3, sizeof(box_t));
    objs[num_obj++] = (void *)box.contents.array.boxes;

    box_t *c1 = box.contents.array.boxes;
    c1[0].tag = VALUE;
    c1[0].contents.value = 1;
    c1[1].tag = VALUE;
    c1[1].contents.value = 2;
    c1[2].tag = NONE;

    alignas(32) int64_t buffer[BUFFER_SIZE];
    const size_t length = flatten(buffer, &box);
    for (size_t i = num_obj; i-- > 0;) {
        free(objs[i]);
        objs[i] = NULL;
    }

    const int64_t expected[] = {1, 2};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_consecutive_null_values_at_the_front_of_the_array_are_omitted_from_the_final_result(void) {
    TEST_IGNORE();
    void *objs[100];
    size_t num_obj = 0;

    box_t box;
    box.tag = BOX;
    box.contents.array.size = 3;
    box.contents.array.boxes = calloc(3, sizeof(box_t));
    objs[num_obj++] = (void *)box.contents.array.boxes;

    box_t *c1 = box.contents.array.boxes;
    c1[0].tag = NONE;
    c1[1].tag = NONE;
    c1[2].tag = VALUE;
    c1[2].contents.value = 3;

    alignas(32) int64_t buffer[BUFFER_SIZE];
    const size_t length = flatten(buffer, &box);
    for (size_t i = num_obj; i-- > 0;) {
        free(objs[i]);
        objs[i] = NULL;
    }

    const int64_t expected[] = {3};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_consecutive_null_values_in_the_middle_of_the_array_are_omitted_from_the_final_result(void) {
    TEST_IGNORE();
    void *objs[100];
    size_t num_obj = 0;

    box_t box;
    box.tag = BOX;
    box.contents.array.size = 4;
    box.contents.array.boxes = calloc(4, sizeof(box_t));
    objs[num_obj++] = (void *)box.contents.array.boxes;

    box_t *c1 = box.contents.array.boxes;
    c1[0].tag = VALUE;
    c1[0].contents.value = 1;
    c1[1].tag = NONE;
    c1[2].tag = NONE;
    c1[3].tag = VALUE;
    c1[3].contents.value = 4;

    alignas(32) int64_t buffer[BUFFER_SIZE];
    const size_t length = flatten(buffer, &box);
    for (size_t i = num_obj; i-- > 0;) {
        free(objs[i]);
        objs[i] = NULL;
    }

    const int64_t expected[] = {1, 4};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_6_level_nested_array_with_null_values(void) {
    TEST_IGNORE();
    void *objs[100];
    size_t num_obj = 0;

    box_t box;
    box.tag = BOX;
    box.contents.array.size = 4;
    box.contents.array.boxes = calloc(4, sizeof(box_t));
    objs[num_obj++] = (void *)box.contents.array.boxes;

    box_t *c1 = box.contents.array.boxes;
    c1[0].tag = VALUE;
    c1[0].contents.value = 0;
    c1[1].tag = VALUE;
    c1[1].contents.value = 2;
    c1[2].tag = BOX;
    c1[2].contents.array.size = 5;
    c1[2].contents.array.boxes = calloc(5, sizeof(box_t));
    objs[num_obj++] = (void *)c1[2].contents.array.boxes;

    box_t *c2 = c1[2].contents.array.boxes;
    c2[0].tag = BOX;
    c2[0].contents.array.size = 2;
    c2[0].contents.array.boxes = calloc(2, sizeof(box_t));
    objs[num_obj++] = (void *)c2[0].contents.array.boxes;

    box_t *c3 = c2[0].contents.array.boxes;
    c3[0].tag = VALUE;
    c3[0].contents.value = 2;
    c3[1].tag = VALUE;
    c3[1].contents.value = 3;

    c2[1].tag = VALUE;
    c2[1].contents.value = 8;
    c2[2].tag = BOX;
    c2[2].contents.array.size = 1;
    c2[2].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c2[2].contents.array.boxes;

    box_t *c4 = c2[2].contents.array.boxes;
    c4[0].tag = BOX;
    c4[0].contents.array.size = 1;
    c4[0].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c4[0].contents.array.boxes;

    box_t *c5 = c4[0].contents.array.boxes;
    c5[0].tag = VALUE;
    c5[0].contents.value = 100;

    c2[3].tag = NONE;
    c2[4].tag = BOX;
    c2[4].contents.array.size = 1;
    c2[4].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c2[4].contents.array.boxes;

    box_t *c6 = c2[4].contents.array.boxes;
    c6[0].tag = BOX;
    c6[0].contents.array.size = 1;
    c6[0].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c6[0].contents.array.boxes;

    box_t *c7 = c6[0].contents.array.boxes;
    c7[0].tag = NONE;

    c1[3].tag = VALUE;
    c1[3].contents.value = -2;

    alignas(32) int64_t buffer[BUFFER_SIZE];
    const size_t length = flatten(buffer, &box);
    for (size_t i = num_obj; i-- > 0;) {
        free(objs[i]);
        objs[i] = NULL;
    }

    const int64_t expected[] = {0, 2, 2, 3, 8, 100, -2};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_all_values_in_nested_array_are_null(void) {
    TEST_IGNORE();
    void *objs[100];
    size_t num_obj = 0;

    box_t box;
    box.tag = BOX;
    box.contents.array.size = 6;
    box.contents.array.boxes = calloc(6, sizeof(box_t));
    objs[num_obj++] = (void *)box.contents.array.boxes;

    box_t *c1 = box.contents.array.boxes;
    c1[0].tag = NONE;
    c1[1].tag = BOX;
    c1[1].contents.array.size = 1;
    c1[1].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c1[1].contents.array.boxes;

    box_t *c2 = c1[1].contents.array.boxes;
    c2[0].tag = BOX;
    c2[0].contents.array.size = 1;
    c2[0].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c2[0].contents.array.boxes;

    box_t *c3 = c2[0].contents.array.boxes;
    c3[0].tag = BOX;
    c3[0].contents.array.size = 1;
    c3[0].contents.array.boxes = calloc(1, sizeof(box_t));
    objs[num_obj++] = (void *)c3[0].contents.array.boxes;

    box_t *c4 = c3[0].contents.array.boxes;
    c4[0].tag = NONE;

    c1[2].tag = NONE;
    c1[3].tag = NONE;
    c1[4].tag = BOX;
    c1[4].contents.array.size = 2;
    c1[4].contents.array.boxes = calloc(2, sizeof(box_t));
    objs[num_obj++] = (void *)c1[4].contents.array.boxes;

    box_t *c5 = c1[4].contents.array.boxes;
    c5[0].tag = BOX;
    c5[0].contents.array.size = 2;
    c5[0].contents.array.boxes = calloc(2, sizeof(box_t));
    objs[num_obj++] = (void *)c5[0].contents.array.boxes;

    box_t *c6 = c5[0].contents.array.boxes;
    c6[0].tag = NONE;
    c6[1].tag = NONE;

    c5[1].tag = NONE;

    c1[5].tag = NONE;

    alignas(32) int64_t buffer[BUFFER_SIZE];
    const size_t length = flatten(buffer, &box);
    for (size_t i = num_obj; i-- > 0;) {
        free(objs[i]);
        objs[i] = NULL;
    }

    TEST_ASSERT_EQUAL_UINT64(0, length);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_empty);
    RUN_TEST(test_no_nesting);
    RUN_TEST(test_flattens_a_nested_array);
    RUN_TEST(test_flattens_array_with_just_integers_present);
    RUN_TEST(test_5_level_nesting);
    RUN_TEST(test_6_level_nesting);
    RUN_TEST(test_null_values_are_omitted_from_the_final_result);
    RUN_TEST(test_consecutive_null_values_at_the_front_of_the_array_are_omitted_from_the_final_result);
    RUN_TEST(test_consecutive_null_values_in_the_middle_of_the_array_are_omitted_from_the_final_result);
    RUN_TEST(test_6_level_nested_array_with_null_values);
    RUN_TEST(test_all_values_in_nested_array_are_null);
    return UNITY_END();
}
