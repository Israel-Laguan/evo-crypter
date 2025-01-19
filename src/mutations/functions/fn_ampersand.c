#include "../mod.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Baconian Cipher (simple A/B version)
const char* baconian_codes[] = {
    "AAAAA", "AAAAB", "AAABA", "AAABB", "AABAA", "AABAB", "AABBA",
    "AABBB", "ABAAA", "ABAAB", "ABABA", "ABABB", "ABBAA", "ABBAB",
    "ABBBA", "ABBBB", "BAAAA", "BAAAB", "BAABA", "BAABB", "BABAA",
    "BABAB", "BABBA", "BABBB", "BBAAA", "BBAAB"};

void fn_ampersand_up(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;
  char result[6 * len + 1]; // Baconian code is 5 times longer + spaces
  result[0] = '\0';
  char* p = str;
  size_t result_len = 0;

  while (*p) {
    if (isalpha(*p)) {
      int index = toupper(*p) - 'A';
      result_len += snprintf(result + result_len, sizeof(result) - result_len,
			     "%s ", baconian_codes[index]);
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

void fn_ampersand_down(char* str) {
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
      if (strcmp(token, baconian_codes[i]) == 0) {
	char decoded_char = 'A' + i;
	result_len += snprintf(result + result_len, sizeof(result) - result_len,
			       "%c", decoded_char);
	break;
      }
    }
    if (i == 26) {
      // Invalid Baconian code
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
