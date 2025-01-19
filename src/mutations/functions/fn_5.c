#include <ctype.h>
#include <string.h>

// Substitution cipher (with hardcoded mapping)
static char substitution_map[] =
    "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm"; // Example mapping

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
    for (int j = 0; j < 52; j++) {
      if (str[i] == substitution_map[j]) {
	if (j < 26) {
	  str[i] = 'A' + j; // Uppercase
	} else {
	  str[i] = 'a' + (j - 26); // Lowercase
	}
	break;
      }
    }
  }
}
