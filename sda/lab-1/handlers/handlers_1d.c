#include <stdio.h>

#include "handlers_1d.h"
#include "app_menu.h"
#include "application.h"
#include "array.h"
#include "sort.h"
#include "../helpers/helpers.h"

#define MAX_SIZE 100

Array_1d array_1d = {0};

static bool isEmpty() {
    return isEmpty_1d(&array_1d);
}

static int inputSize() {
    return readInt("Please input array size: ", 2, MAX_SIZE);
}

static void displayArray() {
    displayArray_1d(&array_1d);
}

static void handleDisplay() {
    if (isEmpty()) {
        printf("Nothing to display.");
        return;
    }

    printf("\nOne dimension array with size: %d\n", (int) array_1d.size);
    displayArray();
    printf("\n");
}

static void handleInput() {
    array_1d.size = inputSize();
    inputArray_1d(&array_1d);

    handleDisplay();
}

static void handleRandomFill() {
    array_1d.size = inputSize();
    randomFillArray_1d(&array_1d);

    handleDisplay();
}

static void handleA() {
    const bool condition = hasGreaterEvenIndicesMean(array_1d.array, (int) array_1d.size);
    const SortType type = condition
                              ? (SortType){HEAP_SORT, ASCENDING}
                              : (SortType){COUNTING_SORT, DESCENDING};

    char reason[256];
    sprintf(reason, "The mean of elements at even positions is %s than the mean at odd positions.",
            condition ? "greater" : "not greater");

    execSort_1d(displayArray, type, reason, &array_1d);
}

static void handleB() {
    const bool condition = containsPrime(array_1d.array, (int) array_1d.size);
    const SortType type = condition
                              ? (SortType){RADIX_SORT, ASCENDING}
                              : (SortType){COMB_SORT, DESCENDING};

    char reason[256];
    sprintf(reason, "The array %s prime numbers.",
            condition ? "contains" : "does not contain");

    execSort_1d(displayArray, type, reason, &array_1d);
}

static void handleC() {
    const bool condition = isNegativeProductNegative(array_1d.array, (int) array_1d.size);
    const SortType type = condition
                              ? (SortType){MERGE_SORT, DESCENDING}
                              : (SortType){BUBBLE_SORT, ASCENDING};

    char reason[256];
    sprintf(reason, "The product of negative elements is %s.",
            condition ? "negative (odd count of negatives)" : "positive (even count of negatives)");

    execSort_1d(displayArray, type, reason, &array_1d);
}

static void handleSort() {
    if (isEmpty()) {
        printf("Nothing to sort.");
    }

    MenuItem items[] = {
        createMenuItem(1, "A", handleA),
        createMenuItem(2, "B", handleB),
        createMenuItem(3, "C", handleC),
    };

    const int count = sizeof(items) / sizeof(MenuItem);

    Menu menu;
    initMenu(&menu, "LABORATORY 1 | ONE-DIMENSIONAL ARRAY SORT", items, count);

    runMenu(&menu);
}

static void handleFree() {
    if (isEmpty()) {
        printf("Nothing to free.");
        return;
    }

    freeArray_1d(&array_1d);

    printf("Memory freed.");
}

void handle_1d() {
    MenuItem items[] = {
        createMenuItem(1, "Input", handleInput),
        createMenuItem(2, "Random fill", handleRandomFill),
        createMenuItem(3, "Display", handleDisplay),
        {4, "Sort", handleSort, false},
        createMenuItem(5, "Free memory", handleFree),
    };

    const int count = sizeof(items) / sizeof(MenuItem);

    Menu menu;
    initMenu(&menu, "LABORATORY 1 | ONE-DIMENSIONAL ARRAY", items, count);

    runMenu(&menu);
}
