/**
 * Laboratory Nr 2
 * Variant 6
 * Victor Dabija
 */

#include "app_menu.h"
#include "handlers.h"

#define LAB_NAME "LABORATORY 2"
#define DEFAULT_CAPACITY 5

Array array;

int main() {
    initArray(&array, DEFAULT_CAPACITY);

    MenuItem items[] = {
        createMenuItem(1, "Input Array", handleInput),
        createMenuItem(2, "Display Array", handleDisplay),
        createMenuItem(3, "Sort Array", handleSort),
        createMenuItem(4, "Generate", handleGenerateList),
    };

    const int count = sizeof(items) / sizeof(items[0]);

    Menu menu;
    initMenu(&menu, LAB_NAME, items, count);

    runMenu(&menu);

    return 0;
}
