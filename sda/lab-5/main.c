/**
 * Laboratory Nr 5
 * Variant 23
 * Victor Dabija
 */

#include <stddef.h>

#include "app_menu.h"
#include "handlers.h"
#include "stack.h"

#define LAB_NAME "LABORATORY 5"

Stack *stack = NULL;
List *queue = NULL;

int main() {
    MenuItem items[] = {
        createMenuItem(1, "Create stack", handleCreateStack),
        createMenuItem(2, "Input car into stack", handleInputData),
        createMenuItem(3, "Save stack data to file", handleSaveStackToFile),
        createMenuItem(4, "Find maximal element by engine power", handleFindMax),
        createMenuItem(5, "Copy data from stack to queue", handleCopyToQueue),
        createMenuItem(6, "Save queue data to file", handleSaveQueueToFile),
        createMenuItem(7, "Determine stack length", handleGetStackLength),
        createMenuItem(8, "Modify car", handleModifyElement),
        createMenuItem(9, "Free stack memory", handleFreeStack),
        createMenuItem(10, "Free queue memory", handleFreeQueue)
    };

    const int count = sizeof(items) / sizeof(MenuItem);

    Menu menu;
    initMenu(&menu, LAB_NAME, items, count);

    runMenu(&menu);

    return 0;
}
