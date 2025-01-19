#include "../mod.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Morse Code (basic implementation)
// Morse code representations for each letter (A-Z) and space
const char* morse_codes[] = {
    ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....", "..",
    ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.", "--.-", ".-.",
    "...",  "-",    "..-",  "...-", ".--", "-..-", "-.--", "--.."};
void fn_9_up(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;
  char result[5 * len + 1]; // Morse code can be up to 5 times longer
  result[0] = '\0';
  char* p = str;
  size_t result_len = 0;

  while (*p) {
    if (isalpha(*p)) {
      int index = toupper(*p) - 'A';
      if (index >= 0 && index < 26) {

	result_len += snprintf(result + result_len, sizeof(result) - result_len,
			       "%s ", morse_codes[index]);
      }
    } else if (*p == ' ') {
      result_len +=
	  snprintf(result + result_len, sizeof(result) - result_len, "  ");
    }
    p++;
  }

  if (result_len > 0 && result[result_len - 1] == ' ') {
    result[result_len - 1] = '\0';
  }

  strncpy(str, result, strlen(result) + 1);
}

void fn_9_down(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;
  char result[len + 1];
  result[0] = '\0';
  char* saveptr;
  char* token = strtok_r(str, " ", &saveptr);
  size_t result_len = 0;

  while (token != NULL) {
    int i;
    for (i = 0; i < 26; i++) {
      if (strcmp(token, morse_codes[i]) == 0) {
	char decoded_char = 'A' + i;
	result_len += snprintf(result + result_len, sizeof(result) - result_len,
			       "%c", decoded_char);
	break;
      }
    }
    if (i == 26) {
      // Invalid Morse code (not found in our table)
      result_len +=
	  snprintf(result + result_len, sizeof(result) - result_len, "?");
    }

    token = strtok_r(NULL, " ", &saveptr);

    if (token != NULL) {
      if (*saveptr == ' ') {
	result_len +=
	    snprintf(result + result_len, sizeof(result) - result_len, " ");
	token = strtok_r(NULL, " ", &saveptr);
      }
    }
  }

  strncpy(str, result, strlen(result) + 1);
}
