#include "../mod.h"
#include <ctype.h>

// Substitution cipher (with hardcoded mapping)
static char substitution_map[] =
    "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm"; // Example mapping
static char substitution_inv_map[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // Inverse mapping

void fn_5_up(char* str) {
  if (str == NULL)
    return;
  for (int i = 0; str[i] != '\0'; i++) {
    if (isupper(str[i])) {
      str[i] = substitution_map[str[i] - 'A'];
    } else if (islower(str[i])) {
      str[i] = substitution_map[str[i] - 'a' + 26];
    }
  }
}

void fn_5_down(char* str) {
  if (str == NULL)
    return;
  for (int i = 0; str[i] != '\0'; i++) {
    if (isupper(str[i])) {
      str[i] = substitution_inv_map[str[i] - 'A'];
    } else if (islower(str[i])) {
      str[i] = substitution_inv_map[str[i] - 'a' + 26];
    }
  }
}
