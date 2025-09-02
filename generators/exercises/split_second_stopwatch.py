import re

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define BUFFER_SIZE 20
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

typedef enum {
    ready = 0,
    running,
    stopped
} state_t;

typedef enum {
    success = 0,
    already_running,
    not_running,
    not_stopped
} error_t;

extern void new(void);
extern error_t start(void);
extern error_t stop(void);
extern error_t reset(void);
extern state_t state(void);
extern error_t lap(void);
extern const char *current_lap(void);
extern size_t previous_laps(const char *buffer[]);
extern void advance_time(const char *by);
extern const char *total(void);

const char *null_gen(void) {
    return NULL;
}
"""


def camel_to_snake(s):
    s1 = re.sub("(.)([A-Z][a-z]+)", r"\1_\2", s)
    return re.sub("([a-z0-9])([A-Z])", r"\1_\2", s1).lower()


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}").replace("'", '"')


def gen_func_body(prop, inp, expected):
    str_list = []
    id = 1
    for command in inp["commands"]:
        op = camel_to_snake(command["command"])
        if op == "new":
            str_list.append(f"{op}();")
        elif op == "previous_laps":
            str_list.append(f"const char *buffer_{id}[BUFFER_SIZE];")
            if len(command["expected"]) == 0:
                str_list.append(f"TEST_ASSERT_EQUAL_UINT64(0, {op}(buffer_{id}));")
            else:
                str_list.append(
                    f"const char *const expected_{id}[] = {array_literal(command['expected'])};"
                )
                str_list.append(
                    f"TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected_{id}), {op}(buffer_{id}));"
                )
                str_list.append(
                    f"for (size_t i = 0; i < ARRAY_SIZE(expected_{id}); ++i)" + "{"
                )
                str_list.append(
                    f"TEST_ASSERT_EQUAL_STRING(expected_{id}[i], buffer_{id}[i]);"
                )
                str_list.append("}")
            id += 1
        elif op == "current_lap" or op == "total":
            str_list.append(
                f'const char *const expected_{id} = "{command["expected"]}";'
            )
            str_list.append(f"const char *result_{id} = null_gen();")
            str_list.append(f"result_{id} = {op}();")
            str_list.append(f"TEST_ASSERT_EQUAL_STRING(expected_{id}, result_{id});")
            id += 1
        elif op == "advance_time":
            str_list.append(f'{op}("{command["by"]}");')
        elif op == "state":
            str_list.append(f"TEST_ASSERT_EQUAL({command['expected']}, {op}());")
        else:
            if "expected" in command:
                if (
                    command["expected"]["error"]
                    == "cannot start an already running stopwatch"
                ):
                    str_list.append(f"TEST_ASSERT_EQUAL(already_running, {op}());")
                elif (
                    command["expected"]["error"]
                    == "cannot reset a stopwatch that is not stopped"
                ):
                    str_list.append(f"TEST_ASSERT_EQUAL(not_stopped, {op}());")
                else:
                    str_list.append(f"TEST_ASSERT_EQUAL(not_running, {op}());")
            else:
                str_list.append(f"TEST_ASSERT_EQUAL(success, {op}());")
    return "\n".join(str_list)
