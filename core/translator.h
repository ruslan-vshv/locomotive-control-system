#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#define MAX_KEY 20
#define MAX_VALUE 50
#define MAX_LANGUAGES 10
#define MAX_FILENAME 50
#define TRANSLATIONS_FOLDER "../translations/"

// Struct to store key-value translation pairs
typedef struct {
    char key[MAX_KEY];
    char value[MAX_VALUE];
} Translation;

// Function declarations
Translation *load_translations(const char *filename, int *count);
const char *get_translation(Translation *translations, int count, const char *key);
int choose_language(char *selected_language);
void free_translations(Translation *translations);

#endif