/**
 * @file cli.h
 * @brief Defines the command-line interface parsing functions for evo-crypter.
 */

#ifndef EVO_CONFIG_CLI_H
#define EVO_CONFIG_CLI_H

#include "mod.h"

/**
 * @brief Parses command-line arguments and populates the Config struct.
 *
 * This function handles the initial parsing of command-line arguments. It
 * identifies flags and their associated values, and it stores them in a
 * preliminary Config object. Further validation and processing of the
 * configuration is done in `initialize_config`.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @return A Config struct populated with the parsed arguments.
 *         The `error` field will be set to `true` if any errors are encountered
 * during parsing.
 */
Config parse_command_line_args(int argc, char* argv[]);

#endif // EVO_CONFIG_CLI_H
