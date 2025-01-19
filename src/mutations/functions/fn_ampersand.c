#include <ctype.h>
#include <string.h>

// XOR Cipher (with a fixed key)
static char xor_key = 'K'; // Example key (can be any character)

void fn_ampersand_up(char* str) {
  if (str == NULL) {
    return;
  }
  for (int i = 0; str[i] != '\0'; i++) {
    str[i] ^= xor_key;
  }
}

void fn_ampersand_down(char* str) {
  fn_ampersand_up(str); // XOR with the same key is its own inverse
}
