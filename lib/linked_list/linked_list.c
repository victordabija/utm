#include <stdlib.h>

#include "linked_list.h"
#include "sort.h"

List *createList(void) {
    List *list = malloc(sizeof(*list));
    if (!list) {
        return NULL;
    }

    list->head = list->tail = NULL;
    list->size = 0;

    return list;
}

bool isEmptyList(const List *list) {
    return (list == NULL || list->head == NULL);
}

static Node *createNode(void *data) {
    Node *node = malloc(sizeof(*node));
    if (node) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

bool prepend(List *list, void *data) {
    if (!list) {
        return false;
    }

    Node *node = createNode(data);
    if (!node) {
        return false;
    }

    node->next = list->head;
    list->head = node;
    if (list->tail == NULL) {
        list->tail = node;
    }
    list->size++;
    return true;
}

bool append(List *list, void *data) {
    if (!list) {
        return false;
    }

    Node *node = createNode(data);
    if (!node) return false;

    if (list->tail == NULL) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
    return true;
}

bool insertAt(List *list, void *data, const int index) {
    if (!list || index < 0 || (size_t) index > list->size) {
        return false;
    }

    if (index == 0) {
        return prepend(list, data);
    }

    if ((size_t) index == list->size) {
        return append(list, data);
    }

    Node *node = createNode(data);
    if (!node) return false;

    Node *prev = list->head;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }

    node->next = prev->next;
    prev->next = node;
    list->size++;
    return true;
}

void *popFront(List *list) {
    if (isEmptyList(list)) {
        return NULL;
    }

    Node *temp = list->head;
    void *data = temp->data;

    list->head = temp->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }

    free(temp);
    list->size--;

    return data;
}

void *popBack(List *list) {
    if (isEmptyList(list)) { return NULL; }
    if (list->size == 1) { return popFront(list); }

    Node *prev = NULL;
    Node *curr = list->head;

    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    void *data = curr->data;
    prev->next = NULL;
    list->tail = prev;

    free(curr);
    list->size--;

    return data;
}

void *removeAt(List *list, const int index) {
    if (isEmptyList(list) || index < 0 || (size_t) index >= list->size) return NULL;

    if (index == 0) return popFront(list);

    Node *prev = list->head;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }

    Node *toDelete = prev->next;
    void *data = toDelete->data;

    prev->next = toDelete->next;

    if (toDelete == list->tail) {
        list->tail = prev;
    }

    free(toDelete);
    list->size--;

    return data;
}

void *getAt(const List *list, int index) {
    if (!list || index < 0 || (size_t) index >= list->size) return NULL;
    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

void *getLast(const List *list) {
    if (isEmptyList(list)) return NULL;
    return list->tail->data;
}

void destroyList(List *list, void (*cleanup)(void *)) {
    if (!list) return;
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        if (cleanup && current->data) {
            cleanup(current->data);
        }
        free(current);
        current = next;
    }
    free(list);
}

void each(List *list, void (*callback)(void *, int)) {
    if (!list || !callback) return;
    Node *current = list->head;
    int index = 0;
    while (current) {
        callback(current->data, index++);
        current = current->next;
    }
}

List *filter(List *l, bool (*predicate)(void *, void *), void *ctx, void *(*clone)(void *)) {
    if (!l || !predicate) return NULL;
    List *newList = createList();
    if (!newList) return NULL;

    const Node *curr = l->head;
    while (curr) {
        if (predicate(curr->data, ctx)) {
            void *dataToAppend = clone ? clone(curr->data) : curr->data;
            append(newList, dataToAppend);
        }
        curr = curr->next;
    }
    return newList;
}

void sortList(List *list, int (*compare)(const void *a, const void *b), const SortDirection direction) {
    if (!list || list->size < 2 || !compare) return;

    bool swapped;
    const Node *lastSorted = NULL;

    do {
        swapped = false;
        Node *curr = list->head;

        while (curr->next != lastSorted) {
            if ((compare(curr->data, curr->next->data) * direction) > 0) {
                void *temp = curr->data;
                curr->data = curr->next->data;
                curr->next->data = temp;
                swapped = true;
            }
            curr = curr->next;
        }
        lastSorted = curr;
    } while (swapped);
}
