#include "utils.h"

void print_usage(const char* program_name) {
  printf("Usage: %s --input <input_file> --threads <num_threads> --generations "
	 "<generations_string> [-d] [-h/--help]\n",
	 program_name);
  printf("  -i, --input    <input_file>   Path to the input file (required)\n");
  printf("  -t, --threads  <num_threads>  Number of threads (default: 1)\n");
  printf("  -g, --generations    <generations_string> Comma-separated "
	 "generations of functions (e.g., 1,0,a,z,#,*) (default: \"1\")\n");
  printf("  -d, --decrypt                 Decrypt instead of encrypt "
	 "(optional)\n");
  printf("  -h, --help                    Display this help message\n");
}

bool is_valid_generations(const char* generations) {
  if (generations == NULL || *generations == '\0') {
    return false; // Handle NULL or empty string
  }
  bool has_valid_char = false;
  for (int i = 0; generations[i] != '\0'; i++) {
    char c = generations[i];
    if (isdigit(c) || (c >= 'a' && c <= 'z') || (c == '#') || (c == '*')) {
      has_valid_char = true;
    } else if (c != ',') {
      return false; // Invalid character found
    }
  }
  return has_valid_char; // Must have at least one valid character
}
