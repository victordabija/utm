#include <stdio.h>

#include "handlers.h"

#include <stdlib.h>
#include <string.h>

#include "application.h"
#include "stack.h"
#include "txt_file.h"
#include "libcar.h"
#include "linked_list.h"

#define STACK_FILENAME "stack.txt"
#define QUEUE_FILENAME "queue.txt"

void handleCreateStack() {
    if (!isEmptyStack(stack)) {
        printf("Stack already exists.");
        return;
    }

    stack = createStack();
    printf("Stack was successfully created.");
}

void handleInputData() {
    if (stack == NULL) {
        printf("Create stack first.");
        return;
    }

    Car *car = readCar();
    pushStack(stack, car);

    printf("Car added successfully.");
}

void handleSaveStackToFile() {
    if (stack == NULL || isEmptyStack(stack)) {
        printf("Create stack first.");
        return;
    }

    // fixme: inefficient, file is opened and closed on each append.
    for (int i = stack->topIndex; i >= 0; i--) {
        appendRecord(STACK_FILENAME, stack->elements[i], carToString);
    }

    printf("Stack saved to %s.\n", STACK_FILENAME);
}

void handleFindMax() {
    if (stack == NULL || isEmptyStack(stack)) {
        printf("Create stack first.");
        return;
    }

    Car *maxCar = stack->elements[0];

    for (int i = 1; i <= stack->topIndex; i++) {
        Car *current = stack->elements[i];
        if (current->enginePower > maxCar->enginePower) {
            maxCar = current;
        }
    }

    printf("Car with the most engine power: %s, %d HP\n", maxCar->model, maxCar->enginePower);
    displayHeader();
    displayCar(*maxCar, 1);
    printf("\n");
}

void handleCopyToQueue() {
    if (stack == NULL || isEmptyStack(stack)) {
        printf("Stack is empty. Nothing to copy.\n");
        return;
    }

    if (queue == NULL) {
        queue = createList();
    }

    for (int i = stack->topIndex; i >= 0; i--) {
        const Car *original = stack->elements[i];

        Car *copy = malloc(sizeof(Car));
        if (copy) {
            memcpy(copy, original, sizeof(Car));
            append(queue, copy);
        }
    }

    printf("Successfully copied %d elements to the queue.\n", stack->topIndex + 1);
}

void handleSaveQueueToFile() {
    if (queue == NULL || isEmptyList(queue)) {
        printf("Queue is empty. Nothing to save.\n");
        return;
    }


    for (int i = 0; i < queue->size; i++) {
        const Car *car = (Car *) getAt(queue, i);
        deleteFile(QUEUE_FILENAME);
        appendRecord(QUEUE_FILENAME, car, carToString);
    }

    printf("Queue saved to %s.\n", QUEUE_FILENAME);
}

void handleGetStackLength() {
    if (stack == NULL || isEmptyStack(stack)) {
        printf("Stack is empty or isn't initialized.");
        return;
    }

    printf("Stack length: %d", stack->topIndex + 1);
}

void handleModifyElement() {
    if (stack == NULL || isEmptyStack(stack)) {
        printf("Stack is empty. Nothing to modify.\n");
        return;
    }

    const int length = stack->topIndex + 1;

    const int index = readInt("Enter index of the car to modify", 1, length) - 1;

    Car *oldCar = stack->elements[index];

    if (!oldCar) {
        printf("Car not found.\n");
        return;
    }

    printf("\n--- Current car ---\n");
    displayHeader();
    displayCar(*oldCar, index + 1);

    printf("\n--- Enter new car ---\n");
    Car *newCar = readCar();

    if (newCar) {
        memcpy(oldCar, newCar, sizeof(Car));
        free(newCar);
        printf("Element modified successfully.\n");
    }
}

void handleFreeStack() {
    if (stack == NULL) {
        printf("Nothing to free");
        return;
    }

    freeStack(stack, freeCar);
    stack = NULL;

    printf("Freed stack successfully.");
}

void handleFreeQueue() {
    if (queue == NULL) {
        printf("Nothing to free in queue.\n");
        return;
    }

    destroyList(queue, freeCar);
    queue = NULL;

    printf("Freed queue successfully.\n");
}
