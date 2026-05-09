#include <stdio.h>
#include <math.h>

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
        printf("[%*d] %s\n", menu->width, menu->items[i].id, menu->items[i].text);
    }
    printf("[%*d] Exit\n", menu->width, 0);
}

static void bye() {
    printf("Bye.");
}

static void runMenuItem(const MenuItem *item) {
    clear();
    printf(">> %s \n\n", item->text);

    item->action();

    if (item->showConfirmation) {
        printf("\nPress Enter to return to menu...");
        getchar(); // catch the newline from scanf
    }
}

MenuItem createMenuItem(const int id, const char *title, const MenuCallback action) {
    return (MenuItem){
        .id = id,
        .text = title,
        .action = action,
        .showConfirmation = true
    };
}

void initMenu(Menu *menu, const char *title, MenuItem *items, const int count) {
    if (!menu || !items || !title || count <= 0) {
        throw("Invalid options for creating menu", 1);
    }

    menu->count = count;
    menu->title = title;
    menu->items = items;

    const int maxId = menu->items[menu->count - 1].id;
    menu->width = (maxId > 0) ? (int) log10(maxId) + 1 : 1;

    eachMenuItems(menu, itemIsValid);
}

void runMenu(const Menu *menu) {
    int choice = -1;

    while (choice != 0) {
        displayMenu(menu);

        choice = readInt("Selection > ", 0, menu->count);

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
