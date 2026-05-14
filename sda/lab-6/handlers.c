#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "handlers.h"
#include "linked_list.h"
#include "libcar.h"
#include "application.h"


static void displayCarWrapper(void *data, int index) {
    if (data) {
        displayCar(*(Car *) data, index + 1);
    }
}

static void *cloneCarWrapper(void *data) {
    if (!data) return NULL;

    Car *newCar = malloc(sizeof(Car));
    if (newCar) {
        memcpy(newCar, data, sizeof(Car));
    }
    return newCar;
}


void handleCreateList() {
    if (list) {
        printf("Invalid operation. List is already initialized.\n");
        return;
    }

    list = createList();
    printf(list ? "List is initialized.\n" : "Failed to initialize the list.\n");
}

void handleInputData() {
    if (!list) {
        printf("Please initialize the list.\n");
        return;
    }

    Car *newCar = readCar();
    append(list, newCar);

    printf("\nCar added successfully!\n");
}

void handleDisplayList() {
    if (isEmptyList(list)) {
        printf("Nothing to display.\n");
        return;
    }

    displayHeader();
    each(list, displayCarWrapper);
}

void handleSearchElement() {
    if (isEmptyList(list)) {
        printf("The list is empty.\n");
        return;
    }

    SearchQuery query = getSearchQuery();

    List *filteredList = filter(
        list,
        (bool (*)(void *, void *)) query.function,
        query.search,
        cloneCarWrapper
    );

    if (filteredList != NULL) {
        if (isEmptyList(filteredList)) {
            printf("No results found.\n");
        } else {
            printf("\n--- Search Results (%zu) ---\n", filteredList->size);
            displayHeader();
            each(filteredList, displayCarWrapper);
        }

        destroyList(filteredList, freeCar);
    }
}

void handleModifyElement() {
    if (isEmptyList(list)) {
        printf("The list is empty. Nothing to edit.\n");
        return;
    }

    const int targetIndex = readInt("Enter the index of the car to edit", 1, (int) list->size) - 1;

    Car *oldCar = getAt(list, targetIndex);

    if (!oldCar) {
        printf("Car not found.\n");
        return;
    }

    printf("\n--- Editing ---\n");
    displayHeader();
    displayCar(*oldCar, targetIndex + 1);
    printf("\n");

    Car *newData = readCar();
    memcpy(oldCar, newData, sizeof(Car));
    free(newData);

    printf("\nCar updated successfully!\n");
}

void handleGetLastAddress() {
    if (isEmptyList(list)) {
        printf("Please initialize the list, or add an item.\n");
        return;
    }

    Car *car = getLast(list);
    printf("Address of last element data: %p\n", (void *) car);
}

void handleGetLength() {
    if (!list) {
        printf("Please initialize the list.\n");
        return;
    }

    printf("List length: %zu\n", list->size);
}

void handleSwapElements() {
    if (isEmptyList(list) || list->size < 2) {
        printf("Not enough elements to swap.\n");
        return;
    }

    handleDisplayList();

    const int indexA = readInt("Index of first car: ", 1, (int) list->size) - 1;
    const int indexB = readInt("Index of the second car: ", 1, (int) list->size) - 1;

    if (indexA == indexB) {
        printf("Indexes are the same.\n");
        return;
    }

    Car *carA = getAt(list, indexA);
    Car *carB = getAt(list, indexB);

    if (carA && carB) {
        Car temp;
        memcpy(&temp, carA, sizeof(Car));
        memcpy(carA, carB, sizeof(Car));
        memcpy(carB, &temp, sizeof(Car));

        printf("Cars are swapped.\n");
    }
}

void handleSortList() {
    if (isEmptyList(list) || list->size < 2) {
        printf("Not enough elements to sort.\n");
        return;
    }

    const SortQuery query = getSortQuery();

    sortList(
        list,
        (int (*)(const void *, const void *)) query.function,
        query.direction
    );

    printf("Sort completed!\n");
}

void handleFreeMemory() {
    if (!list) {
        printf("Nothing to destroy.\n");
        return;
    }

    destroyList(list, freeCar);
    list = NULL;

    printf("List is destroyed.\n");
}

void handleGenerateList() {
    if (!list) {
        printf("Please initialize the list first.\n");
        return;
    }

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

        snprintf(newCar->manufacturingDate, sizeof(newCar->manufacturingDate), "%04d-%02d-%02d", year, month, day);

        newCar->enginePower = (float) rand() / (float) RAND_MAX * (600.0f - 100.0f) + 100.0f;
        newCar->cost = (double) rand() / (double) RAND_MAX * (100000.0 - 5000.0) + 5000.0;

        append(list, newCar);
    }

    printf("Done! 10 cars added to the list.\n");
}
