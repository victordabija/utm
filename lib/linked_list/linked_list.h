#ifndef UTM_LINKED_LIST_H
#define UTM_LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Node {
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    size_t size;
} List;

#define listEntry(ptr, type, member) \
((type *)((char *)(ptr) - offsetof(type, member)))

List *createList(void);

bool isEmpty(const List *list);

void prepend(List *list, Node *node);

void append(List *list, Node *node);

void insertAt(List *list, Node *node, int index);

Node *popFront(List *list);

Node *popBack(List *list);

Node *removeAt(List *list, int index);

Node *getAt(const List *list, int index);

Node *getLast(const List *l);

void destroyList(List *list, void (*cleanup)(Node *));

void each(List *list, void (*callback)(Node *, int));

List *filter(List *l, bool (*predicate)(Node *, void *), void *ctx, Node *(*clone)(Node *n));

typedef enum {
    SORT_ASC = 1,
    SORT_DESC = -1
} SortDirection;

void sortList(List *list, int (*compare)(Node *a, Node *b), void (*swap)(Node *a, Node *b), SortDirection direction);

#endif
