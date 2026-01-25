#include <stdlib.h>
#include "linked_list.h"

List *createList(void) {
    List *list = malloc(sizeof(*list));
    if (!list) {
        return NULL;
    }

    list->head = list->tail = NULL;
    list->size = 0;

    return list;
}

bool isEmpty(const List *list) {
    return (list == NULL || list->head == NULL);
}

void prepend(List *list, Node *node) {
    if (!list || !node) {
        return;
    }

    node->next = list->head;
    list->head = node;
    if (list->tail == NULL) {
        list->tail = node;
    }
    list->size++;
}

void append(List *list, Node *node) {
    if (!list || !node) return;
    node->next = NULL;

    if (list->tail == NULL) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
}

void insertAt(List *list, Node *node, const int index) {
    if (!list || !node || index < 0 || (size_t) index > list->size) return;

    if (index == 0) {
        prepend(list, node);
    } else if ((size_t) index == list->size) {
        append(list, node);
    } else {
        Node *prev = getAt(list, index - 1);
        node->next = prev->next;
        prev->next = node;
        list->size++;
    }
}

Node *popFront(List *list) {
    if (isEmpty(list)) return NULL;
    Node *temp = list->head;
    list->head = temp->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }
    list->size--;
    return temp;
}

Node *removeAt(List *list, const int index) {
    if (isEmpty(list) || index < 0 || (size_t) index >= list->size) return NULL;

    if (index == 0) return popFront(list);

    Node *prev = getAt(list, index - 1);
    Node *toDelete = prev->next;
    prev->next = toDelete->next;

    if (toDelete == list->tail) {
        list->tail = prev;
    }

    list->size--;
    return toDelete;
}

Node *getAt(const List *list, int index) {
    if (!list || index < 0 || (size_t) index >= list->size) return NULL;
    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

Node *getLast(const List *l) {
    if (isEmpty(l)) {
        return NULL;
    }

    return l->tail;
}

void destroyList(List *list, void (*cleanup)(Node *)) {
    if (!list) return;
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        if (cleanup) cleanup(current);
        current = next;
    }
    free(list);
}

void each(List *list, void (*callback)(Node *, int)) {
    if (!list || !callback) return;
    Node *current = list->head;
    int index = 0;
    while (current) {
        Node *next = current->next;
        callback(current, index++);
        current = next;
    }
}

List *filter(List *l, bool (*predicate)(Node *, void *), void *ctx, Node *(*clone)(Node *n)) {
    if (!l || !predicate || !clone) return NULL;
    List *newList = createList();
    Node *curr = l->head;
    while (curr) {
        if (predicate(curr, ctx)) {
            append(newList, clone(curr));
        }
        curr = curr->next;
    }
    return newList;
}

void sortList(List *list, int (*compare)(Node *a, Node *b), void (*swap)(Node *a, Node *b),
              const SortDirection direction) {
    if (!list || list->size < 2 || !compare || !swap) return;

    bool swapped;
    const Node *lastSorted = NULL;

    do {
        swapped = false;
        Node *ptr1 = list->head;

        while (ptr1->next != lastSorted) {
            if ((compare(ptr1, ptr1->next) * direction) > 0) {
                swap(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lastSorted = ptr1;
    } while (swapped);
}
