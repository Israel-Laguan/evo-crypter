#include <ctype.h>
#include <string.h>

// Reverse Words Cypher
void fn_9_up(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;

  // Reverse the entire string
  for (size_t i = 0; i < len / 2; i++) {
    char temp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = temp;
  }

  // Reverse each word individually
  size_t start = 0;
  for (size_t i = 0; i <= len; i++) {
    if (str[i] == ' ' || str[i] == '\0') {
      for (size_t j = 0; j < (i - start) / 2; j++) {
	char temp = str[start + j];
	str[start + j] = str[i - j - 1];
	str[i - j - 1] = temp;
      }
      start = i + 1;
    }
  }
}

void fn_9_down(char* str) { fn_9_up(str); }
