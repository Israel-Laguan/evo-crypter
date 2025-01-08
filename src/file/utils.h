#ifndef EVO_FILE_UTILS_H
#define EVO_FILE_UTILS_H

#include <stdbool.h>
#include <stdio.h>

void reverse_generations(char *generations);
char *read_file(const char *filename);
bool file_exists(const char *filename);

#endif // EVO_FILE_UTILS_H