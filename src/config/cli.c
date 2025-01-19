#include "cli.h"
#include "mod.h"

/**
 * @brief Handles the input file flag (-i or --input).
 *
 * @param config The Config struct to update.
 * @param value The value associated with the flag (input file path).
 */
void handle_input_flag(Config* config, const char* value) {
  config->input_file = strdup(value);
  if (config->input_file == NULL) {
    perror("Error allocating memory for input_file");
    config->error = true;
  }
}

/**
 * @brief Handles the threads flag (-t or --threads).
 *
 * @param config The Config struct to update.
 * @param value The value associated with the flag (number of threads).
 */
void handle_threads_flag(Config* config, const char* value) {
  config->threads = atoi(value);
  if (config->threads <= 0) {
    char error_buffer[1024];
    snprintf(error_buffer, sizeof(error_buffer),
	     "Error: --threads value must be a positive integer.\n");
    fprintf(stderr, "%s", error_buffer);
    config->error = true;
  }
}

/**
 * @brief Handles the generations flag (-g or --generations).
 *
 * @param config The Config struct to update.
 * @param value The value associated with the flag (generations string).
 */
void handle_generations_flag(Config* config, const char* value) {
  config->generations = strdup(value);
  if (config->generations == NULL) {
    perror("Error allocating memory for generations");
    config->error = true;
  }
}

/**
 * @brief Handles the decrypt flag (-d or --decrypt).
 *
 * @param config The Config struct to update.
 * @param value The value associated with the flag (NULL in this case).
 */
void handle_decrypt_flag(Config* config, const char* value) {
  (void)value;
  config->decrypt = true;
}

/**
 * @brief Handles the help flag (-h or --help).
 *
 * @param config The Config struct to update.
 * @param value The value associated with the flag (NULL in this case).
 */
void handle_help_flag(Config* config, const char* value) {
  (void)value;
  config->help = true;
}

// Lookup table (Dispatch Table)
typedef struct {
  const char* short_name;
  const char* long_name;
  void (*handler)(Config* config, const char* value);
} FlagHandler;

/**
 * @brief Array of FlagHandler structs, mapping flag names to handler functions.
 */
FlagHandler flag_handlers[] = {
    {"-i", "--input", handle_input_flag},
    {"-t", "--threads", handle_threads_flag},
    {"-g", "--generations", handle_generations_flag},
    {"-d", "--decrypt", handle_decrypt_flag},
    {"-h", "--help", handle_help_flag},
    {NULL, NULL, NULL} // Sentinel value to mark the end of the table
};

Config parse_command_line_args(int argc, char* argv[]) {
  Config config = {NULL, NULL, 1, false, false, false};

  for (int i = 1; i < argc; i++) {
    bool flag_found = false;
    for (int j = 0; flag_handlers[j].short_name != NULL; j++) {
      if (strcmp(argv[i], flag_handlers[j].short_name) == 0 ||
	  strcmp(argv[i], flag_handlers[j].long_name) == 0) {

	flag_found = true;
	char* value = NULL;

	// Expect a value unless it's a boolean flag (like -d or -h)
	if (flag_handlers[j].handler != handle_decrypt_flag &&
	    flag_handlers[j].handler != handle_help_flag) {
	  if (i + 1 < argc && argv[i + 1][0] != '-') {
	    value = argv[++i];
	  } else {
	    // Reduce the scope of error_buffer
	    char error_buffer[1024];
	    snprintf(error_buffer, sizeof(error_buffer),
		     "Error: Missing value for %s\n", argv[i]);
	    fprintf(stderr, "%s", error_buffer);
	    config.error = true;
	    return config;
	  }
	}

	flag_handlers[j].handler(&config, value);
	break;
      }
    }
    if (!flag_found) {
      // Reduce the scope of error_buffer
      char error_buffer[1024];
      snprintf(error_buffer, sizeof(error_buffer),
	       "Error: Unknown argument: %s\n", argv[i]);
      fprintf(stderr, "%s", error_buffer);
      config.error = true;
      return config;
    }
  }

  return config;
}
