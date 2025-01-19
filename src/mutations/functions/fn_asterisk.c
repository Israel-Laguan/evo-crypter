#include "../mod.h"
#include <ctype.h>
#include <stdio.h>
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
  char result[len + 1];
  result[0] = '\0';
  char* saveptr;
  char* word = strtok_r(str, " ", &saveptr);
  size_t result_len = 0;

  while (word != NULL) {
    int i;
    for (i = 0; i < DICT_SIZE; i++) {
      if (strcasecmp(word, dictionary[i]) == 0) { // Case-insensitive comparison
	result_len += snprintf(result + result_len, sizeof(result) - result_len,
			       "%s ", dictionary[(i + 5) % DICT_SIZE]);
	break;
      }
    }
    if (i == DICT_SIZE) {
      // Word not in dictionary so we add it as is
      result_len += snprintf(result + result_len, sizeof(result) - result_len,
			     "%s ", word);
    }
    word = strtok_r(NULL, " ", &saveptr);
  }

  if (result_len > 0 && result[result_len - 1] == ' ') {
    result[result_len - 1] = '\0';
  }
  strncpy(str, result, len + 1);
}

void fn_asterisk_down(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;
  char result[len + 1];
  result[0] = '\0';
  char* saveptr;
  char* word = strtok_r(str, " ", &saveptr);
  size_t result_len = 0;

  while (word != NULL) {
    int i;
    for (i = 0; i < DICT_SIZE; i++) {
      if (strcasecmp(word, dictionary[i]) == 0) {
	result_len +=
	    snprintf(result + result_len, sizeof(result) - result_len, "%s ",
		     dictionary[(i - 5 + DICT_SIZE) % DICT_SIZE]);
	break;
      }
    }
    if (i == DICT_SIZE) {
      // Word not in dictionary
      result_len += snprintf(result + result_len, sizeof(result) - result_len,
			     "%s ", word);
    }
    word = strtok_r(NULL, " ", &saveptr);
  }

  if (result_len > 0 && result[result_len - 1] == ' ') {
    result[result_len - 1] = '\0';
  }
  strncpy(str, result, len + 1);
}
