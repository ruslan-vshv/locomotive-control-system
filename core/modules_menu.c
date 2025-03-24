#include <stdio.h>
#include "translator.h"
#include "modules_menu.h"

#define MAX_MENU_ITEMS 40  // Adjust as needed

static int menu_items_count = 0;
static MenuItem menu[MAX_MENU_ITEMS];

void register_menu_item(MenuItem menu_item) {
    if (menu_items_count < MAX_MENU_ITEMS) {
        menu[menu_items_count++] = menu_item;
    } else {
        printf("Menu items limit reached! Cannot register: %s\n", menu_item.name);
    }
}

void render_menu() {
    printf("\n%s:\n", t("Main menu"));
    for (int i = 0; i < menu_items_count; i++) {
        printf("%d. %s\n", i + 1, menu[i].name);
    }
    printf("\n0. %s\n", t("Exit"));
}

void modules_menu() {
    // Show main menu.
    int choice;

    render_menu();

    while (1) {
        printf("%s (0-%d): ", t("Enter your choice"), menu_items_count);
        scanf("%d", &choice);

        if (choice < 0 || choice > menu_items_count) {
            printf("%s\n", t("Invalid choice!"));
            continue;
        }

        if (choice != 0) {
            // Execute the corresponding action.
            menu[choice - 1].action();
            render_menu();
        }
        else {
            break;
        }
    }
}
