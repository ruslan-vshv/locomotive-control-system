#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#define MAX_KEY 20
#define MAX_VALUE 50
#define MAX_LANGUAGES 10
#define MAX_FILENAME 50
#define TRANSLATIONS_FOLDER "../translations/"

// Function declarations
const char *t(const char *key);
void free_translations();

#endif
