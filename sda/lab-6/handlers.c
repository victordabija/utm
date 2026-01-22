#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "queue.h"
#include "handlers.h"
#include "application.h"

static void destroyCar(Node *node);

static void displayCar(Node *node, int index);

static void swapCars(Node *nodeA, Node *nodeB);

void handleCreateList() {
    if (queue) {
        printf("Invalid operation. Queue is already initialized.");
        return;
    }

    printf("Queue is initialized.");
    queue = createQueue();
}

void handleInputData() {
    if (!queue) {
        printf("Please initialize the queue.");
        return;
    }

    Car *newCar = malloc(sizeof(Car));

    printf("Model: ");
    scanf(" %49[^\n]", newCar->model);

    printf("Country: ");
    scanf(" %29[^\n]", newCar->country);

    printf("Manufacturing Year: ");
    // FIXME: proper date formatting
    scanf("%d", &newCar->manufacturingDate);

    newCar->enginePower = readInt("Engine Power (HP)", 0, 1500);

    newCar->cost = readDouble("Cost: ", 1, INFINITY);

    enqueue(queue, &newCar->link);

    printf("\nCar added successfully!\n");
}

void handleDisplayList() {
    if (isEmpty(queue)) {
        printf("Nothing to display.\n");
        return;
    }

    printf("\n%-3s | %-20s | %-15s | %-5s | %-8s | %-10s\n",
           "ID", "Model", "Country", "Year", "Power", "Cost");
    printf("--------------------------------------------------------------------------\n");

    each(queue, displayCar);
}

void handleSearchElement() { printf("\n>> Operation: Searching...\n"); }

void handleModifyElement() { printf("\n>> Operation: Modifying...\n"); }

void handleGetLastAddress() {
    if (!queue) {
        printf("Please initialize the queue.");
        return;
    }

    Node *lastNode = getLast(queue);
    Car *car = queueEntry(lastNode, Car, link);

    printf("Address of last element: %p\n", (void *) car);
}

void handleGetLength() {
    if (!queue) {
        printf("Please initialize the queue.");
        return;
    }

    printf("Queue length: %d", (int) queue->size);
}

void handleSwapElements() {
    handleDisplayList();

    const int indexA = readInt("Index of first car: ", 1, (int) queue->size) - 1;
    const int indexB = readInt("Index of the second car: ", 1, (int) queue->size) - 1;

    if (indexA == indexB) {
        printf("Indexes are the same.");
        return;
    }

    Node *nodeA = getAt(queue, indexA);
    Node *nodeB = getAt(queue, indexB);

    swapCars(nodeA, nodeB);

    printf("Cars are swapped.");
}

void handleSortList() { printf("\n>> Operation: Sorting...\n"); }

void handleFreeMemory() {
    if (!queue) {
        printf("Nothing to destroy.");
        return;
    }

    destroyQueue(queue, destroyCar);
    queue = NULL;

    printf("Queue is destroyed.");
}

void handleGenerateList() {
    // Arrays of data to pick from
    const char *models[] = {
        "Tesla Model 3", "BMW M4", "Audi A6", "Toyota Camry", "Ford Mustang", "Mercedes S-Class", "Honda Civic",
        "Porsche 911"
    };
    const char *countries[] = {"USA", "Germany", "Japan", "Italy", "UK", "France", "South Korea"};

    int modelsCount = sizeof(models) / sizeof(models[0]);
    int countriesCount = sizeof(countries) / sizeof(countries[0]);

    // Seed the random generator so we get different results every time
    srand((unsigned int) time(NULL));

    printf("\nGenerating 10 random cars...\n");

    for (int i = 0; i < 10; i++) {
        Car *newCar = malloc(sizeof(Car));
        if (!newCar) break;

        // Pick random strings
        snprintf(newCar->model, sizeof(newCar->model), "%s", models[rand() % modelsCount]);
        snprintf(newCar->country, sizeof(newCar->country), "%s", countries[rand() % countriesCount]);

        // Generate numeric values
        // rand() % (max - min + 1) + min
        newCar->manufacturingDate = rand() % (2026 - 2000 + 1) + 2000;

        // Random float: (float)rand() / (float)(RAND_MAX) * (max - min) + min
        newCar->enginePower = (float) rand() / (float) RAND_MAX * (600.0f - 100.0f) + 100.0f;

        // Random double
        newCar->cost = (double) rand() / (double) RAND_MAX * (100000.0 - 5000.0) + 5000.0;

        // Enqueue into our intrusive queue
        enqueue(queue, &newCar->link);
    }

    printf("Done! 10 cars added to the queue.\n");
}

static void destroyCar(Node *node) {
    Car *car = queueEntry(node, Car, link);
    free(car);
}

static void displayCar(Node *node, const int index) {
    if (!node) {
        return;
    }

    Car *c = queueEntry(node, Car, link);

    printf("%-3d | %-20s | %-15s | %-5d | %-8d | %-10.2f\n",
           index + 1, c->model, c->country, c->manufacturingDate, c->enginePower, c->cost);
}

static void swapCars(Node *nodeA, Node *nodeB) {
    Car *carA = queueEntry(nodeA, Car, link);
    Car *carB = queueEntry(nodeB, Car, link);
    Car temp;

    memcpy(&temp, carA, sizeof(Car));
    memcpy(carA, carB, sizeof(Car));
    memcpy(carB, &temp, sizeof(Car));

    Node *tempNext = carA->link.next;
    carA->link.next = carB->link.next;
    carB->link.next = tempNext;
}
