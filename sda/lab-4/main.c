/**
 * Laboratory Nr 4
 * Variant 4
 * Victor Dabija
 */

#include "handlers.h"
#include "app_menu.h"

#define LAB_NAME "LABORATORY 4"

int main() {
    MenuItem items[] = {
        {1, "Create file", handleCreate},
        {2, "Display All Cars", handleDisplay},
        {3, "Add New Car to File", handleAppend},
        {4, "Modify car Details", handleModify},
        {5, "Search for a car", handleSearch},
        {6, "Sort cars", handleSort},
        {7, "Remove a car", handleDeleteCar},
        {8, "Delete file", handleDeleteFile},
    };

    const int count = sizeof(items) / sizeof(items[0]);

    Menu menu;
    initMenu(&menu, LAB_NAME, items, count);

    runMenu(&menu);

    return 0;
}
