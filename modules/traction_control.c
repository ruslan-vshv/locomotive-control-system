#include <stdio.h>
#include "traction_control.h"
#include "../core/module.h"
#include "../core/logger.h"
#include "../core/translator.h"
#include "../core/modules_menu.h"

typedef enum {
    AUTO,
    MANUAL
} TractionMode;
TractionMode traction_control_mode = AUTO;

// Register menu items
void traction_control_init() {
    register_menu_item((MenuItem){t("Switch traction control mode"), switch_traction_control_mode});
    printf("Traction control module initialized!\n");
}

// Register module automatically at startup
__attribute__((constructor)) static void module_register() {
    register_module((Module){ "Traction control", traction_control_init });
}

void switch_traction_control_mode() {
    if (traction_control_mode == AUTO) {
        traction_control_mode = MANUAL;
        printf("Traction control module changed to manual!\n");
        log_event("Traction control module changed to manual", "info");
    } else {
        traction_control_mode = AUTO;
        printf("Traction control module changed to automatic!\n");
        log_event("Traction control module changed to automatic", "info");
    }
}
