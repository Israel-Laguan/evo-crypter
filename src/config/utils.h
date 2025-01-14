/**
 * @file utils.h
 * @brief Utility functions for the config module.
 */

#ifndef EVO_CONFIG_UTILS_H
#define EVO_CONFIG_UTILS_H

#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Prints the program's usage information to the console.
 *
 * @param program_name The name of the program executable.
 */
void print_usage(const char* program_name);

/**
 * @brief Validates the generation string.
 *
 * Checks if the provided generation string only contains valid characters:
 * 0-9, a-z, #, and *.
 *
 * @param generations The generation string to validate.
 * @return `true` if the generation string is valid, `false` otherwise.
 */
bool is_valid_generations(const char* generations);

#endif // EVO_CONFIG_UTILS_H
