#include "sort.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../application/application.h"

char *getLabelByDirection(const SortDirection direction, const bool capitalize) {
    static char label[10];
    strcpy(label, direction == ASCENDING ? "ascending" : "descending");

    if (capitalize) {
        label[0] = (char) toupper(label[0]);
    }

    return label;
}

char *getLabelByMethod(const SortMethod method, const bool capitalize) {
    static char label[20];

    switch (method) {
        case BUBBLE_SORT: {
            strcpy(label, "bubble");
            break;
        }
        case COMB_SORT: {
            strcpy(label, "comb");
            break;
        }
        case MERGE_SORT: {
            strcpy(label, "merge");
            break;
        }
        case HEAP_SORT: {
            strcpy(label, "heap");
            break;
        }
        case COUNTING_SORT: {
            strcpy(label, "counting");
            break;
        }
        case RADIX_SORT: {
            strcpy(label, "radix");
            break;
        }
        case QUICK_SORT: {
            strcpy(label, "quick");
            break;
        }
        case SHELL_SORT: {
            strcpy(label, "shell");
            break;
        }
        case SELECTION_SORT: {
            strcpy(label, "selection");
            break;
        }
        case INSERTION_SORT: {
            strcpy(label, "insertion");
            break;
        }

        default: {
            strcpy(label, "unknown");
            break;
        }
    }

    if (capitalize) {
        label[0] = (char) toupper(label[0]);
    }

    return label;
}

void sortByType(int *arr, const int n, const SortType type) {
    sortByMethod(arr, n, type.direction, type.method);
}

void sortByMethod(int *arr, const int n, const SortDirection direction, const SortMethod method) {
    switch (method) {
        case BUBBLE_SORT: {
            bubbleSort(arr, n, direction);
            break;
        }
        case COMB_SORT: {
            combSort(arr, n, direction);
            break;
        }
        case MERGE_SORT: {
            mergeSort(arr, n, direction);
            break;
        }
        case HEAP_SORT: {
            heapSort(arr, n, direction);
            break;
        }
        case COUNTING_SORT: {
            countingSort(arr, n, direction);
            break;
        }
        case RADIX_SORT: {
            radixSort(arr, n, direction);
            break;
        }
        case SHELL_SORT: {
            shellSort(arr, n, direction);
            break;
        }
        case SELECTION_SORT: {
            selectionSort(arr, n, direction);
            break;
        }
        case INSERTION_SORT: {
            insertionSort(arr, n, direction);
            break;
        }


        default: {
            throw("Unexpected sorting method", 1);
            break;
        }
    }
}

/* =========================================
 * Helpers
 * ========================================= */
static void swap(int *a, int *b) {
    const int temp = *a;
    *a = *b;
    *b = temp;
}

static bool shouldSwap(const int a, const int b, const SortDirection direction) {
    if (direction == ASCENDING) {
        return a > b;
    }
    return a < b;
}

/* =========================================
 * 1. Bubble Sort
 * ========================================= */
void bubbleSort(int arr[], const int n, const SortDirection direction) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (shouldSwap(arr[j], arr[j + 1], direction)) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

/* =========================================
 * 2. Comb Sort
 * ========================================= */
void combSort(int arr[], int n, const SortDirection direction) {
    int gap = n;
    bool swapped = true;

    while (gap != 1 || swapped) {
        // Shrink factor of 1.3
        gap = (gap * 10) / 13;
        if (gap < 1) {
            gap = 1;
        }

        swapped = false;
        for (int i = 0; i < n - gap; i++) {
            if (shouldSwap(arr[i], arr[i + gap], direction)) {
                swap(&arr[i], &arr[i + gap]);
                swapped = true;
            }
        }
    }
}

/* =========================================
 * 3. Merge Sort
 * ========================================= */
static void merge(int arr[], const int left, const int mid, const int right, const SortDirection direction) {
    const int n1 = mid - left + 1;
    const int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        const bool condition = (direction == ASCENDING) ? (L[i] <= R[j]) : (L[i] >= R[j]);
        if (condition) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

static void mergeSortHelper(int arr[], const int left, const int right, const SortDirection direction) {
    if (left < right) {
        const int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid, direction);
        mergeSortHelper(arr, mid + 1, right, direction);
        merge(arr, left, mid, right, direction);
    }
}

void mergeSort(int arr[], const int n, const SortDirection direction) {
    mergeSortHelper(arr, 0, n - 1, direction);
}

/* =========================================
 * 4. Heap Sort
 * ========================================= */
static void heapify(int arr[], const int n, const int i, const SortDirection direction) {
    int extreme = i;
    const int left = 2 * i + 1;
    const int right = 2 * i + 2;

    if (direction == ASCENDING) {
        if (left < n && arr[left] > arr[extreme]) {
            extreme = left;
        }
        if (right < n && arr[right] > arr[extreme]) {
            extreme = right;
        }
    } else {
        if (left < n && arr[left] < arr[extreme]) {
            extreme = left;
        }
        if (right < n && arr[right] < arr[extreme]) {
            extreme = right;
        }
    }

    if (extreme != i) {
        swap(&arr[i], &arr[extreme]);
        heapify(arr, n, extreme, direction);
    }
}

void heapSort(int arr[], const int n, const SortDirection direction) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, direction);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0, direction);
    }
}

/* =========================================
 * 5. Counting Sort
 * ========================================= */
void countingSort(int arr[], const int n, const SortDirection direction) {
    if (n <= 1) {
        return;
    }

    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    const int range = max - min + 1;
    int *count = calloc(range, sizeof(int));
    int *output = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        count[arr[i] - min]++;
    }

    if (direction == ASCENDING) {
        for (int i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }
    } else {
        for (int i = range - 2; i >= 0; i--) {
            count[i] += count[i + 1];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

/* =========================================
 * 6. Radix Sort
 * ========================================= */
static void countSortForRadix(int arr[], const int n, const int exp, const SortDirection direction) {
    int *output = malloc(n * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        count[arr[i] / exp % 10]++;
    }

    if (direction == ASCENDING) {
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
    } else {
        for (int i = 8; i >= 0; i--) {
            count[i] += count[i + 1];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        const int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

void radixSort(int arr[], const int n, const SortDirection direction) {
    if (n <= 1) {
        return;
    }

    // Find the minimum element
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    // Offset elements to ensure all are non-negative
    if (min < 0) {
        for (int i = 0; i < n; i++) {
            arr[i] -= min;
        }
    }

    // Find the maximum element in the newly offset array
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Perform standard Radix Sort on non-negative values
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSortForRadix(arr, n, exp, direction);
    }

    // Revert the offset to restore the original negative values
    if (min < 0) {
        for (int i = 0; i < n; i++) {
            arr[i] += min;
        }
    }
}

/* =========================================
 * 7. Quick Sort
 * ========================================= */
static int partition(int *arr, const int low, const int high, const SortDirection direction) {
    const int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        bool condition = false;
        if (direction == ASCENDING) {
            condition = (arr[j] <= pivot);
        } else {
            condition = (arr[j] >= pivot);
        }

        if (condition) {
            i++;
            swap(&arr[i], &arr[j]); // Assuming swap() is still in your file
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int *arr, const int low, const int high, const SortDirection direction) {
    if (low < high) {
        const int pi = partition(arr, low, high, direction);
        quickSort(arr, low, pi - 1, direction);
        quickSort(arr, pi + 1, high, direction);
    }
}

/* =========================================
 * 8. Shell Sort
 * ========================================= */
void shellSort(int *arr, const int n, const SortDirection direction) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            const int temp = arr[i];
            int j;
            for (j = i; j >= gap; j -= gap) {
                bool condition = false;
                if (direction == ASCENDING) {
                    condition = (arr[j - gap] > temp);
                } else {
                    condition = (arr[j - gap] < temp);
                }

                if (condition) {
                    arr[j] = arr[j - gap];
                } else {
                    break;
                }
            }
            arr[j] = temp;
        }
    }
}

/* =========================================
 * 9. Selection Sort
 * ========================================= */
void selectionSort(int *arr, const int n, const SortDirection direction) {
    for (int i = 0; i < n - 1; i++) {
        int extremeIdx = i;
        for (int j = i + 1; j < n; j++) {
            bool condition = false;
            if (direction == ASCENDING) {
                condition = (arr[j] < arr[extremeIdx]);
            } else {
                condition = (arr[j] > arr[extremeIdx]);
            }

            if (condition) {
                extremeIdx = j;
            }
        }
        if (extremeIdx != i) {
            swap(&arr[i], &arr[extremeIdx]);
        }
    }
}

/* =========================================
 * 10. Insertion Sort
 * ========================================= */
void insertionSort(int *arr, const int n, const SortDirection direction) {
    for (int i = 1; i < n; i++) {
        const int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            bool condition = false;
            if (direction == ASCENDING) {
                condition = (arr[j] > key);
            } else {
                condition = (arr[j] < key);
            }

            if (condition) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}
