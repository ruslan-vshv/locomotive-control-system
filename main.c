#include <stdio.h>
#include "core/translator.h"
#include "core/logger.h"

void main() {
    printf("%s\n", t("Hello, World!"));

    log_event("Application closed.");
}
