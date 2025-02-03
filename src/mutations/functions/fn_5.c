#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Caesar Cipher with dynamic shift
void fn_5_up(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;

  int shift = len % 26; // Dynamic shift based on string length
  for (size_t i = 0; str[i] != '\0'; i++) {
    if (isupper(str[i])) {
      str[i] = ((str[i] - 'A' + shift) % 26) + 'A';
    } else if (islower(str[i])) {
      str[i] = ((str[i] - 'a' + shift) % 26) + 'a';
    }
  }
}

void fn_5_down(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;

  int shift = len % 26; // Dynamic shift based on string length
  for (size_t i = 0; str[i] != '\0'; i++) {
    if (isupper(str[i])) {
      str[i] = ((str[i] - 'A' - shift + 26) % 26) + 'A';
    } else if (islower(str[i])) {
      str[i] = ((str[i] - 'a' - shift + 26) % 26) + 'a';
    }
  }
}
