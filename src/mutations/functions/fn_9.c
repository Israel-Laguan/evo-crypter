#include <ctype.h>
#include <string.h>

// Atbash Cipher
void fn_9_up(char* str) {
  if (str == NULL) {
    return;
  }
  for (int i = 0; str[i] != '\0'; i++) {
    if (isupper(str[i])) {
      str[i] = 'Z' - (str[i] - 'A');
    } else if (islower(str[i])) {
      str[i] = 'z' - (str[i] - 'a');
    }
  }
}

void fn_9_down(char* str) {
  fn_9_up(str); // Atbash is its own inverse
}
