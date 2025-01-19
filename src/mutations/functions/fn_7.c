#include "../mod.h"
#include <ctype.h>

// Affine Cipher (with a=5, b=8)
void fn_7_up(char* str) {
  if (str == NULL)
    return;
  for (int i = 0; str[i] != '\0'; i++) {
    if (isalpha(str[i])) {
      char base = isupper(str[i]) ? 'A' : 'a';
      str[i] = (5 * (str[i] - base) + 8) % 26 + base;
    }
  }
}

void fn_7_down(char* str) {
  if (str == NULL)
    return;
  // Modular inverse of 5 (mod 26) is 21
  for (int i = 0; str[i] != '\0'; i++) {
    if (isalpha(str[i])) {
      char base = isupper(str[i]) ? 'A' : 'a';
      str[i] = (21 * (str[i] - base - 8 + 26)) % 26 +
	       base; // +26 for positive modulo
    }
  }
}
