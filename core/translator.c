#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "translator.h"

Translation *load_translations(const char *filename, int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open %s\n", filename);
        *count = 0;
        return NULL;
    }

    // First pass: count lines to determine size
    int num_lines = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strchr(line, ':') != NULL) num_lines++; // Only count valid lines
    }
    rewind(file); // Reset file pointer to start

    // Allocate memory for translations
    Translation *translations = (Translation *)malloc(num_lines * sizeof(Translation));
    if (translations == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        *count = 0;
        return NULL;
    }

    // Second pass: load translations
    int index = 0;
    while (fgets(line, sizeof(line), file) && index < num_lines) {
        line[strcspn(line, "\n")] = 0;
        char *colon = strchr(line, ':');
        if (colon == NULL) continue;

        *colon = '\0';
        strncpy(translations[index].key, line, MAX_KEY - 1);
        translations[index].key[MAX_KEY - 1] = '\0';
        strncpy(translations[index].value, colon + 1, MAX_VALUE - 1);
        translations[index].value[MAX_VALUE - 1] = '\0';
        index++;
    }
    fclose(file);

    *count = index; // Actual number of translations loaded
    return translations;
}

const char *get_translation(Translation *translations, int count, const char *key) {
    for (int i = 0; i < count; i++) {
        if (strcmp(translations[i].key, key) == 0) {
            return translations[i].value;
        }
    }
    return "Translation not found";
}

int choose_language(char *selected_language) {
    char languages[MAX_LANGUAGES][MAX_FILENAME];
    int num_languages = 0;

    // Scan the "translations" folder
    DIR *dir = opendir(TRANSLATIONS_FOLDER);
    if (dir == NULL) {
        printf("Error: Could not open translations directory\n");
        return 0;
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
        printf("Error: No translation files (.txt) found in translations directory\n");
        return 0;
    }

    // Display language options
    printf("Choose a language:\n");
    for (int i = 0; i < num_languages; i++) {
        char display_name[MAX_FILENAME];
        strncpy(display_name, languages[i], MAX_FILENAME - 1);
        display_name[strcspn(display_name, ".")] = '\0'; // Remove .txt
        printf("%d. %s\n", i + 1, display_name);
    }

    // Get user input
    int choice;
    printf("Enter your choice (1-%d): ", num_languages);
    scanf("%d", &choice);

    if (choice < 1 || choice > num_languages) {
        printf("Invalid choice!\n");
        return 0;
    }

    // Construct full path to selected file
    snprintf(selected_language, MAX_FILENAME, "%s%s", TRANSLATIONS_FOLDER, languages[choice - 1]);
    return 1; // Success
}

void free_translations(Translation *translations) {
    if (translations != NULL) {
        free(translations);
    }
}
