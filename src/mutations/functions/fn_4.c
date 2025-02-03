#include "../mod.h"
#include <ctype.h>

// ROT13
void fn_4_up(char* str) {
  if (str == NULL)
    return;
  for (int i = 0; str[i] != '\0'; i++) {
    if (isupper(str[i])) {
      str[i] = ((str[i] - 'A' + 13) % 26) + 'A';
    } else if (islower(str[i])) {
      str[i] = ((str[i] - 'a' + 13) % 26) + 'a';
    }
  }
}

void fn_4_down(char* str) {
  if (str == NULL)
    return;
  fn_4_up(str); // ROT13 is its own inverse
}
