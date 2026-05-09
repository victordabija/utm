/**
 * Laboratory Nr 3
 * Variant 6
 * Victor Dabija
 */

#include "app_menu.h"
#include "handlers.h"

#define LAB_NAME "LABORATORY 3"


int main() {
    MenuItem items[] = {
        createMenuItem(1, "Create file", handleCreate),
        createMenuItem(2, "Display All Cars", handleDisplay),
        createMenuItem(3, "Add New Car to File", handleAppend),
        createMenuItem(4, "Modify car Details", handleModify),
        createMenuItem(5, "Search for a car", handleSearch),
        createMenuItem(6, "Sort cars", handleSort),
        createMenuItem(7, "Remove a car", handleDeleteCar),
        createMenuItem(8, "Delete file", handleDeleteFile),
    };

    const int count = sizeof(items) / sizeof(items[0]);

    Menu menu;
    initMenu(&menu, LAB_NAME, items, count);

    runMenu(&menu);

    return 0;
}
