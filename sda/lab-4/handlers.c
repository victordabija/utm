#include "handlers.h"
#include "txt_file.h"
#include "libcar.h"
#include "application.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


static void carToString(const void *record, char *buffer) {
    const Car *car = record;
    sprintf(buffer, "%s|%s|%s|%d|%.2f",
            car->model, car->country, car->manufacturingDate,
            car->enginePower, car->cost);
}

static void carFromString(const char *string, void *record) {
    Car *car = record;
    sscanf(string, "%[^|]|%[^|]|%[^|]|%d|%lf",
           car->model, car->country, car->manufacturingDate,
           &car->enginePower, &car->cost);
}

void handleCreate() {
    const bool success = createFile(FILENAME);

    printf("%s\n", success ? "Successfully created" : "Failed to create");
}

void handleDisplay() {
    size_t returnCount;
    Car *cars = get(FILENAME, &returnCount, 0, sizeof(Car), carFromString);

    if (cars == NULL) {
        printf("Nothing to be displayed.");
        return;
    }

    displayHeader();
    for (size_t i = 0; i < returnCount; i++) {
        displayCar(cars[i], (int) i + 1);
    }

    free(cars);
}

void handleAppend() {
    Car *car = readCar();

    const bool success = appendRecord(FILENAME, car, carToString);
    free(car);

    printf("%s\n", success ? "Successfully inserted." : "Failed to insert.");
}

void handleModify() {
    const int count = (int) getCount(FILENAME);
    if (!count) {
        printf("Nothing to be modified.");
        return;
    }

    handleDisplay();
    const int targetIndex = readInt("\nEnter the index of the car to edit: ", 1, count) - 1;
    Car *car = readCar();

    const bool success = modifyRecord(FILENAME, targetIndex, car, carToString);
    free(car);

    printf("%s\n", success ? "Successfully modified." : "Failed to modify.");
}

void handleSearch() {
    const SearchQuery query = getSearchQuery();
    size_t returnCount;

    Car *cars = searchRecords(FILENAME, sizeof(Car), query.search, (SearchFunc) query.function, carFromString,
                              &returnCount);

    if (!cars) {
        printf("Nothing has been found.");
        return;
    }

    printf("Found %d %s: \n", (int) returnCount, (int) returnCount == 1 ? "car" : "cars");
    for (size_t i = 0; i < returnCount; i++) {
        displayCar(cars[i], (int) i + 1);
    }

    free(cars);
}

void handleSort() {
    const SortQuery query = getSortQuery();

    const bool success = sortFile(FILENAME, sizeof(Car), (CompareFunc) query.function, query.direction, carFromString,
                                  carToString);

    if (success) {
        printf(
            "\nSuccessfully sorted file in %s direction by %s column.",
            getLabelByDirection(query.direction, false),
            getLabelByCompareType(query.type, false)
        );
        return;
    }

    printf("\nSorting failed.");
}


void handleDeleteCar() {
    const int count = (int) getCount(FILENAME);
    if (!count) {
        printf("Nothing to be deleted.");
        return;
    }

    handleDisplay();
    const int targetIndex = readInt("\nEnter the index of the car to delete: ", 1, count) - 1;

    const bool success = deleteRecord(FILENAME, targetIndex);

    printf(success ? "Successfully deleted." : "Failed to delete.");
}


void handleDeleteFile() {
    const bool success = deleteFile(FILENAME);

    printf(success ? "Successfully deleted file %s." : "Failed to delete file %s.", FILENAME);
}
