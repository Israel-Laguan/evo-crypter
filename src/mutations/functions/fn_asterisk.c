#include "../mod.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dictionary Move (shift by 5, using a small example dictionary)
const char* dictionary[] = {"apple", "banana", "orange", "grape",  "melon",
			    "dog",   "cat",    "bird",	 "fish",   "elephant",
			    "red",   "green",  "blue",	 "yellow", "purple"};
const int DICT_SIZE = sizeof(dictionary) / sizeof(dictionary[0]);

void fn_asterisk_up(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;

  // Allocate a larger buffer to handle potential expansion.
  char* result = malloc(len * 2 + 1);
  if (result == NULL) {
    perror("Memory allocation failed");
    exit(1);
  }
  result[0] = '\0';

  char* saveptr;
  char* word = strtok_r(str, " ", &saveptr);
  size_t result_len = 0;

  while (word != NULL) {
    int i;
    for (i = 0; i < DICT_SIZE; i++) {
      if (strcasecmp(word, dictionary[i]) == 0) { // Case-insensitive comparison
	int n = snprintf(result + result_len, len * 2 + 1 - result_len, "%s ",
			 dictionary[(i + 5) % DICT_SIZE]);
	if (n < 0 || (size_t)n >= len * 2 + 1 - result_len) {
	  fprintf(stderr, "snprintf failed or buffer too small\n");
	  free(result);
	  exit(1);
	}
	result_len += n;
	break;
      }
    }
    if (i == DICT_SIZE) {
      // Word not in dictionary so we add it as is
      int n =
	  snprintf(result + result_len, len * 2 + 1 - result_len, "%s ", word);
      if (n < 0 || (size_t)n >= len * 2 + 1 - result_len) {
	fprintf(stderr, "snprintf failed or buffer too small\n");
	free(result);
	exit(1);
      }
      result_len += n;
    }
    word = strtok_r(NULL, " ", &saveptr);
  }

  if (result_len > 0 && result[result_len - 1] == ' ') {
    result[result_len - 1] = '\0';
  }

  // Ensure null-termination and copy back to original string
  if (result_len < len * 2 + 1) {
    result[result_len] = '\0';
  } else {
    result[len * 2] = '\0';
  }

  strncpy(str, result, result_len + 1);
  str[result_len] = '\0';
  free(result);
}

void fn_asterisk_down(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;

  char* result = malloc(len * 2 + 1);
  if (result == NULL) {
    perror("Memory allocation failed");
    exit(1);
  }
  result[0] = '\0';
  char* saveptr;
  char* word = strtok_r(str, " ", &saveptr);
  size_t result_len = 0;

  while (word != NULL) {
    int i;
    for (i = 0; i < DICT_SIZE; i++) {
      if (strcasecmp(word, dictionary[i]) == 0) {
	int n = snprintf(result + result_len, len * 2 + 1 - result_len, "%s ",
			 dictionary[(i - 5 + DICT_SIZE) % DICT_SIZE]);
	if (n < 0 || (size_t)n >= len * 2 + 1 - result_len) {
	  fprintf(stderr, "snprintf failed or buffer too small\n");
	  free(result);
	  exit(1);
	}
	result_len += n;
	break;
      }
    }
    if (i == DICT_SIZE) {
      // Word not in dictionary
      int n =
	  snprintf(result + result_len, len * 2 + 1 - result_len, "%s ", word);
      if (n < 0 || (size_t)n >= len * 2 + 1 - result_len) {
	fprintf(stderr, "snprintf failed or buffer too small\n");
	free(result);
	exit(1);
      }
      result_len += n;
    }
    word = strtok_r(NULL, " ", &saveptr);
  }

  if (result_len > 0 && result[result_len - 1] == ' ') {
    result[result_len - 1] = '\0';
  }

  // Ensure null-termination and copy back to original string
  if (result_len < len * 2 + 1) {
    result[result_len] = '\0';
  } else {
    result[len * 2] = '\0';
  }

  strncpy(str, result, result_len + 1);
  str[result_len] = '\0';
  free(result);
}
