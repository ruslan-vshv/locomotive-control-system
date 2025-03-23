#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logger.h"

#define LOGS_FOLDER "../logs/"

// Log events, 3 types of events available - ERROR, WARNING and INFO.
void log_event(const char *event, const char *event_type) {
    char filename[100];

    // Get current date.
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    snprintf(filename, sizeof(filename), LOGS_FOLDER "locomotive%04d-%02d-%02d.log",
             t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

    // Open log file (create if it doesn't exist).
    FILE *file = fopen(filename, "a");

    // Validate event type, default to "INFO"
    const char *type;
    if (strcmp(event_type, "error") == 0) {
        type = "ERROR";
    } else if (strcmp(event_type, "warning") == 0) {
        type = "WARNING";
    } else {
        type = "INFO"; // Default
    }

    // Log event with timestamp and type.
    fprintf(file, "[%02d:%02d:%02d] [%s] %s\n",
            t->tm_hour, t->tm_min, t->tm_sec, type, event);

    fclose(file);
}
