#ifndef UTM_ARRAY_H
#define UTM_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t x;
    size_t y;
} Sizes_2d;

typedef struct {
    int *array;
    size_t size;
} Array_1d;

typedef struct {
    int **array;
    Sizes_2d coordinates;
} Array_2d;

void inputArray_1d(Array_1d *array_1d);

void inputArray_2d(Array_2d *array_2d);

void displayArray_1d(const Array_1d *array_1d);

void displayArray_2d(const Array_2d *array_2d);

/**
 * Has to be seeded in particular.
 */
void randomFillArray_1d(Array_1d *array_1d);

/**
 * Has to be seeded in particular.
 */
void randomFillArray_2d(Array_2d *array_2d);

bool isEmpty_1d(const Array_1d *array_1d);

bool isEmpty_2d(const Array_2d *array_2d);

void freeArray_1d(Array_1d *array_1d);

void freeArray_2d(Array_2d *array_2d);

#endif //UTM_ARRAY_H
