#include "module.h"
#include <stdio.h>

#define MAX_MODULES 10  // Adjust as needed

static Module modules[MAX_MODULES];
static int module_count = 0;

void register_module(Module module) {
    if (module_count < MAX_MODULES) {
        modules[module_count++] = module;
    } else {
        printf("Module limit reached! Cannot register: %s\n", module.name);
    }
}

void load_modules() {
    printf("Loading registered modules...\n");
    for (int i = 0; i < module_count; i++) {
        printf("Initializing module: %s\n", modules[i].name);
        modules[i].init();
    }
}
