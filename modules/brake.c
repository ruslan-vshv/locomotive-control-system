#include <stdio.h>
#include "brake.h"
#include "../core/module.h"
#include "../core/logger.h"
#include "../core/translator.h"
#include "../core/modules_menu.h"

// Register menu items
void brake_init() {
    register_menu_item((MenuItem){t("Activate brakes"), activate_brakes});
    register_menu_item((MenuItem){t("Release brakes"), release_brakes});
    printf("Brake module initialized!\n");
}

// Register module automatically at startup
__attribute__((constructor)) void module_register() {
    register_module((Module){ "Brake", brake_init });
}

void activate_brakes() {
    printf("%s\n", t("Brakes activated"));
    log_event("Brakes activated", "info");
}

void release_brakes() {
    printf("%s\n", t("Brakes released"));
    log_event("Brakes released", "info");
}
