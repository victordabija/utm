#ifndef UTM_SDA_LAB_2_HANDLERS_H
#define UTM_SDA_LAB_2_HANDLERS_H

typedef struct {
    char model[50];
    char country[30];
    char manufacturingDate[11];
    int enginePower;
    double cost;
} Car;

/**
 * Wrapper around dynamic array to have size, capacity and data in a structured way and in one place.
 */
typedef struct {
    Car *data;
    int size;
    int capacity;
} Array;

typedef enum {
    SORT_ASC = 1,
    SORT_DESC = -1
} SortDirection;

typedef enum {
    BUBBLE_SORT = 1,
    SELECTION_SORT = 2
} SortMethod;

extern Array array;

void handleInput();

void handleDisplay();

void handleSort();

void handleGenerateList();

void initArray(Array *arr, int capacity);

#endif //UTM_SDA_LAB_2_HANDLERS_H
