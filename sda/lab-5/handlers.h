#ifndef UTM_SDA_LAB_5_HANDLERS_H
#define UTM_SDA_LAB_5_HANDLERS_H

#include "linked_list.h"
#include "stack.h"

extern Stack *stack;
extern List *queue;

void handleCreateStack();

void handleInputData();

void handleSaveStackToFile();

void handleFindMax();

void handleCopyToQueue();

void handleSaveQueueToFile();

void handleGetStackLength();

void handleModifyElement();

void handleFreeStack();

void handleFreeQueue();

#endif //UTM_SDA_LAB_5_HANDLERS_H
