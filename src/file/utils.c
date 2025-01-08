#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

void reverse_generations(char *generations)
{
    int len = strlen(generations);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = generations[i];
        generations[i] = generations[len - i - 1];
        generations[len - i - 1] = temp;
    }
}

char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *file_content = (char *)malloc(file_size + 1);
    if (file_content == NULL) {
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(file_content, 1, file_size, file);
    file_content[bytes_read] = '\0';

    fclose(file);
    return file_content;
}

bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}
