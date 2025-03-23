#include <stdio.h>
#include "core/translator.h"
#include "core/logger.h"
#include "core/user_interface.h"

void main() {
    user_interface_init();
    log_event("Application closed.", "info");
}
