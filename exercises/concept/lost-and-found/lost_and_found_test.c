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
typedef void (*print_t)(const char *, ...);

extern void create_item_entry(item_t *item, uint64_t ID, const char *description, uint64_t day, uint64_t month, uint64_t num_categories,
                              ...);
extern item_t *create_monthly_list(uint64_t capacity, allocator_t allocator);
extern void insert_found_item(item_t *list, uint64_t index, item_t item);
extern void print_item(char buffer[], const item_t *list, uint64_t index, print_t print_fn);

static item_t found_items[5];
static uint64_t found_items_index = 0;

static const uint64_t capacities[] = {1200, 1920, 600, 840, 2520, 1440};

static uint64_t capacity_index = 0;

static void *malloc_helper(uint64_t size) {
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(capacities[capacity_index], size, "In allocator: the requested size is different from expected.");
    void *list_space = malloc(size);
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
        printf("%s\n", introduction);
    }

    va_list args;
    va_start(args, introduction);

    uint64_t index = va_arg(args, uint64_t);
    uint64_t ID = va_arg(args, uint64_t);
    const char *description = va_arg(args, const char *);
    uint64_t day = va_arg(args, uint64_t);
    uint64_t month = va_arg(args, uint64_t);
    uint64_t num_categories = va_arg(args, uint64_t);
    const char *const *categories = va_arg(args, const char *const *);

    va_end(args);

    TEST_ASSERT_EQUAL_UINT64_MESSAGE(description_index, index, "Expected a different index for the item.");
    printf("Index of the item is: %" PRIu64 "\n", index);

    TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[description_index].ID, ID, "Expected a different ID for the item.");
    printf("ID of the item is: %" PRIu64 "\n", ID);

    TEST_ASSERT_EQUAL_STRING_MESSAGE(found_items[description_index].description, description,
                                     "Expected a different description for the item.");
    printf("Description of the item is: %s\n", description);

    TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[description_index].day, day, "Expected a different day for the item.");
    printf("Item was found in day: %" PRIu64 "\n", day);

    TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[description_index].month, month, "Expected a different month for the item.");
    printf("Item was found in month: %" PRIu64 "\n", month);

    TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[description_index].num_categories, num_categories,
                                     "Expected a different number of categories for the item.");
    printf("The number of categories for item is: %" PRIu64 "\n", num_categories);

    for (uint64_t i = 0; i < num_categories; ++i) {
        TEST_ASSERT_EQUAL_STRING_MESSAGE(found_items[description_index].categories[i], categories[i],
                                         "At least one of the categories is different from expected.");
        printf("Category %" PRIu64 " is: %s\n", i + 1, categories[i]);
    }
    print_count++;
    printf("\n");
}

void setUp(void) {
}

void tearDown(void) {
}

void test_create_item_entry_1(void) {
    create_item_entry(&found_items[found_items_index], 128465, "A blue watch.", 20, 10, 2, "watch", "blue");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(128465, found_items[found_items_index].ID, "Expected a different ID for the item.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("A blue watch.", found_items[found_items_index].description,
                                     "Expected a different description for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(20, found_items[found_items_index].day, "Expected a different day for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(10, found_items[found_items_index].month, "Expected a different month for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, found_items[found_items_index].num_categories,
                                     "Expected a different number of categories for the item.");

    TEST_ASSERT_EQUAL_STRING("watch", found_items[found_items_index].categories[0]);
    TEST_ASSERT_EQUAL_STRING("blue", found_items[found_items_index].categories[1]);
    found_items_index++;
}

void test_create_item_entry_2(void) {
    TEST_IGNORE();

    create_item_entry(&found_items[found_items_index], 78556, "A white book of Epidemiology with 1245 pages.", 2, 7, 5, "book", "white",
                      "large", "Epidemiology", "Medicine");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(78556, found_items[found_items_index].ID, "Expected a different ID for the item.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("A white book of Epidemiology with 1245 pages.", found_items[found_items_index].description,
                                     "Expected a different description for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, found_items[found_items_index].day, "Expected a different day for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, found_items[found_items_index].month, "Expected a different month for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, found_items[found_items_index].num_categories,
                                     "Expected a different number of categories for the item.");

    TEST_ASSERT_EQUAL_STRING("book", found_items[found_items_index].categories[0]);
    TEST_ASSERT_EQUAL_STRING("white", found_items[found_items_index].categories[1]);
    TEST_ASSERT_EQUAL_STRING("large", found_items[found_items_index].categories[2]);
    TEST_ASSERT_EQUAL_STRING("Epidemiology", found_items[found_items_index].categories[3]);
    TEST_ASSERT_EQUAL_STRING("Medicine", found_items[found_items_index].categories[4]);
    found_items_index++;
}

void test_create_item_entry_3(void) {
    TEST_IGNORE();

    create_item_entry(&found_items[found_items_index], 45445, "A smartphone case with images of unicorns and rainbows.", 14, 5, 3,
                      "smartphone case", "unicorn image", "rainbow image");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(45445, found_items[found_items_index].ID, "Expected a different ID for the item.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("A smartphone case with images of unicorns and rainbows.", found_items[found_items_index].description,
                                     "Expected a different description for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(14, found_items[found_items_index].day, "Expected a different day for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, found_items[found_items_index].month, "Expected a different month for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, found_items[found_items_index].num_categories,
                                     "Expected a different number of categories for the item.");

    TEST_ASSERT_EQUAL_STRING("smartphone case", found_items[found_items_index].categories[0]);
    TEST_ASSERT_EQUAL_STRING("unicorn image", found_items[found_items_index].categories[1]);
    TEST_ASSERT_EQUAL_STRING("rainbow image", found_items[found_items_index].categories[2]);
    found_items_index++;
}

void test_create_item_entry_4(void) {
    TEST_IGNORE();

    create_item_entry(&found_items[found_items_index], 3348, "A red hand mirror.", 23, 2, 2, "red", "hand mirror");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(3348, found_items[found_items_index].ID, "Expected a different ID for the item.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("A red hand mirror.", found_items[found_items_index].description,
                                     "Expected a different description for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(23, found_items[found_items_index].day, "Expected a different day for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, found_items[found_items_index].month, "Expected a different month for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, found_items[found_items_index].num_categories,
                                     "Expected a different number of categories for the item.");

    TEST_ASSERT_EQUAL_STRING("red", found_items[found_items_index].categories[0]);
    TEST_ASSERT_EQUAL_STRING("hand mirror", found_items[found_items_index].categories[1]);
    found_items_index++;
}

void test_create_item_entry_5(void) {
    TEST_IGNORE();

    create_item_entry(&found_items[found_items_index], 14, "An yellow tennis ball.", 3, 1, 3, "yellow", "ball", "tennis");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(14, found_items[found_items_index].ID, "Expected a different ID for the item.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("An yellow tennis ball.", found_items[found_items_index].description,
                                     "Expected a different description for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, found_items[found_items_index].day, "Expected a different day for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1, found_items[found_items_index].month, "Expected a different month for the item.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, found_items[found_items_index].num_categories,
                                     "Expected a different number of categories for the item.");

    TEST_ASSERT_EQUAL_STRING("yellow", found_items[found_items_index].categories[0]);
    TEST_ASSERT_EQUAL_STRING("ball", found_items[found_items_index].categories[1]);
    TEST_ASSERT_EQUAL_STRING("tennis", found_items[found_items_index].categories[2]);
    found_items_index++;
}

void test_create_monthly_lists(void) {
    TEST_IGNORE();

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
}

void test_insert_found_items(void) {
    TEST_IGNORE();

    item_t *list = malloc(ARRAY_SIZE(found_items) * sizeof(item_t));
    for (size_t i = 0; i < ARRAY_SIZE(found_items); ++i) {
        insert_found_item(list, i, found_items[i]);
        TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[i].ID, list[i].ID, "Expected a different ID for the item.");
        TEST_ASSERT_EQUAL_STRING_MESSAGE(found_items[i].description, list[i].description, "Expected a different description for the item.");
        TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[i].day, list[i].day, "Expected a different day for the item.");
        TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[i].month, list[i].month, "Expected a different month for the item.");
        TEST_ASSERT_EQUAL_UINT64_MESSAGE(found_items[i].num_categories, list[i].num_categories,
                                         "Expected a different number of categories for the item.");
        for (size_t j = 0; j < found_items[i].num_categories; ++j) {
            TEST_ASSERT_EQUAL_STRING_MESSAGE(found_items[i].categories[j], list[i].categories[j],
                                             "At least one of the categories is different from expected for the item.");
        }
    }
    free(list);
}

void test_print_items(void) {
    TEST_IGNORE();

    printf("\n-------------------------------\nStart of the printing test.\n-------------------------------\n\n");
    for (size_t i = 0; i < ARRAY_SIZE(found_items); ++i) {
        description_index = i;
        char buffer[MAX_STRING_LENGTH];
        print_item(buffer, found_items, description_index, print_helper);
        TEST_ASSERT_EQUAL_UINT64_MESSAGE(i + 1, print_count, "The printing function was not called.");
    }
    printf("-------------------------------\nEnd of the printing test.\n-------------------------------\n\n");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_item_entry_1);
    RUN_TEST(test_create_item_entry_2);
    RUN_TEST(test_create_item_entry_3);
    RUN_TEST(test_create_item_entry_4);
    RUN_TEST(test_create_item_entry_5);
    RUN_TEST(test_create_monthly_lists);
    RUN_TEST(test_insert_found_items);
    RUN_TEST(test_print_items);
    return UNITY_END();
}
