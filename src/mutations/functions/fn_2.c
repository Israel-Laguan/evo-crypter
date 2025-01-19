#include <ctype.h>
#include <string.h>

// Reverse String
void fn_2_up(char* str) {
  if (str == NULL) {
    return;
  }
  size_t end = strlen(str);

  if (end > 0) {
    end--;
    size_t start = 0;
    while (start < end) {
      char temp = str[start];
      str[start] = str[end];
      str[end] = temp;
      start++;
      end--;
    }
  }
}

void fn_2_down(char* str) {
  if (str == NULL) {
    return;
  }
  fn_2_up(str);
}
