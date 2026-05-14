#ifndef UTM_STACK_H
#define UTM_STACK_H

#include <stdbool.h>

typedef struct {
    void **elements;
    int capacity;
    int topIndex;
} Stack;

typedef void (*CleanupCallback)(void *);

Stack *createStack(void);

bool pushStack(Stack *stack, void *item);

void *popStack(Stack *stack);

void *peekStack(const Stack *stack);

bool isEmptyStack(const Stack *stack);

void freeStack(Stack *stack, CleanupCallback cleanup);
#endif //UTM_STACK_H
