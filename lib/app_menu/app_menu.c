#include <stdio.h>

#include "app_menu.h"
#include "application.h"

static void itemIsValid(const MenuItem *item) {
    if (!item->action) {
        throw("Menu item must have a callback provided.", 1);
    }
}

static void eachMenuItems(const Menu *menu, void (*callback)(const MenuItem *item)) {
    if (!callback) {
        return;
    }

    for (int i = 0; i < menu->count; i++) {
        callback(menu->items + i);
    }
}

static void displayMenu(const Menu *menu) {
    clear();

    printf("\n--- %s MENU ---\n", menu->title);
    for (int i = 0; i < menu->count; i++) {
        printf("[%2d] %s\n", menu->items[i].id, menu->items[i].text);
    }
    printf("[ 0] Exit\nSelection > ");
}

static void bye() {
    printf("Bye.");
}

static void runMenuItem(const MenuItem *item) {
    clear();
    printf(">> %s \n\n", item->text);

    item->action();

    printf("\nPress Enter to return to menu...");
    getchar(); // catch the newline from scanf
    getchar(); // wait for actual enter
}

void initMenu(Menu *menu, const char *title, MenuItem *items, const int count) {
    if (!menu || !items || !title || count <= 0) {
        throw("Invalid options for creating menu", 1);
    }

    menu->count = count;
    menu->title = title;
    menu->items = items;

    eachMenuItems(menu, itemIsValid);
}

void runMenu(const Menu *menu) {
    int choice = -1;

    while (choice != 0) {
        displayMenu(menu);

        /*
         * Handle invalid input:
         * If scanf fails (user typed a letter), clear the input buffer
         * to prevent an infinite loop and restart the menu.
         */
        if (scanf("%d", &choice) != 1) {
            do {
            } while (getchar() != '\n');

            continue;
        }

        if (choice == 0) {
            bye();
            break;
        }

        for (int i = 0; i < menu->count; i++) {
            if (menu->items[i].id == choice) {
                if (menu->items[i].action) {
                    runMenuItem(&menu->items[i]);
                }
                break;
            }
        }
    }
}
