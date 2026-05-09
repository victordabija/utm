#include "array.h"

#include <stdio.h>

#include "application.h"

#include <stdlib.h>

#define MIN (-99)
#define MAX 99

static void freeIfNotEmpty_1d(Array_1d *array_1d) {
    if (isEmpty_1d(array_1d)) {
        freeArray_1d(array_1d);
    }
}

static void freeIfNotEmpty_2d(Array_2d *array_2d) {
    if (isEmpty_2d(array_2d)) {
        freeArray_2d(array_2d);
    }
}

void inputArray_1d(Array_1d *array_1d) {
    freeIfNotEmpty_1d(array_1d);

    array_1d->array = malloc(array_1d->size * sizeof(int));

    for (size_t i = 0; i < array_1d->size; i++) {
        array_1d->array[i] = readInt("Please input value: ", MIN, MAX);
    }
}

void inputArray_2d(Array_2d *array_2d) {
    freeIfNotEmpty_2d(array_2d);

    array_2d->array = malloc(array_2d->coordinates.y * sizeof(int *));

    for (size_t i = 0; i < array_2d->coordinates.y; i++) {
        array_2d->array[i] = malloc(array_2d->coordinates.x * sizeof(int));

        for (size_t j = 0; j < array_2d->coordinates.x; j++) {
            array_2d->array[i][j] = readInt("Input value: ", MIN, MAX);
        }
    }
}

void displayArray_1d(const Array_1d *array_1d) {
    for (size_t i = 0; i < array_1d->size; i++) {
        printf(" %-3d ", array_1d->array[i]);
    }
}

void displayArray_2d(const Array_2d *array_2d) {
    for (size_t i = 0; i < array_2d->coordinates.y; i++) {
        for (size_t j = 0; j < array_2d->coordinates.x; j++) {
            printf(" %-3d ", array_2d->array[i][j]);
        }
        printf("\n");
    }
}

void randomFillArray_1d(Array_1d *array_1d) {
    freeIfNotEmpty_1d(array_1d);

    array_1d->array = malloc(array_1d->size * sizeof(int));

    for (size_t i = 0; i < array_1d->size; i++) {
        array_1d->array[i] = MIN + rand() % (MAX - MIN + 1);;
    }
}

void randomFillArray_2d(Array_2d *array_2d) {
    freeIfNotEmpty_2d(array_2d);

    array_2d->array = malloc(array_2d->coordinates.y * sizeof(int *));

    for (size_t i = 0; i < array_2d->coordinates.y; i++) {
        array_2d->array[i] = malloc(array_2d->coordinates.x * sizeof(int));

        for (size_t j = 0; j < array_2d->coordinates.x; j++) {
            array_2d->array[i][j] = MIN + rand() % (MAX - MIN + 1);
        }
    }
}

bool isEmpty_1d(const Array_1d *array_1d) {
    return array_1d->size == 0 || array_1d->array == NULL;
}

bool isEmpty_2d(const Array_2d *array_2d) {
    return array_2d->coordinates.x == 0 || array_2d->coordinates.y == 0 || array_2d->array == NULL;
}

void freeArray_1d(Array_1d *array_1d) {
    if (array_1d->array != NULL) {
        free(array_1d->array);
        array_1d->array = NULL;
    }
    array_1d->size = 0;
}

void freeArray_2d(Array_2d *array_2d) {
    if (array_2d->array == NULL) {
        return;
    }

    for (size_t i = 0; i < array_2d->coordinates.y; i++) {
        if (array_2d->array[i] != NULL) {
            free(array_2d->array[i]);
        }
    }

    free(array_2d->array);

    array_2d->array = NULL;
    array_2d->coordinates.x = 0;
    array_2d->coordinates.y = 0;
}
