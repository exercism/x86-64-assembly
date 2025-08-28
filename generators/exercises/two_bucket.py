FUNC_PROTO = """\
#include "vendor/unity.h"

#define SUCCESS 0
#define UNREACHABLE_GOAL 1

typedef enum {
   ONE = 1,
   TWO
} bucket_id;

typedef struct {
    size_t moves;
    bucket_id goal_bucket;
    size_t other_bucket;
} bucket_result_t;

extern int measure(bucket_result_t *result, size_t bucket_one, size_t bucket_two, size_t goal, bucket_id start_bucket);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    str_list.append("bucket_result_t result = " + "{0};\n")
    if "error" in expected:
        str_list.append(
            f"TEST_ASSERT_EQUAL(UNREACHABLE_GOAL, {prop}(&result, {inp['bucketOne']}, {inp['bucketTwo']}, {inp['goal']}, {inp['startBucket'].upper()}));\n"
        )
    else:
        str_list.append(
            f"TEST_ASSERT_EQUAL(SUCCESS, {prop}(&result, {inp['bucketOne']}, {inp['bucketTwo']}, {inp['goal']}, {inp['startBucket'].upper()}));\n"
        )
        str_list.append(f"TEST_ASSERT_EQUAL({expected['moves']}, result.moves);\n")
        str_list.append(
            f"TEST_ASSERT_EQUAL({expected['goalBucket'].upper()}, result.goal_bucket);\n"
        )
        str_list.append(
            f"TEST_ASSERT_EQUAL({expected['otherBucket']}, result.other_bucket);\n"
        )
    return "".join(str_list)
