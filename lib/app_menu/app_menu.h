#ifndef UTM_APP_MENU_H
#define UTM_APP_MENU_H
#include <stdbool.h>

typedef void (*MenuCallback)(void);

typedef struct {
    int id;
    const char *text;
    MenuCallback action;
    bool showConfirmation; // confirm with "Enter" when callback executed.
} MenuItem;

typedef struct {
    const char *title;
    MenuItem *items;
    int count;
    int width; // used for indentation
} Menu;

/**
 * Show confirmation by default is true. If you want to set it to false, initialize `MenuItem` by yourself.
 */
MenuItem createMenuItem(int id, const char *title, MenuCallback action);

void initMenu(Menu *menu, const char *title, MenuItem *items, int count);

void runMenu(const Menu *menu);

#endif //UTM_APP_MENU_H
