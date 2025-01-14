#include "mod.h"
#include "cli.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Config initialize_config(int argc, char* argv[]) {
  Config config = parse_command_line_args(argc, argv);
  char error_buffer[1024];

  if (config.error || config.help) {
    return config;
  }

  if (config.input_file == NULL) {
    snprintf(error_buffer, sizeof(error_buffer),
	     "Error: --input argument is required.\n");
    fprintf(stderr, "%s", error_buffer);
    config.error = true;
    return config;
  }

  if (config.generations == NULL) {
    config.generations = strdup("1");
    if (config.generations == NULL) {
      perror("Error allocating memory for default generations");
      config.error = true;
      return config;
    }
    printf("Warning: --generations not provided, using default generations "
	   "'1'.\n");
  }

  for (int j = 0; config.generations[j] != '\0'; j++) {
    if (isupper(config.generations[j])) {
      config.generations[j] = tolower(config.generations[j]);
    }
  }
  if (!is_valid_generations(config.generations)) {
    snprintf(error_buffer, sizeof(error_buffer),
	     "Error: Invalid characters in --generations. Allowed: 0-9, a-z, "
	     "#, *\n");
    fprintf(stderr, "%s", error_buffer);
    config.error = true;
    return config;
  }

  return config;
}

void free_config(Config* config) {
  if (config->input_file) {
    free(config->input_file);
    config->input_file = NULL;
  }
  if (config->generations) {
    free(config->generations);
    config->generations = NULL;
  }
}
