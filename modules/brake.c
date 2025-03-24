#include <stdio.h>
#include <stdbool.h>
#include "brake.h"
#include "../core/module.h"
#include "../core/logger.h"
#include "../core/translator.h"
#include "../core/modules_menu.h"

int brake_status = false;

// Register menu items
void brake_init() {
    register_menu_item((MenuItem){t("Activate brakes"), activate_brakes});
    register_menu_item((MenuItem){t("Release brakes"), release_brakes});
    printf("Brake module initialized!\n");
}

// Register module automatically at startup
__attribute__((constructor)) static void module_register() {
    register_module((Module){ "Brake", brake_init });
}

void activate_brakes() {
    if (!brake_status) {
        brake_status = true;
        printf("%s\n", t("Brakes activated"));
        log_event("Brakes activated", "info");
    }
    else {
        printf("%s\n", t("Brakes has already been activated"));
    }
}

void release_brakes() {
    if (brake_status) {
        brake_status = false;
        printf("%s\n", t("Brakes released"));
        log_event("Brakes released", "info");
    }
    else {
        printf("%s\n", t("Brakes has not been activated"));
    }
}
