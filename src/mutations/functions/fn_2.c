#include "../mod.h"
#include <ctype.h>

// Reverse String
void fn_2_up(char* str) {
  int start = 0;
  int end = 0;

  // Find the end of the current line (where '\n' or '\0' is)
  while (str[end] != '\n' && str[end] != '\0') {
    end++;
  }

  // Reverse the line (excluding the newline character, if any)
  end--; // Move back from '\n' or '\0'
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

void fn_2_down(char* str) { fn_2_up(str); }
