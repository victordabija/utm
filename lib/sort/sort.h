#ifndef UTM_SORT_H
#define UTM_SORT_H

#include <stdbool.h>

typedef enum {
    ASCENDING = 1,
    DESCENDING = -1,
} SortDirection;

typedef enum {
    BUBBLE_SORT,
    COMB_SORT,
    MERGE_SORT,
    HEAP_SORT,
    COUNTING_SORT,
    RADIX_SORT,
    QUICK_SORT,
    SHELL_SORT,
    SELECTION_SORT,
    INSERTION_SORT,
} SortMethod;

typedef struct {
    SortMethod method;
    SortDirection direction;
} SortType;


char *getLabelByDirection(SortDirection direction, bool capitalize);

char *getLabelByMethod(SortMethod method, bool capitalize);

void sortByType(int *arr, int n, SortType type);

void sortByMethod(int *arr, int n, SortDirection direction, SortMethod method);

void bubbleSort(int *arr, int n, SortDirection direction);

void combSort(int *arr, int n, SortDirection direction);

void mergeSort(int *arr, int n, SortDirection direction);

void heapSort(int *arr, int n, SortDirection direction);

void countingSort(int *arr, int n, SortDirection direction);

void radixSort(int *arr, int n, SortDirection direction);

void quickSort(int *arr, int low, int high, SortDirection direction);

void shellSort(int *arr, int n, SortDirection direction);

void selectionSort(int *arr, int n, SortDirection direction);

void insertionSort(int *arr, int n, SortDirection direction);

#endif //UTM_SORT_H
