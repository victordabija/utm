#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define DEFAULT_STACK_CAPACITY 16

Stack *createStack(void) {
    Stack *newStack = malloc(sizeof(Stack));

    if (newStack == NULL) {
        return NULL;
    }

    newStack->capacity = DEFAULT_STACK_CAPACITY;
    newStack->topIndex = -1;
    newStack->elements = (void **) malloc(newStack->capacity * sizeof(void *));

    if (newStack->elements == NULL) {
        free(newStack);
        return NULL;
    }

    return newStack;
}

bool pushStack(Stack *stack, void *item) {
    if (stack == NULL) {
        return false;
    }

    /* Resize the stack dynamically if it reaches capacity */
    if (stack->topIndex >= stack->capacity - 1) {
        const int newCapacity = stack->capacity * 2;
        void **newElements = (void **) realloc(stack->elements, newCapacity * sizeof(void *));

        if (newElements == NULL) {
            return false;
        }

        stack->elements = newElements;
        stack->capacity = newCapacity;
    }

    stack->topIndex++;
    stack->elements[stack->topIndex] = item;

    return true;
}

void *popStack(Stack *stack) {
    if (stack == NULL) {
        return NULL;
    }

    if (isEmptyStack(stack)) {
        return NULL;
    }

    void *item = stack->elements[stack->topIndex];
    stack->topIndex--;

    return item;
}

void *peekStack(const Stack *stack) {
    if (stack == NULL) {
        return NULL;
    }

    if (isEmptyStack(stack)) {
        return NULL;
    }

    return stack->elements[stack->topIndex];
}

bool isEmptyStack(const Stack *stack) {
    if (stack == NULL) {
        return true;
    }

    if (stack->topIndex == -1) {
        return true;
    }

    return false;
}

void freeStack(Stack *stack, const CleanupCallback cleanup) {
    if (stack != NULL) {
        if (cleanup != NULL) {
            while (!isEmptyStack(stack)) {
                void *item = popStack(stack);
                cleanup(item);
            }
        }

        if (stack->elements != NULL) {
            free(stack->elements);
        }

        free(stack);
    }
}
