#include <stdio.h>
#include <time.h>
#include "logger.h"

#define LOGS_FOLDER "../logs/"

void log_event(const char *event) {
    char filename[100];

    // Get current date.
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    snprintf(filename, sizeof(filename), LOGS_FOLDER "locomotive%04d-%02d-%02d.log",
             t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

    // Open log file (create if it doesn't exist).
    FILE *file = fopen(filename, "a");

    // Log event with timestamp.
    fprintf(file, "[%02d:%02d:%02d] %s\n",
            t->tm_hour, t->tm_min, t->tm_sec, event);

    fclose(file);
}
