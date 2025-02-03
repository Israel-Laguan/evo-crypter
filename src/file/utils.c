#include "utils.h"
#include <errno.h>

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
  } else {
    // Check if the error was specifically because the file doesn't exist
    if (errno == ENOENT) {
      return false; // File not found
    }
    // Handle other potential errors (e.g., permissions)
    fprintf(stderr, "Error: Could not open file '%s': %s\n", filename,
	    strerror(errno));
    return false; // Treat other errors as file not existing for now
  }
}
