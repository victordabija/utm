#include "helpers.h"

#include <stdio.h>

#include "application.h"

bool hasGreaterEvenIndicesMean(const int *arr, const int n) {
    if (n == 0) {
        return false;
    }

    long long sumEven = 0;
    long long sumOdd = 0;
    int countEven = 0;
    int countOdd = 0;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            sumEven += arr[i];
            countEven++;
        } else {
            sumOdd += arr[i];
            countOdd++;
        }
    }

    const double meanEven = (countEven > 0) ? ((double) sumEven / countEven) : 0.0;
    const double meanOdd = (countOdd > 0) ? ((double) sumOdd / countOdd) : 0.0;

    return meanEven > meanOdd;
}

bool isNegativeProductNegative(const int *arr, const int n) {
    int negativeCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            negativeCount++;
        }
    }

    // The product of negative numbers is only negative if there is an odd amount of them.
    // If the count is 0, the product is technically 0 (or an empty product of 1), which is not negative.
    return (negativeCount % 2) != 0;
}

int elementsAboveDiagonalCount(const int size) {
    return (size * size - size) / 2;
}

void showSortExplanation(char *explanation, const SortType type) {
    printf("Condition: %s\n", explanation);
    printf("Action: Applying %s sort in %s order.\n", getLabelByMethod(type.method,false),
           getLabelByDirection(type.direction, false));
}

void execSort_1d(void (*display)(void), const SortType type, char *reason, const Array_1d *array_1d) {
    showSortExplanation(reason, type);

    printf("\nBefore sort: \n");
    display(); // before sorted

    sortByType(array_1d->array, (int) array_1d->size, type);

    printf("\n\nAfter sort: \n");
    display(); // after sorted

    printf("\n");
}

void execSort_2d(void (*display)(), const SortType type, char *reason,
                 void (*execute)(bool), const bool condition) {
    showSortExplanation(reason, type);

    printf("\nBefore sort: \n");
    display();

    execute(condition);

    printf("\n\nAfter sort: \n");
    display();

    printf("\n");
}
