#include "../mod.h"
#include <ctype.h>

// Caesar Cipher with alternating shift
void fn_7_up(char* str) {
  if (str == NULL)
    return;
  int shift = 3;
  for (size_t i = 0; str[i] != '\0'; i++) {
    if (isupper(str[i])) {
      str[i] = ((str[i] - 'A' + (i % 2 == 0 ? shift : -shift) + 26) % 26) + 'A';
    } else if (islower(str[i])) {
      str[i] = ((str[i] - 'a' + (i % 2 == 0 ? shift : -shift) + 26) % 26) + 'a';
    }
  }
}

void fn_7_down(char* str) {
  if (str == NULL)
    return;
  int shift = 3;
  for (size_t i = 0; str[i] != '\0'; i++) {
    if (isupper(str[i])) {
      str[i] = ((str[i] - 'A' - (i % 2 == 0 ? shift : -shift) + 26) % 26) + 'A';
    } else if (islower(str[i])) {
      str[i] = ((str[i] - 'a' - (i % 2 == 0 ? shift : -shift) + 26) % 26) + 'a';
    }
  }
}
