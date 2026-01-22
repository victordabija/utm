#ifndef UTM_SDA_LAB_6_HANDLERS_H
#define UTM_SDA_LAB_6_HANDLERS_H

#include "queue.h"

extern Queue *queue;

typedef struct {
    char model[50];
    char country[30];
    int manufacturingDate;
    int enginePower;
    double cost;
    Node link;
} Car;

void handleCreateList();

void handleInputData();

void handleDisplayList();

void handleSearchElement();

void handleModifyElement();

void handleGetLastAddress();

void handleGetLength();

void handleSwapElements();

void handleSortList();

void handleFreeMemory();

void handleGenerateList();

#endif //UTM_SDA_LAB_6_HANDLERS_H
