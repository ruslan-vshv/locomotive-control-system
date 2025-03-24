#include <stdio.h>
#include <stdbool.h>
#include "compressor_unit.h"
#include "../core/module.h"
#include "../core/logger.h"
#include "../core/translator.h"
#include "../core/modules_menu.h"

int compressor_unit_status = false;

// Register menu items
void compressor_unit_init() {
    register_menu_item((MenuItem){t("Activate compressor unit"), activate_compressor_unit});
    printf("Compressor unit module initialized!\n");
}

// Register module automatically at startup
__attribute__((constructor)) static void module_register() {
    register_module((Module){ "Compressor Unit", compressor_unit_init });
}

void activate_compressor_unit() {
    if (!compressor_unit_status) {
        compressor_unit_status = true;
        printf("%s\n", t("Compressor unit activated"));
        log_event("Compressor unit activated", "info");
    }
    else {
        printf("%s\n", t("Compressor unit has already been activated"));
    }
}
