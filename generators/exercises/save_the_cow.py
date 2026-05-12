FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdalign.h>
#include <stdint.h>
#include <stddef.h>

#define MAX_WORD_SIZE 27
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef enum {
    Error = -1,
    Ongoing,
    Lose,
    Win
} state_t;

typedef struct {
    state_t state;
    char masked_word[MAX_WORD_SIZE];
    uint8_t remaining_failures;
} result_t;

extern result_t guess(const char word[], const char guesses[], size_t num_guesses);
"""


def extra_cases():
    return [
        {
            "description": "Big word, ongoing after many guesses",
            "property": "guess",
            "input": {
                "word": "authentic",
                "guesses": ["a", "e", "p", "m", "i", "l", "c", "n", "o", "r", "q", "u"],
            },
            "expected": {
                "state": "Ongoing",
                "maskedWord": "au__en_ic",
                "remainingFailures": 3,
            },
        },
        {
            "description": "Big word, win after few guesses",
            "property": "guess",
            "input": {
                "word": "intelligence",
                "guesses": ["a", "e", "i", "l", "n", "t", "g", "c"],
            },
            "expected": {
                "state": "Win",
                "maskedWord": "intelligence",
                "remainingFailures": 8,
            },
        },
        {
            "description": "Small word, win after few guesses",
            "property": "guess",
            "input": {"word": "car", "guesses": ["a", "m", "c", "p", "r"]},
            "expected": {"state": "Win", "maskedWord": "car", "remainingFailures": 7},
        },
        {
            "description": "Small word, still lose with a gotcha",
            "property": "guess",
            "input": {
                "word": "dye",
                "guesses": ["a", "r", "m", "p", "c", "o", "q", "n", "u", "e", "d", "i"],
            },
            "expected": {"state": "Lose", "maskedWord": "d_e", "remainingFailures": 0},
        },
    ]


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}").replace('"', "'")


def gen_func_body(prop, inp, expected):
    str_list = []
    str_list.append(f'alignas(16) const char word[MAX_WORD_SIZE] = "{inp["word"]}";')
    if len(inp["guesses"]) == 0:
        str_list.append(f"const result_t result = {prop}(word, NULL, 0);")
    else:
        str_list.append(
            f"alignas(16) const char guesses[] = {array_literal(inp['guesses'])};"
        )
        str_list.append(
            f"const result_t result = {prop}(word, guesses, ARRAY_SIZE(guesses));"
        )
    state = ""
    if isinstance(expected, dict) and "error" in expected:
        state = "Error"
        str_list.append(f"TEST_ASSERT_EQUAL_INT({state}, result.state);")
    else:
        state = expected["state"]
        str_list.append(f"TEST_ASSERT_EQUAL_INT({state}, result.state);")
        str_list.append(
            f'TEST_ASSERT_EQUAL_STRING("{expected["maskedWord"]}", result.masked_word);'
        )
        str_list.append(
            f"TEST_ASSERT_EQUAL_UINT8({expected['remainingFailures']}, result.remaining_failures);"
        )
    return "\n".join(str_list)
