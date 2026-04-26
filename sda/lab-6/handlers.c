#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "linked_list.h"
#include "handlers.h"
#include "application.h"

static Car *getCarByNode(Node *node);

static Car *readCar();

static void destroyCar(Node *node);

static void displayCar(Node *node, int index);

static void swapCars(Node *nodeA, Node *nodeB);

static Node *cloneCar(Node *node);

static int compareByModel(Node *nodeA, Node *nodeB);

static int compareByCountry(Node *nodeA, Node *nodeB);

static int compareByDate(Node *nodeA, Node *nodeB);

static int compareByPower(Node *nodeA, Node *nodeB);

static int compareByCost(Node *nodeA, Node *nodeB);

static bool matchModel(Node *node, void *ctx);

static bool matchCountry(Node *node, void *ctx);

void handleCreateList() {
    if (list) {
        printf("Invalid operation. List is already initialized.");
        return;
    }

    printf("List is initialized.");
    list = createList();
}

void handleInputData() {
    if (!list) {
        printf("Please initialize the list.");
        return;
    }

    Car *newCar = readCar();

    if (newCar == NULL) {
        printf("Failed to initialize the new car.");
        return;
    }

    append(list, &newCar->link);
    free(newCar);
    printf("\nCar added successfully!\n");
}

void handleDisplayList() {
    if (isEmpty(list)) {
        printf("Nothing to display.\n");
        return;
    }

    printf("\n%-3s | %-20s | %-15s | %-10s | %-8s | %-10s\n",
           "ID", "Model", "Country", "Date", "Power", "Cost");
    printf("-------------------------------------------------------------------------------\n");

    each(list, displayCar);
}

void handleSearchElement() {
    typedef struct {
        int index;
        char *text;
        bool (*match)(Node *node, void *ctx);
    } SearchMenuItem;

    const SearchMenuItem items[] = {
        {1, "By Model", matchModel},
        {2, "By Country", matchCountry}
    };

    const int itemsCount = sizeof(items) / sizeof(items[0]);

    printf("Choose sorting criteria:\n");
    for (int i = 0; i < itemsCount; ++i) {
        const SearchMenuItem item = items[i];
        printf("[%d] %-10s\n", item.index, item.text);
    }

    const int choice = readInt("Choice", 1, itemsCount);

    char searchTerm[50];
    readString("Enter search term", searchTerm, 1, 49);

    List *filteredList = filter(
        list,
        items[choice - 1].match,
        searchTerm,
        cloneCar
    );

    if (filteredList != NULL) {
        if (isEmpty(filteredList)) {
            printf("No results found.\n");
        } else {
            printf("\n--- Search Results (%zu) ---\n", filteredList->size);
            each(filteredList, displayCar);
        }

        destroyList(filteredList, destroyCar);
    }
}

void handleModifyElement() {
    if (isEmpty(list)) {
        printf("The list is empty. Nothing to edit.\n");
        return;
    }

    const int targetIndex = readInt("Enter the index of the car to edit", 1, (int) list->size) - 1;

    Node *node = getAt(list, targetIndex);
    Car *oldCar = getCarByNode(node);

    printf("\n--- Editing ---\n");
    displayCar(node, targetIndex);
    printf("\n");

    Car *newData = readCar();
    if (newData) {
        strcpy(oldCar->model, newData->model);
        strcpy(oldCar->country, newData->country);
        strcpy(oldCar->manufacturingDate, newData->manufacturingDate);
        oldCar->enginePower = newData->enginePower;
        oldCar->cost = newData->cost;

        free(newData);
        printf("\nCar updated successfully!\n");
    }
}

void handleGetLastAddress() {
    if (!list) {
        printf("Please initialize the list.");
        return;
    }

    Node *lastNode = getLast(list);
    Car *car = getCarByNode(lastNode);

    printf("Address of last element: %p\n", (void *) car);
}

void handleGetLength() {
    if (!list) {
        printf("Please initialize the list.");
        return;
    }

    printf("List length: %d", (int) list->size);
}

void handleSwapElements() {
    handleDisplayList();

    const int indexA = readInt("Index of first car: ", 1, (int) list->size) - 1;
    const int indexB = readInt("Index of the second car: ", 1, (int) list->size) - 1;

    if (indexA == indexB) {
        printf("Indexes are the same.");
        return;
    }

    Node *nodeA = getAt(list, indexA);
    Node *nodeB = getAt(list, indexB);

    swapCars(nodeA, nodeB);

    printf("Cars are swapped.");
}

void handleSortList() {
    typedef struct {
        int index;
        char *text;

        int (*compare)(Node *a, Node *b);
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

    const SortDirection direction = (dir == 1) ? SORT_ASC : SORT_DESC;

    sortList(
        list,
        items[choice - 1].compare,
        swapCars,
        direction
    );

    printf("Sort completed!\n");
}

void handleFreeMemory() {
    if (!list) {
        printf("Nothing to destroy.");
        return;
    }

    destroyList(list, destroyCar);
    list = NULL;

    printf("List is destroyed.");
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

        append(list, &newCar->link);
    }

    printf("Done! 10 cars added to the list.\n");
}

static void destroyCar(Node *node) {
    Car *car = getCarByNode(node);
    free(car);
}

static Car *readCar() {
    Car *newCar = malloc(sizeof(Car));
    if (newCar == NULL) {
        return NULL;
    }

    char today[11];
    getCurrentDate(today);

    readString("Model", newCar->model, 2, 49);
    readString("Country", newCar->country, 2, 29);

    readDate("Manufacturing Date (YYYY-MM-DD)", newCar->manufacturingDate, "1885-01-01", today);

    newCar->enginePower = readInt("Engine Power (HP)", 0, 1500);
    newCar->cost = readDouble("Cost", 1, 1000000.0);

    return newCar;
}

static void displayCar(Node *node, const int index) {
    if (!node) {
        return;
    }

    Car *c = getCarByNode(node);

    printf("%-3d | %-20s | %-15s | %-10s | %-8d | %-10.2f\n",
           index + 1, c->model, c->country, c->manufacturingDate, c->enginePower, c->cost);
}

static void swapCars(Node *nodeA, Node *nodeB) {
    Car *carA = getCarByNode(nodeA);
    Car *carB = getCarByNode(nodeB);
    Car temp;

    memcpy(&temp, carA, sizeof(Car));
    memcpy(carA, carB, sizeof(Car));
    memcpy(carB, &temp, sizeof(Car));

    Node *tempNext = carA->link.next;
    carA->link.next = carB->link.next;
    carB->link.next = tempNext;
}

static Car *getCarByNode(Node *node) {
    return listEntry(node, Car, link);
}

static Node *cloneCar(Node *node) {
    const Car *oldCar = getCarByNode(node);

    Car *newCar = malloc(sizeof(Car));
    memcpy(newCar, oldCar, sizeof(Car));

    // NOTE: The new copy's link must be cleaned so it doesn't
    // point to the old list's neighbors.
    newCar->link.next = NULL;

    return &newCar->link;
}

/****************** Sorting Start ******************/
static int compareByModel(Node *nodeA, Node *nodeB) {
    const Car *carA = getCarByNode(nodeA);
    const Car *carB = getCarByNode(nodeB);

    return strcmp(carA->model, carB->model);
}

static int compareByCountry(Node *nodeA, Node *nodeB) {
    const Car *carA = getCarByNode(nodeA);
    const Car *carB = getCarByNode(nodeB);

    return strcmp(carA->country, carB->country);
}

static int compareByDate(Node *nodeA, Node *nodeB) {
    const Car *carA = getCarByNode(nodeA);
    const Car *carB = getCarByNode(nodeB);

    return strcmp(carA->manufacturingDate, carB->manufacturingDate);
}

static int compareByPower(Node *nodeA, Node *nodeB) {
    const Car *carA = getCarByNode(nodeA);
    const Car *carB = getCarByNode(nodeB);

    return (carA->enginePower > carB->enginePower) - (carA->enginePower < carB->enginePower);
}

static int compareByCost(Node *nodeA, Node *nodeB) {
    const Car *carA = getCarByNode(nodeA);
    const Car *carB = getCarByNode(nodeB);

    return (carA->cost > carB->cost) - (carA->cost < carB->cost);
}

/****************** Sorting End ******************/

/**************** Searching Start ****************/
bool matchModel(Node *node, void *ctx) {
    const Car *c = getCarByNode(node);
    return strcasestr(c->model, (char *) ctx) != NULL;
}

bool matchCountry(Node *node, void *ctx) {
    const Car *c = getCarByNode(node);
    return strcasestr(c->country, (char *) ctx) != NULL;
}

/**************** Searching End ****************/
