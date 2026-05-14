#include "libcar.h"
#include "application.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const CompareMethod compareMethods[] = {
    {BY_MODEL, compareByModel},
    {BY_COUNTRY, compareByCountry},
    {BY_DATE, compareByDate},
    {BY_POWER, compareByPower},
    {BY_COST, compareByCost}
};

const SearchMethod searchMethods[] = {
    {BY_MODEL, matchByModel},
    {BY_COUNTRY, matchByCountry},
};

int getCompareMethodsCount();

int getSearchMethodsCount();

void showCompareMethods();

void showSearchMethods();

SortDirection getSortDirection();

void displayCar(Car car, const int index) {
    printf("%-3d | %-20s | %-15s | %-10s | %-8d | %-10.2f\n",
           index, car.model, car.country, car.manufacturingDate, car.enginePower, car.cost);
}

void displayHeader() {
    printf("\n%-3s | %-20s | %-15s | %-10s | %-8s | %-10s\n",
           "ID", "Model", "Country", "Date", "Power", "Cost");
    printf("-------------------------------------------------------------------------------\n");
}

Car *readCar() {
    Car *car = malloc(sizeof(Car));

    char today[11];
    getCurrentDate(today);

    readString("Model", car->model, 2, 49);
    readString("Country", car->country, 2, 29);

    readDate("Manufacturing Date (YYYY-MM-DD)", car->manufacturingDate, FIRST_CAR_MADE_DATE, today);

    car->enginePower = readInt("Engine Power (HP)", 0, 1500);
    car->cost = readDouble("Cost", 1, 1000000.0);

    return car;
}

// SORT
int compareByModel(const Car *a, const Car *b) {
    return strcmp(a->model, b->model);
}

int compareByCountry(const Car *a, const Car *b) {
    return strcmp(a->country, b->country);
}

int compareByDate(const Car *a, const Car *b) {
    return strcmp(a->manufacturingDate, b->manufacturingDate);
}

int compareByPower(const Car *a, const Car *b) {
    return (a->enginePower > b->enginePower) - (a->enginePower < b->enginePower);
}

int compareByCost(const Car *a, const Car *b) {
    return (a->cost > b->cost) - (a->cost < b->cost);
}


// SEARCH
bool matchByModel(const Car *record, const void *search) {
    return strcasestr(record->model, (char *) search) != NULL;
}

bool matchByCountry(const Car *record, const void *search) {
    return strcasestr(record->country, (char *) search) != NULL;
}

int getCompareMethodsCount() {
    return (int) sizeof(compareMethods) / sizeof(CompareMethod);
}

int getSearchMethodsCount() {
    return (int) sizeof(searchMethods) / sizeof(SearchMethod);
}

void showCompareMethods() {
    for (int i = 0; i < getCompareMethodsCount(); ++i) {
        const CompareMethod method = compareMethods[i];
        printf("[%d] %-10s\n", i + 1, getLabelByCompareType(method.type, true));
    }
}

void showSearchMethods() {
    for (int i = 0; i < getSearchMethodsCount(); ++i) {
        const SearchMethod method = searchMethods[i];
        printf("[%d] %-10s\n", i + 1, getLabelByCompareType(method.type, true));
    }
}

SearchQuery getSearchQuery() {
    SearchQuery query;

    printf("Choose searching criteria: \n");
    showSearchMethods();
    const int choice = readInt("Choice", 1, getSearchMethodsCount()) - 1;

    // Get the search text
    readString("Enter search: ", query.search, 1, SEARCH_STRING_LIMIT);

    const SearchMethod searchMethod = searchMethods[choice];
    query.function = searchMethod.function;
    query.type = searchMethod.type;

    return query;
}

SortDirection getSortDirection() {
    printf("\nChoose sorting direction:\n");
    printf("[1] Ascending\n");
    printf("[2] Descending\n");
    const int direction = readInt("Choice", 1, 2);

    return direction == 1 ? ASCENDING : DESCENDING;
}

SortQuery getSortQuery() {
    SortQuery query;

    printf("Choose sorting column: \n");
    showCompareMethods();
    const int choice = readInt("Choice", 1, getCompareMethodsCount()) - 1;

    const CompareMethod compareMethod = compareMethods[choice];
    query.function = compareMethod.function;
    query.type = compareMethod.type;
    query.direction = getSortDirection();

    return query;
}

char *getLabelByCompareType(const CompareType type, const bool capitalize) {
    static char label[10];

    switch (type) {
        case BY_MODEL:
            strcpy(label, "model");
            break;
        case BY_COUNTRY:
            strcpy(label, "country");
            break;
        case BY_DATE:
            strcpy(label, "date");
            break;
        case BY_POWER:
            strcpy(label, "power");
            break;
        case BY_COST:
            strcpy(label, "cost");
            break;
        default:
            throw("Unexpected case.", 1);
    }

    if (capitalize) {
        label[0] = (char) toupper((unsigned char) label[0]);
    }

    return label;
}

void carToString(const void *record, char *buffer) {
    const Car *car = record;
    sprintf(buffer, "%s|%s|%s|%d|%.2f",
            car->model, car->country, car->manufacturingDate,
            car->enginePower, car->cost);
}

void carFromString(const char *string, void *record) {
    Car *car = record;
    sscanf(string, "%[^|]|%[^|]|%[^|]|%d|%lf",
           car->model, car->country, car->manufacturingDate,
           &car->enginePower, &car->cost);
}

void freeCar(void *record) {
    Car *car = record;
    free(car);
}
