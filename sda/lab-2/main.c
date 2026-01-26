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
        {1, "Input Array", handleInput},
        {2, "Display Array", handleDisplay},
        {3, "Sort Array", handleSort},
        {4, "Generate", handleGenerateList},
    };

    const int count = sizeof(items) / sizeof(items[0]);

    Menu menu;
    initMenu(&menu, LAB_NAME, items, count);

    runMenu(&menu);

    return 0;
}
