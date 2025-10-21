from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <inttypes.h>

#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])
#define MAX_CATEGORIES 10
#define MAX_STRING_LENGTH 50

typedef struct {
    uint64_t ID;
    const char *description;
    uint64_t day;
    uint64_t month;
    uint64_t num_categories;
    const char *categories[MAX_CATEGORIES];
} item_t;

typedef void *(*allocator_t)(uint64_t);
typedef void (*print_t)(const char*, ...);

extern void create_item_entry(item_t *item, uint64_t ID, const char *description, uint64_t day, uint64_t month, uint64_t num_categories, ...);
extern item_t *create_monthly_list(uint64_t capacity, allocator_t allocator);
extern void insert_found_item(item_t *list, uint64_t index, item_t item);
extern void print_item(char buffer[], const item_t *list, uint64_t index, print_t print_fn);

static item_t found_items[5];
static uint64_t found_items_index = 0;

static const uint64_t capacities[] = {
    1200, 1920, 600, 840, 2520, 1440
};

static uint64_t capacity_index = 0;

static void *malloc_helper(uint64_t size) {
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(capacities[capacity_index], size, "The requested size is different from expected.");
    void* list_space = malloc(size);
    unsigned char *bytes = (unsigned char *)list_space;
    for (size_t i = 0; i < size; ++i) {
        bytes[i] = i;
    }
    return list_space;
}

static uint64_t description_index = 0;
static uint64_t print_count = 0;

static void print_helper(const char *introduction, ...) {
    if (introduction) {
        printf("%s\\n", introduction);
    }

    va_list args;
    va_start(args, introduction);

    uint64_t index = va_arg(args, uint64_t);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(description_index, index, "Expected a different index for the item.");
    printf("Index of the item is: %" PRIu64 "\\n", index);

    uint64_t ID = va_arg(args, uint64_t);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[description_index].ID, ID, "Expected a different ID for the item.");
    printf("ID of the item is: %" PRIu64 "\\n", ID);

    const char *description = va_arg(args, const char*);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(found_items[description_index].description, description, "Expected a different description for the item.");
    printf("Description of the item is: %s\\n", description);

    uint64_t day = va_arg(args, uint64_t);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[description_index].day, day, "Expected a different day for the item.");
    printf("Item was found in day: %" PRIu64 "\\n", day);

    uint64_t month = va_arg(args, uint64_t);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[description_index].month, month, "Expected a different month for the item.");
    printf("Item was found in month: %" PRIu64 "\\n", month);

    uint64_t num_categories = va_arg(args, uint64_t);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[description_index].num_categories, num_categories, "Expected a different number of categories for the item.");
    printf("The number of categories for item is: %" PRIu64 "\\n", num_categories);

    const char * const *categories = va_arg(args, const char* const*);
    for (uint64_t i = 0; i < num_categories; ++i) {
        TEST_ASSERT_EQUAL_STRING_MESSAGE(found_items[description_index].categories[i], categories[i], "At least one of the categories is different from expected.");
        printf("Category %" PRIu64 " is: %s\\n", i + 1, categories[i]);
    }
    print_count++;
    printf("\\n");
}
"""

CREATE_ENTRY_START_TEMPLATE = Template("""
create_item_entry(&found_items[found_items_index], ${entries_array});
TEST_ASSERT_EQUAL_UINT64_MESSAGE(${ID}, found_items[found_items_index].ID, "Expected a different ID for the item.");
TEST_ASSERT_EQUAL_STRING_MESSAGE("${description}", found_items[found_items_index].description, "Expected a different description for the item.");
TEST_ASSERT_EQUAL_UINT64_MESSAGE(${day}, found_items[found_items_index].day, "Expected a different day for the item.");
TEST_ASSERT_EQUAL_UINT64_MESSAGE(${month}, found_items[found_items_index].month, "Expected a different month for the item.");
TEST_ASSERT_EQUAL_UINT64_MESSAGE(${num_categories}, found_items[found_items_index].num_categories, "Expected a different number of categories for the item.");
""")

CREATE_MONTHLY_LIST_TEMPLATE = Template("""
for (size_t i = 0; i < ARRAY_SIZE(capacities); ++i) {
    capacity_index = i;
    item_t *list = create_monthly_list(capacities[i], malloc_helper);
    TEST_ASSERT_NOT_NULL_MESSAGE(list, "The list is null");
    const unsigned char *bytes = (const unsigned char *)list;
    for (size_t j = 0; j < capacities[i]; ++j) {
        TEST_ASSERT_MESSAGE(bytes[i] == 0, "There is at least one non-zero byte in the allocated space.");
    }
    free(list);
}
""")

INSERT_FOUND_ITEM_TEMPLATE = Template("""
item_t *list = malloc(ARRAY_SIZE(found_items) * sizeof(item_t));
for (size_t i = 0; i < ARRAY_SIZE(found_items); ++i) {
    insert_found_item(list, i, found_items[i]);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[i].ID, list[i].ID, "Expected a different ID for the item.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(found_items[i].description, list[i].description, "Expected a different description for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[i].day, list[i].day, "Expected a different day for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[i].month, list[i].month, "Expected a different month for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[i].num_categories, list[i].num_categories, "Expected a different number of categories for the item.");
    for (size_t j = 0; j < found_items[i].num_categories; ++j) {
        TEST_ASSERT_EQUAL_STRING_MESSAGE(found_items[i].categories[j], list[i].categories[j], "At least one of the categories is different from expected for the item.");
    }
}
free(list);
""")

PRINT_ITEM_DESCRIPTION_TEMPLATE = Template("""
printf("\\n-------------------------------\\nStart of the printing test.\\n-------------------------------\\n\\n");
for (size_t i = 0; i < ARRAY_SIZE(found_items); ++i) {
    description_index = i;
    char buffer[MAX_STRING_LENGTH];
    print_item(buffer, found_items, description_index, print_helper);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(i + 1, print_count, "The printing function was not called.");
}
printf("-------------------------------\\nEnd of the printing test.\\n-------------------------------\\n\\n");
""")


def extra_cases():
    return [
        {
            "description": "create_item_entry_1",
            "property": "create_item_entry",
            "input": {
                "ID": 128465,
                "description": "A blue watch.",
                "day": 20,
                "month": 10,
                "num_categories": 2,
                "categories": ["watch", "blue"],
            },
            "expected": None,
        },
        {
            "description": "create_item_entry_2",
            "property": "create_item_entry",
            "input": {
                "ID": 78556,
                "description": "A white book of Epidemiology with 1245 pages.",
                "day": 2,
                "month": 7,
                "num_categories": 5,
                "categories": ["book", "white", "large", "Epidemiology", "Medicine"],
            },
            "expected": None,
        },
        {
            "description": "create_item_entry_3",
            "property": "create_item_entry",
            "input": {
                "ID": 45445,
                "description": "A smartphone case with images of unicorns and rainbows.",
                "day": 14,
                "month": 5,
                "num_categories": 3,
                "categories": ["smartphone case", "unicorn image", "rainbow image"],
            },
            "expected": None,
        },
        {
            "description": "create_item_entry_4",
            "property": "create_item_entry",
            "input": {
                "ID": 3348,
                "description": "A red hand mirror.",
                "day": 23,
                "month": 2,
                "num_categories": 2,
                "categories": ["red", "hand mirror"],
            },
            "expected": None,
        },
        {
            "description": "create_item_entry_5",
            "property": "create_item_entry",
            "input": {
                "ID": 14,
                "description": "An yellow tennis ball.",
                "day": 3,
                "month": 1,
                "num_categories": 3,
                "categories": ["yellow", "ball", "tennis"],
            },
            "expected": None,
        },
        {
            "description": "create_monthly_lists",
            "property": "create_monthly_list",
            "input": None,
            "expected": None,
        },
        {
            "description": "insert_found_items",
            "property": "insert_found_item",
            "input": None,
            "expected": None,
        },
        {
            "description": "print_items",
            "property": "print_item",
            "input": None,
            "expected": None,
        },
    ]


def array_literal(cards):
    return str(cards).replace("[", "").replace("]", "").replace("'", '"')


def gen_func_body(prop, inp, expected):
    if prop == "create_item_entry":
        str_list = []
        entries = [
            inp["ID"],
            inp["description"],
            inp["day"],
            inp["month"],
            inp["num_categories"],
            *inp["categories"],
        ]
        str_list.append(
            CREATE_ENTRY_START_TEMPLATE.substitute(
                entries_array=array_literal(entries),
                ID=inp["ID"],
                description=inp["description"],
                day=inp["day"],
                month=inp["month"],
                num_categories=inp["num_categories"],
            )
        )
        for i in range(inp["num_categories"]):
            str_list.append(
                f'TEST_ASSERT_EQUAL_STRING("{inp["categories"][i]}", found_items[found_items_index].categories[{i}]);'
            )
        str_list.append("found_items_index++;")
        return "\n".join(str_list)
    elif prop == "create_monthly_list":
        return CREATE_MONTHLY_LIST_TEMPLATE.substitute()
    elif prop == "insert_found_item":
        return INSERT_FOUND_ITEM_TEMPLATE.substitute()
    return PRINT_ITEM_DESCRIPTION_TEMPLATE.substitute()
