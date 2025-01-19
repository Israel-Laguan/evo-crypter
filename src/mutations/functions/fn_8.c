#include "../mod.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Insert 'X' after every 3 characters
void fn_8_up(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;
  size_t new_len = len + (len / 3);
  char* new_str = malloc(new_len + 1);
  if (new_str == NULL) {
    exit(1);
  }
  size_t j = 0;
  for (size_t i = 0; i < len; i++) {
    new_str[j++] = str[i];
    if ((i + 1) % 3 == 0 && i != len - 1) {
      new_str[j++] = 'X';
    }
  }
  new_str[j] = '\0';
  strncpy(str, new_str, len + (len / 3) + 1);
  str[new_len] = '\0';
  free(new_str);
}

void fn_8_down(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;
  char* new_str = malloc(len + 1);
  if (new_str == NULL) {
    exit(1);
  }
  size_t j = 0;
  for (size_t i = 0; i < len; i++) {
    if ((i + 1) % 4 != 0 ||
	str[i] !=
	    'X') // Added a condition to only remove 'X' where it was inserted
    {
      new_str[j++] = str[i];
    }
  }
  new_str[j] = '\0';
  strncpy(str, new_str, j + 1);
  str[j] = '\0';
  free(new_str);
}
