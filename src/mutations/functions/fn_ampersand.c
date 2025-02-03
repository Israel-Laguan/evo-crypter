#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Rail Fence Cipher with dynamic rails
void fn_ampersand_up(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;

  // Determine the number of rails dynamically
  int rails = (len < 3) ? 1 : 3;

  // Allocate memory for rails
  char rail[rails][len + 1];
  for (int i = 0; i < rails; i++) {
    memset(rail[i], 0, len + 1);
  }

  // Fill the rails
  int direction = 1;
  int row = 0;
  for (size_t i = 0; i < len; i++) {
    strncat(rail[row], &str[i], 1);
    row += direction;
    if (row == rails - 1 || row == 0) {
      direction *= -1;
    }
  }

  // SAFE CONCATENATION: Replace strcat with memcpy + offset tracking
  size_t offset = 0;
  for (int i = 0; i < rails; i++) {
    size_t rail_len = strlen(rail[i]);
    if (rail_len > 0) {
      memcpy(str + offset, rail[i], rail_len);
      offset += rail_len;
    }
  }
  str[offset] = '\0'; // Ensure null-termination
}

void fn_ampersand_down(char* str) {
  if (str == NULL)
    return;
  size_t len = strlen(str);
  if (len == 0)
    return;

  // Determine the number of rails dynamically
  int rails = (len < 3) ? 1 : 3;

  // Calculate rail counts
  int rail_counts[rails];
  memset(rail_counts, 0, sizeof(rail_counts));

  int direction = 1;
  int row = 0;
  for (size_t i = 0; i < len; i++) {
    rail_counts[row]++;
    row += direction;
    if (row == rails - 1 || row == 0) {
      direction *= -1;
    }
  }

  // Split into rails
  char rail[rails][len + 1];
  int offset = 0;
  for (int i = 0; i < rails; i++) {
    strncpy(rail[i], str + offset, rail_counts[i]);
    rail[i][rail_counts[i]] = '\0';
    offset += rail_counts[i];
  }

  // Reconstruct original string
  direction = 1;
  row = 0;
  int rail_indices[rails];
  memset(rail_indices, 0, sizeof(rail_indices));

  for (size_t i = 0; i < len; i++) {
    str[i] = rail[row][rail_indices[row]++];
    row += direction;
    if (row == rails - 1 || row == 0) {
      direction *= -1;
    }
  }
  str[len] = '\0';
}
