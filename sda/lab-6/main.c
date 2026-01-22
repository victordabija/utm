#include "app_menu.h"
#include "handlers.h"

#define LAB_NAME "LABORATORY 6"

Queue *queue = NULL;

int main() {
    MenuItem items[] = {
        {1, "Create list in dynamic memory", handleCreateList},
        {2, "Input element info from keyboard", handleInputData},
        {3, "Display list elements on screen", handleDisplayList},
        {4, "Search for an element in list", handleSearchElement},
        {5, "Modify element fields", handleModifyElement},
        {6, "Get address of last element", handleGetLastAddress},
        {7, "Determine list length", handleGetLength},
        {8, "Swap two elements", handleSwapElements},
        {9, "Sort the list", handleSortList},
        {10, "Free list memory (Cleanup)", handleFreeMemory},
        {11, "Generate list", handleGenerateList}
    };

    const int count = sizeof(items) / sizeof(items[0]);

    Menu menu;
    initMenu(&menu, LAB_NAME, items, count);

    runMenu(&menu);

    return 0;
}
