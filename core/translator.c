#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "translator.h"

#define MAX_KEY 20
#define MAX_VALUE 50
#define MAX_LANGUAGES 10
#define MAX_FILENAME 50
#define TRANSLATIONS_FOLDER "../translations/"

typedef struct {
    char key[MAX_KEY];
    char value[MAX_VALUE];
} Translation;

static Translation *translations = NULL;
static int trans_count = 0;
static int is_initialized = 0;  // Track if translations are loaded

// Language selection logic
static char *select_translation_file() {
    // Load list of languages based on available translation files.
    static char selected_language[MAX_FILENAME];
    char languages[MAX_LANGUAGES][MAX_FILENAME];
    int num_languages = 0;

    DIR *dir = opendir(TRANSLATIONS_FOLDER);
    if (dir == NULL) {
        printf("Error: Could not open translations directory\n");
        return NULL;
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
        return NULL;
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
    printf("Enter your choice (1-%d): ", num_languages);
    scanf("%d", &choice);

    if (choice < 1 || choice > num_languages) {
        printf("Invalid choice!\n");
        return NULL;
    }

    snprintf(selected_language, MAX_FILENAME, "%s%s", TRANSLATIONS_FOLDER, languages[choice - 1]);
    return selected_language;
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
        strncpy(loaded_translations[index].key, line, MAX_KEY - 1);
        loaded_translations[index].key[MAX_KEY - 1] = '\0';
        strncpy(loaded_translations[index].value, colon + 1, MAX_VALUE - 1);
        loaded_translations[index].value[MAX_VALUE - 1] = '\0';
        index++;
    }
    fclose(file);

    *count = index;
    return loaded_translations;
}

// Initialize translator - run language selection logic and load translations for selected lang.
int initialize_translator() {
    char *selected_file = select_translation_file();
    if (selected_file == NULL) {
        return 0;
    }

    translations = load_translations(selected_file, &trans_count);
    if (translations == NULL || trans_count == 0) {
        printf("No translations loaded!\n");
        return 0;
    }

    is_initialized = 1;
    atexit(free_translations); // Register cleanup on exit

    return 1;
}

// Get translation for provided sting.
const char *t(const char *key) {
    if (!is_initialized && !initialize_translator()) {
        return "Translation module failed to initialize";
    }

    for (int i = 0; i < trans_count; i++) {
        if (strcmp(translations[i].key, key) == 0) {
            return translations[i].value;
        }
    }

    // If no translation found - return original string.
    return key;
}

// Free allocated memory for translations list.
void free_translations() {
    if (translations != NULL) {
        free(translations);
    }
}
