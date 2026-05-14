#ifndef UTM_LINKED_LIST_H
#define UTM_LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>

#include "sort.h"

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    size_t size;
} List;

List *createList(void);

bool isEmptyList(const List *list);

bool prepend(List *list, void *data);

bool append(List *list, void *data);

bool insertAt(List *list, void *data, int index);

void *popFront(List *list);

void *popBack(List *list);

void *removeAt(List *list, int index);

void *getAt(const List *list, int index);

void *getLast(const List *list);

void destroyList(List *list, void (*cleanup)(void *data));

void each(List *list, void (*callback)(void *data, int index));

List *filter(List *l, bool (*predicate)(void *data, void *ctx), void *ctx, void *(*clone)(void *data));

void sortList(List *list, int (*compare)(const void *a, const void *b), SortDirection direction);

#endif
