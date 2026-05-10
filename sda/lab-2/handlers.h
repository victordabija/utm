#ifndef UTM_SDA_LAB_2_HANDLERS_H
#define UTM_SDA_LAB_2_HANDLERS_H

#include "libcar.h"

/**
 * Wrapper around dynamic array to have size, capacity and data in a structured way and in one place.
 */
typedef struct {
    Car *data;
    int size;
    int capacity;
} Array;

extern Array array;

void handleInput();

void handleDisplay();

void handleSort();

void handleGenerateList();

void initArray(Array *arr, int capacity);

#endif //UTM_SDA_LAB_2_HANDLERS_H
