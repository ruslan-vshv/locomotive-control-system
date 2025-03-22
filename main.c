#include <stdio.h>
#include "core/translator.h"

int main() {
    char selected_language[MAX_FILENAME];
    int trans_count;

    // Choose language
    if (!choose_language(selected_language)) {
        return 1;
    }

    // Load translations
    Translation *translations = load_translations(selected_language, &trans_count);
    if (translations == NULL || trans_count == 0) {
        printf("No translations loaded!\n");
        free_translations(translations);
        return 1;
    }

    // Display the "greeting" translation
    const char *key = "greeting";
    printf("%s\n", get_translation(translations, trans_count, key));

    // Clean up
    free_translations(translations);
    return 0;
}
