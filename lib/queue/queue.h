#ifndef UTM_QUEUE_H
#define UTM_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Node {
    struct Node *next;
} Node;

struct Queue {
    Node *front;
    Node *rear;
    size_t size;
};

typedef struct Queue Queue;

/* Macro to get the struct pointer from the Node pointer */
#define queueEntry(ptr, type, member) \
((type *)((char *)(ptr) - offsetof(type, member)))

Queue *createQueue(void);

bool isEmpty(const Queue *q);

void enqueue(Queue *q, Node *node);

Node *dequeue(Queue *q);

Node *queuePeek(const Queue *q);

void destroyQueue(Queue *q, void (*cleanup)(Node *));

Node *getLast(const Queue *q);

Node *getAt(const Queue *q, int index);

void each(Queue *q, void (*callback)(Node *, int));

#endif /* UTM_QUEUE_H */
