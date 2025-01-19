/**
 * @file mod.h
 * @brief Defines the configuration structure and functions for evo-crypter.
 */

#ifndef EVO_CONFIG_MOD_H
#define EVO_CONFIG_MOD_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strncpy

/**
 * @brief Represents the program's configuration settings.
 *
 * This struct holds all the options and flags parsed from the
 * command-line arguments.
 */
typedef struct {
  char* input_file;  /**< Path to the input file. */
  char* generations; /**< String representing the sequence of mutations. */
  int threads;	     /**< Number of threads to be used. */
  bool decrypt;	     /**< Flag to indicate decryption mode. */
  bool error;	     /**< Flag to indicate an error during parsing. */
  bool help;	     /**< Flag to display help information. */
} Config;

/**
 * @brief Initializes the configuration, validates it, and sets default values.
 *
 * This function takes the preliminary Config object created by
 * `parse_command_line_args`, performs validation checks, sets default values
 * for unspecified options, and ensures that the configuration is consistent and
 * ready for use.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @return A fully initialized and validated Config struct.
 *         The `error` field will be set to `true` if any errors are
 * encountered.
 */
Config initialize_config(int argc, char* argv[]);

/**
 * @brief Frees the dynamically allocated memory in the Config struct.
 *
 * This function should be called when the Config struct is no longer needed to
 * prevent memory leaks.
 *
 * @param config A pointer to the Config struct to be freed.
 */
void free_config(Config* config);

#endif // EVO_CONFIG_MOD_H
