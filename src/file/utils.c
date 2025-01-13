#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_generations(char* generations) {
  int len = strlen(generations);
  for (int i = 0; i < len / 2; i++) {
    char temp = generations[i];
    generations[i] = generations[len - i - 1];
    generations[len - i - 1] = temp;
  }
}

bool file_exists(const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file) {
    fclose(file);
    return true;
  }
  return false;
}
