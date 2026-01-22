#include <stdlib.h>

#include "queue.h"

Queue *createQueue(void) {
    Queue *q = malloc(sizeof(*q));
    if (!q) return NULL;
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

bool isEmpty(const Queue *q) {
    return (q == NULL || q->front == NULL);
}

void enqueue(Queue *q, Node *node) {
    if (!q || !node) return;

    node->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
    q->size++;
}

Node *dequeue(Queue *q) {
    if (isEmpty(q)) return NULL;

    Node *temp = q->front;
    q->front = temp->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    q->size--;
    return temp;
}

Node *queuePeek(const Queue *q) {
    return q == NULL ? NULL : q->front;
}

void destroyQueue(Queue *q, void (*cleanup)(Node *)) {
    if (!q) {
        return;
    }

    Node *current = q->front;
    while (current != NULL) {
        Node *next = current->next;

        if (cleanup != NULL) {
            cleanup(current);
        }

        current = next;
    }

    free(q);
}

Node *getLast(const Queue *q) {
    if (isEmpty(q)) {
        return NULL;
    }

    return q->rear;
}

Node *getAt(const Queue *q, const int index) {
    if (!q || index < 0 || (size_t)index >= q->size) {
        return NULL;
    }

    Node *current = q->front;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current;
}

void each(Queue *q, void (*callback)(Node *, int)) {
    if (!q || !callback) {
        return;
    }

    Node *current = q->front;
    int index = 0;
    while (current != NULL) {
        // We must store 'next' before the callback, just in case
        // the callback deletes the current node (safe iteration).
        Node *next = current->next;
        callback(current, index++);
        current = next;
    }
}
