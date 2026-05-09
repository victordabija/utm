#ifndef UTM_SDA_LAB_1_HELPERS_H
#define UTM_SDA_LAB_1_HELPERS_H

#include <stdbool.h>

#include "array.h"
#include "sort.h"

bool hasGreaterEvenIndicesMean(const int *arr, int n);

bool isNegativeProductNegative(const int *arr, int n);

/**
 *
 * @param size
 * @return count of elements above diagonal of a n * n matrix
 */
int elementsAboveDiagonalCount(int size);

void showSortExplanation(char *explanation, SortType type);

/**
 * Executes sorting. Shows explanations.
 *
 * @param display function which displays the array
 * @param type
 * @param reason why specific sort method and direction was chosen
 * @param array_1d
 */
void execSort_1d(void (*display)(void), SortType type, char *reason, const Array_1d *array_1d);

void execSort_2d(void (*display)(), SortType type, char *reason,
                 void (*execute)(bool), bool condition);

#endif //UTM_SDA_LAB_1_HELPERS_H
