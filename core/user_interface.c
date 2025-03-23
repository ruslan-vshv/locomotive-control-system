#include <stdio.h>
#include "user_interface.h"
#include <string.h>
#include "translator.h"
#include "../modules/brake.h"

// Array of module action functions
typedef void (*module_action)(void);

typedef struct {
    const char *name;
    module_action action;
} MenuItem;

int menu_size = 2;

// Menu item array containing modules and their respective actions.
MenuItem menu[2];

void render_menu() {
    // Initialize menu items.
    MenuItem temp_menu[] = {
        {t("Activate brakes"), activate_brakes},
        {t("Release brakes"), release_brakes}
    };
    memcpy(menu, temp_menu, sizeof(temp_menu)); // Copy initialized data

    printf("\n%s:\n", t("Main menu"));
    for (int i = 0; i < menu_size; i++) {
        printf("%d. %s\n", i + 1, menu[i].name);
    }

    printf("\n0. %s\n", t("Exit"));
}

void user_interface_init() {
    // Show language selector.
    select_language();

    // Show main menu.
    int choice;

    render_menu();

    while (1) {
        printf("%s (0-%d): ", t("Enter your choice"), menu_size);
        scanf("%d", &choice);

        if (choice < 0 || choice > menu_size) {
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
