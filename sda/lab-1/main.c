/**
 * Laboratory Nr 1
 * Variant 10
 * Victor Dabija
 */

#include <stdlib.h>
#include <time.h>

#include "app_menu.h"
#include "handlers/handlers_1d.h"
#include "handlers/handlers_2d.h"

#define LAB_NAME "LABORATORY 1"


int main() {
    srand(time(NULL));

    MenuItem items[] = {
        {1, "One-dimensional array", handle_1d, false},
        {2, "Two-dimensional array", handle_2d, false}
    };

    const int count = sizeof(items) / sizeof(MenuItem);

    Menu menu;
    initMenu(&menu, LAB_NAME, items, count);

    runMenu(&menu);

    return 0;
}
