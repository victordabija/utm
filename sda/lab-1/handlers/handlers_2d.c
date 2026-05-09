#include <stdio.h>

#include "handlers_2d.h"

#include <stdlib.h>
#include <string.h>

#include "app_menu.h"
#include "application.h"
#include "array.h"
#include "sort.h"
#include "../helpers/helpers.h"

#define MAX_SIZE 100
#define K 10

Array_2d array_2d = {0};

static bool isEmpty() {
    return isEmpty_2d(&array_2d);
}

static Sizes_2d inputSize() {
    Sizes_2d sizes_2d;
    sizes_2d.x = readInt("Please input size: ", 2, MAX_SIZE);
    sizes_2d.y = sizes_2d.x; // by requirement we have a (n * n) matrix.

    return sizes_2d;
}

static void display() {
    displayArray_2d(&array_2d);
}

static void handleDisplay() {
    if (isEmpty()) {
        printf("Nothing to display.");
        return;
    }

    printf("\nTwo dimension array (%d x %d): \n", (int) array_2d.coordinates.x, (int) array_2d.coordinates.y);
    display();
    printf("\n");
}

static void handleInput() {
    array_2d.coordinates = inputSize();
    inputArray_2d(&array_2d);

    handleDisplay();
}

static void handleRandomFill() {
    array_2d.coordinates = inputSize();
    randomFillArray_2d(&array_2d);

    handleDisplay();
}

static void executeA(const bool condition) {
    const int n = (int) array_2d.coordinates.x;
    int *buffer = malloc(n * sizeof(int));


    if (condition) {
        for (int i = 0; i < n; i++) {
            buffer[i] = array_2d.array[i][n - 1 - i];
        }

        quickSort(buffer, 0, n - 1, ASCENDING);

        for (int i = 0; i < n; i++) {
            array_2d.array[i][n - 1 - i] = buffer[i];
        }
    } else {
        for (int i = 0; i < n; i++) {
            buffer[i] = array_2d.array[i][0];
        }

        shellSort(buffer, n, DESCENDING);

        for (int i = 0; i < n; i++) {
            array_2d.array[i][0] = buffer[i];
        }
    }

    free(buffer);
}

static void handleA() {
    const int n = (int) array_2d.coordinates.x;
    if (n <= 1) {
        return;
    }

    const int elementsAboveDiagonal = elementsAboveDiagonalCount(n);

    const bool condition = elementsAboveDiagonal > K;
    const SortType type = condition
                              ? (SortType){QUICK_SORT, ASCENDING}
                              : (SortType){SHELL_SORT, DESCENDING};

    char reason[256];
    sprintf(
        reason,
        "Elements above diagonal (%d) is %s than K (%d).",
        elementsAboveDiagonal,
        (condition ? "greater" : "not greater"),
        K
    );

    condition
        ? strcat(reason, " Sorting secondary diagonal.")
        : strcat(reason, " Sorting first column.");

    execSort_2d(display, type, reason, executeA, condition);
}

static void handleB() {
    const int n = (int) array_2d.coordinates.x;
    if (n <= 0) {
        return;
    }

    // Find the maximum element and count its occurrences
    int maxElement = array_2d.array[0][0];
    int count = 0;
    int maxRow = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (array_2d.array[i][j] > maxElement) {
                maxElement = array_2d.array[i][j];
                count = 1;
                maxRow = i;
            } else if (array_2d.array[i][j] == maxElement) {
                count++;
            }
        }
    }

    const bool condition = count == 1;
    const SortType type = condition
                              ? (SortType){SELECTION_SORT, ASCENDING}
                              : (SortType){INSERTION_SORT, DESCENDING};

    char reason[256];
    sprintf(reason, "Max element (%d) found %d time(s). ", maxElement, count);
    strcat(reason, condition ? "Sorting row." : "Sorting columns.");

    showSortExplanation(reason, type);
    printf("\nBefore sort: \n");
    display();

    if (count == 1) {
        selectionSort(array_2d.array[maxRow], n, ASCENDING);
    } else {
        int *buffer = malloc(n * sizeof(int));

        bool *colsToSort = calloc(n, sizeof(bool));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (array_2d.array[i][j] == maxElement) {
                    colsToSort[j] = true;
                }
            }
        }

        for (int col = 0; col < n; col++) {
            if (colsToSort[col]) {
                for (int i = 0; i < n; i++) {
                    buffer[i] = array_2d.array[i][col];
                }

                insertionSort(buffer, n, DESCENDING);

                for (int i = 0; i < n; i++) {
                    array_2d.array[i][col] = buffer[i];
                }
            }
        }

        free(colsToSort);
        free(buffer);
    }

    printf("\n\nAfter sort: \n");
    display();

    printf("\n");
}

static void handleSort() {
    if (isEmpty()) {
        printf("Nothing to sort.");
    }

    MenuItem items[] = {
        createMenuItem(1, "A", handleA),
        createMenuItem(2, "B", handleB),
    };

    const int count = sizeof(items) / sizeof(MenuItem);

    Menu menu;
    initMenu(&menu, "LABORATORY 1 | TWO-DIMENSIONAL ARRAY SORT", items, count);

    runMenu(&menu);
}

static void handleFree() {
    if (isEmpty()) {
        printf("Nothing to free.");
        return;
    }

    freeArray_2d(&array_2d);

    printf("Memory freed.");
}

void handle_2d() {
    MenuItem items[] = {
        createMenuItem(1, "Input", handleInput),
        createMenuItem(2, "Random fill", handleRandomFill),
        createMenuItem(3, "Display", handleDisplay),
        {4, "Sort", handleSort, false},
        createMenuItem(5, "Free memory", handleFree),
    };

    const int count = sizeof(items) / sizeof(MenuItem);

    Menu menu;
    initMenu(&menu, "LABORATORY 1 | TWO-DIMENSIONAL ARRAY", items, count);

    runMenu(&menu);
}
