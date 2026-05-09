#include "app_menu.h"
#include "handlers.h"

#define LAB_NAME "LABORATORY 6"

List *list = NULL;

int main() {
    MenuItem items[] = {
        createMenuItem(1, "Create list in dynamic memory", handleCreateList),
        createMenuItem(2, "Input element info from keyboard", handleInputData),
        createMenuItem(3, "Display list elements on screen", handleDisplayList),
        createMenuItem(4, "Search for an element in list", handleSearchElement),
        createMenuItem(5, "Modify element fields", handleModifyElement),
        createMenuItem(6, "Get address of last element", handleGetLastAddress),
        createMenuItem(7, "Determine list length", handleGetLength),
        createMenuItem(8, "Swap two elements", handleSwapElements),
        createMenuItem(9, "Sort the list", handleSortList),
        createMenuItem(10, "Free list memory (Cleanup)", handleFreeMemory),
        createMenuItem(11, "Generate list", handleGenerateList)
    };

    const int count = sizeof(items) / sizeof(items[0]);

    Menu menu;
    initMenu(&menu, LAB_NAME, items, count);

    runMenu(&menu);

    return 0;
}
