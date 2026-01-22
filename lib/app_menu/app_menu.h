#ifndef UTM_APP_MENU_H
#define UTM_APP_MENU_H
#include <stdbool.h>

typedef void (*MenuCallback)(void);

typedef struct {
    int id;
    const char *text;
    MenuCallback action;
} MenuItem;

typedef struct {
    const char *title;
    MenuItem *items;
    int count;
} Menu;

void initMenu(Menu *menu, const char* title, MenuItem *items, int count);
void runMenu(const Menu *menu);

#endif //UTM_APP_MENU_H