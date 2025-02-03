#include <ctype.h>
#include <string.h>

// Invert Case Cypher
void fn_8_up(char* str) {
  if (str == NULL)
    return;
  for (size_t i = 0; str[i] != '\0'; i++) {
    if (isupper(str[i])) {
      str[i] = tolower(str[i]);
    } else if (islower(str[i])) {
      str[i] = toupper(str[i]);
    }
  }
}

void fn_8_down(char* str) { fn_8_up(str); }
