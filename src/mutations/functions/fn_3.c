#include "fn_3.h"
#include "../mod.h"
#include <ctype.h>

// Vigenere Cipher (with a fixed key)
char vigenere_key[] = "vigenere";

void fn_3_up(char* str) {
  if (str == NULL)
    return;
  int key_len = strlen(vigenere_key);
  if (key_len == 0)
    return;

  for (int i = 0, j = 0; str[i] != '\0'; i++) {
    if (isalpha(str[i])) {
      char k = vigenere_key[j % key_len];
      int shift = tolower(k) - 'a';

      if (isupper(str[i])) {
	str[i] = ((str[i] - 'A' + shift) % 26) + 'A';
      } else if (islower(str[i])) {
	str[i] = ((str[i] - 'a' + shift) % 26) + 'a';
      }

      j++;
    }
  }
}

void fn_3_down(char* str) {
  if (str == NULL)
    return;
  int key_len = strlen(vigenere_key);
  if (key_len == 0)
    return;

  for (int i = 0, j = 0; str[i] != '\0'; i++) {
    if (isalpha(str[i])) {
      char k = vigenere_key[j % key_len];
      int shift = tolower(k) - 'a';

      if (isupper(str[i])) {
	str[i] = ((str[i] - 'A' - shift + 26) % 26) + 'A';
      } else if (islower(str[i])) {
	str[i] = ((str[i] - 'a' - shift + 26) % 26) + 'a';
      }

      j++;
    }
  }
}
