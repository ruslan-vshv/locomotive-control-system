#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "translator.h"

#include "logger.h"

#define MAX_STRING 20
#define MAX_TRANSLATION 20
#define MAX_LANGUAGES 10
#define MAX_FILENAME 50
#define TRANSLATIONS_FOLDER "../translations/"

typedef struct {
    char string[MAX_STRING];
    char translation[MAX_TRANSLATION];
} Translation;

static Translation *translations = NULL;
static char *translation_file = NULL;
static int trans_count = 0;
static int is_initialized = 0;  // Track if translations are loaded

// Language selection logic
void select_language() {
    // Load list of languages based on available translation files.
    static char selected_language[MAX_FILENAME];
    char languages[MAX_LANGUAGES][MAX_FILENAME];
    int num_languages = 0;

    DIR *dir = opendir(TRANSLATIONS_FOLDER);
    if (dir == NULL) {
        printf("Error: Could not open translations directory\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && num_languages < MAX_LANGUAGES) {
        if (strstr(entry->d_name, ".txt") != NULL) {
            strncpy(languages[num_languages], entry->d_name, MAX_FILENAME - 1);
            languages[num_languages][MAX_FILENAME - 1] = '\0';
            num_languages++;
        }
    }
    closedir(dir);

    if (num_languages == 0) {
        printf("Error: No translation files found in translations directory\n");
        return;
    }

    // Language selection interface.
    printf("Choose a language:\n");
    for (int i = 0; i < num_languages; i++) {
        char display_name[MAX_FILENAME];
        strncpy(display_name, languages[i], MAX_FILENAME - 1);
        display_name[strcspn(display_name, ".")] = '\0';
        printf("%d. %s\n", i + 1, display_name);
    }

    int choice;

    while (1) {
        printf("Enter your choice (1-%d): ", num_languages);
        scanf("%d", &choice);

        if (choice < 1 || choice > num_languages) {
            printf("Invalid choice!\n");
            continue;
        }
        break;
    }

    // Log selection.
    char chosen_language[50];
    sprintf(chosen_language, "User has chosen %s", languages[choice - 1]);
    log_event(chosen_language, "info");

    snprintf(selected_language, MAX_FILENAME, "%s%s", TRANSLATIONS_FOLDER, languages[choice - 1]);
    translation_file = selected_language;
}

// Load translations for selected language.
static Translation *load_translations(const char *filename, int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open %s\n", filename);
        *count = 0;
        return NULL;
    }

    // Count lines in file to allocate memory.
    int num_lines = 0;
    char line[100];

    while (fgets(line, sizeof(line), file)) {
        if (strchr(line, ':') != NULL) num_lines++;
    }
    rewind(file);

    // Allocate memory for translations to load.
    Translation *loaded_translations = (Translation *)malloc(num_lines * sizeof(Translation));
    if (loaded_translations == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        *count = 0;
        return NULL;
    }

    // Load content of a translation file into Translation struct.
    int index = 0;
    while (fgets(line, sizeof(line), file) && index < num_lines) {
        line[strcspn(line, "\n")] = 0;
        char *colon = strchr(line, ':');
        if (colon == NULL) continue;

        *colon = '\0';
        strncpy(loaded_translations[index].string, line, MAX_STRING - 1);
        loaded_translations[index].string[MAX_STRING - 1] = '\0';
        strncpy(loaded_translations[index].translation, colon + 1, MAX_TRANSLATION - 1);
        loaded_translations[index].translation[MAX_TRANSLATION - 1] = '\0';
        index++;
    }
    fclose(file);

    *count = index;
    return loaded_translations;
}

// Initialize translator - load translations for selected lang.
int initialize_translator() {
    if (translation_file == NULL) {
        // select_language();
    }

    translations = load_translations(translation_file, &trans_count);
    if (translations == NULL || trans_count == 0) {
        printf("No translations loaded!\n");
        return 0;
    }

    is_initialized = 1;
    atexit(free_translations); // Register cleanup on exit

    return 1;
}

// Get translation for provided sting.
const char *t(const char *string) {
    if (!is_initialized && !initialize_translator()) {
        return "Translation module failed to initialize";
    }

    for (int i = 0; i < trans_count; i++) {
        if (strcmp(translations[i].string, string) == 0) {
            return translations[i].translation;
        }
    }

    // If no translation found - return original string.
    return string;
}

// Free allocated memory for translations list.
void free_translations() {
    if (translations != NULL) {
        free(translations);
    }
}
