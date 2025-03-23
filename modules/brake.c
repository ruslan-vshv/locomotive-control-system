#include <stdio.h>
#include "brake.h"
#include "../core/logger.h"
#include "../core/translator.h"

void activate_brakes() {
    printf("%s\n", t("Brakes activated"));
    log_event("Brakes activated", "info");
}

void release_brakes() {
    printf("%s\n", t("Brakes released"));
    log_event("Brakes released", "info");
}
