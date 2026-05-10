#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "handlers.h"
#include "application.h"
#include "libcar.h"
#include "sort.h"

static void addElement(Array *arr, const Car *car);

static void sort(const Array *arr, int (*compare)(const Car *a, const Car *b), SortMethod method,
                 SortDirection direction);

static void bubbleSort_local(const Array *arr, int (*compare)(const Car *a, const Car *b), SortDirection direction);

static void selectionSort_local(const Array *arr, int (*compare)(const Car *a, const Car *b), SortDirection direction);

void handleInput() {
    Car *car = readCar();
    addElement(&array, car);

    free(car);
}

void handleDisplay() {
    if (array.size == 0) {
        printf("Array is empty.");
        return;
    }

    displayHeader();
    for (int i = 0; i < array.size; i++) {
        displayCar(*(array.data + i), i);
    }
}

void handleSort() {
    typedef struct {
        int index;
        char *text;

        int (*compare)(const Car *a, const Car *b);
    } SortMenuItem;

    const SortMenuItem items[] = {
        {1, "Model", compareByModel},
        {2, "Country", compareByCountry},
        {3, "Power", compareByPower},
        {4, "Cost", compareByCost},
        {5, "Date", compareByDate},
    };

    const int itemsCount = sizeof(items) / sizeof(items[0]);

    printf("Choose sorting criteria:\n");
    for (int i = 0; i < itemsCount; i++) {
        const SortMenuItem item = items[i];
        printf("[%d] %-10s\n", item.index, item.text);
    }

    const int choice = readInt("Choice", 1, itemsCount);

    printf("\nChoose sorting direction:\n");
    printf("[1] Ascending\n");
    printf("[2] Descending\n");
    const int dir = readInt("Choice", 1, 2);

    const SortDirection direction = (dir == 1) ? ASCENDING : DESCENDING;

    printf("\nChoose sorting method:\n");
    printf("[1] Bubble sort\n");
    printf("[2] Selection sort\n");
    const int method = readInt("Choice", 1, 2) == 1 ? BUBBLE_SORT : SELECTION_SORT;

    sort(&array, items[choice - 1].compare, method, direction);
}

void initArray(Array *arr, const int capacity) {
    arr->size = 0;
    arr->capacity = capacity;
    arr->data = (Car *) malloc(arr->capacity * sizeof(Car));
}

static void addElement(Array *arr, const Car *car) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->data = (Car *) realloc(arr->data, arr->capacity * sizeof(Car));
    }

    arr->data[arr->size] = *car;
    arr->size++;
}

static void sort(const Array *arr, int (*compare)(const Car *a, const Car *b), const SortMethod method,
                 const SortDirection direction) {
    switch (method) {
        case BUBBLE_SORT:
            bubbleSort_local(arr, compare, direction);
            break;
        case SELECTION_SORT:
            selectionSort_local(arr, compare, direction);
            break;
        default:
            throw("Selected sort method does not exist", -1);
    }
}

static void bubbleSort_local(const Array *arr, int (*compare)(const Car *a, const Car *b), const SortDirection direction) {
    if (arr->size < 2) {
        return;
    }

    for (int i = 0; i < arr->size - 1; i++) {
        for (int j = 0; j < arr->size - i - 1; j++) {
            const int cmp = compare(&arr->data[j], &arr->data[j + 1]);

            if ((direction == ASCENDING && cmp > 0) || (direction == DESCENDING && cmp < 0)) {
                const Car temp = arr->data[j];
                arr->data[j] = arr->data[j + 1];
                arr->data[j + 1] = temp;
            }
        }
    }
}

static void selectionSort_local(const Array *arr, int (*compare)(const Car *a, const Car *b), const SortDirection direction) {
    if (arr->size < 2) return;

    for (int i = 0; i < arr->size - 1; i++) {
        int targetIdx = i;
        for (int j = i + 1; j < arr->size; j++) {
            const int cmp = compare(&arr->data[j], &arr->data[targetIdx]);

            if ((direction == ASCENDING && cmp < 0) || (direction == DESCENDING && cmp > 0)) {
                targetIdx = j;
            }
        }

        if (targetIdx != i) {
            const Car temp = arr->data[i];
            arr->data[i] = arr->data[targetIdx];
            arr->data[targetIdx] = temp;
        }
    }
}

void handleGenerateList() {
    const char *models[] = {
        "Tesla Model 3", "BMW M4", "Audi A6", "Toyota Camry", "Ford Mustang", "Mercedes S-Class", "Honda Civic",
        "Porsche 911"
    };
    const char *countries[] = {"USA", "Germany", "Japan", "Italy", "UK", "France", "South Korea"};

    const int modelsCount = sizeof(models) / sizeof(models[0]);
    const int countriesCount = sizeof(countries) / sizeof(countries[0]);

    srand((unsigned int) time(NULL));

    printf("\nGenerating 10 random cars...\n");

    for (int i = 0; i < 10; i++) {
        Car *newCar = malloc(sizeof(Car));
        if (!newCar) break;

        snprintf(newCar->model, sizeof(newCar->model), "%s", models[rand() % modelsCount]);
        snprintf(newCar->country, sizeof(newCar->country), "%s", countries[rand() % countriesCount]);

        const int year = rand() % (2026 - 2000 + 1) + 2000;
        const int month = rand() % 12 + 1;
        const int day = rand() % 28 + 1;

        sprintf(newCar->manufacturingDate, "%04d-%02d-%02d", year, month, day);

        newCar->enginePower = (float) rand() / (float) RAND_MAX * (600.0f - 100.0f) + 100.0f;

        newCar->cost = (double) rand() / (double) RAND_MAX * (100000.0 - 5000.0) + 5000.0;

        addElement(&array, newCar);
    }

    printf("Done! 10 cars added to the list.\n");
}
