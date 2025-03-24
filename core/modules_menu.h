#ifndef MODULES_MENU_H
#define MODULES_MENU_H

// Array of module action functions
typedef void (*module_action)(void);
typedef struct {
    const char *name;
    module_action action;
} MenuItem;

void register_menu_item(MenuItem menu_item);
void modules_menu();

#endif //MODULES_MENU_H
