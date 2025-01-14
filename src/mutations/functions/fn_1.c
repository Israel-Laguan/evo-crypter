#include "../mod.h"
#include <ctype.h>

void fn_1_up(char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (isupper(str[i])) {
      str[i] = ((str[i] - 'A' + 3) % 26) + 'A';
    } else if (islower(str[i])) {
      str[i] = ((str[i] - 'a' + 3) % 26) + 'a';
    }
  }
}

void fn_1_down(char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (isupper(str[i])) {
      str[i] = ((str[i] - 'A' - 3 + 26) % 26) + 'A';
    } else if (islower(str[i])) {
      str[i] = ((str[i] - 'a' - 3 + 26) % 26) + 'a';
    }
  }
}