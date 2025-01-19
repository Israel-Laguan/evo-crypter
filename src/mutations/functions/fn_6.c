#include "../mod.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Rail Fence Cipher (with 3 rails)
void fn_6_up(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;
  char rail1[len + 1], rail2[len + 1], rail3[len + 1];
  int i1 = 0, i2 = 0, i3 = 0;

  for (size_t i = 0; i < len; i++) {
    if (i % 4 == 0) {
      rail1[i1++] = str[i];
    } else if (i % 2 == 0) {
      rail3[i3++] = str[i];
    } else {
      rail2[i2++] = str[i];
    }
  }

  rail1[i1] = rail2[i2] = rail3[i3] = '\0';
  size_t offset = 0;
  strncpy(str + offset, rail1, i1);
  offset += i1;
  strncpy(str + offset, rail2, i2);
  offset += i2;
  strncpy(str + offset, rail3, i3);
  offset += i3;
  str[offset] = '\0';
}

void fn_6_down(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;
  char rail1[len + 1], rail2[len + 1], rail3[len + 1];
  int i1 = 0, i2 = 0, i3 = 0;

  // Calculate lengths of each rail
  for (size_t j = 0; j < len; j++) {
    if (j % 4 == 0) {
      i1++;
    } else if (j % 2 == 0) {
      i3++;
    } else {
      i2++;
    }
  }

  // Split the string into rails
  strncpy(rail1, str, i1);
  rail1[i1] = '\0';
  strncpy(rail2, str + i1, i2);
  rail2[i2] = '\0';
  strncpy(rail3, str + i1 + i2, i3);
  rail3[i3] = '\0';

  // Reconstruct the original string
  i1 = i2 = i3 = 0;
  for (size_t j = 0; j < len; j++) {
    if (j % 4 == 0) {
      str[j] = rail1[i1++];
    } else if (j % 2 == 0) {
      str[j] = rail3[i3++];
    } else {
      str[j] = rail2[i2++];
    }
  }
  str[len] = '\0';
}
