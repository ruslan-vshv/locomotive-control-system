#include <stdio.h>
#include "core/translator.h"
#include "core/logger.h"
#include "core/user_interface.h"
#include "core/autoloader.h"

int modules = 0;

void main() {
    // Show language selector.
    select_language();

    load_modules();

    user_interface_init();

    log_event("Application closed.", "info");
}
