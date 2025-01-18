/**
 * @file utils.h
 * @brief Defines utility functions for file operations in evo-crypter.
 */

#ifndef EVO_FILE_UTILS_H
#define EVO_FILE_UTILS_H

#include <setjmp.h>
#include <stdbool.h>
#include <stddef.h> // stdio.h dep
#include <stdio.h>  // fopen
#include <string.h> // strlen

/**
 * @brief Reverses the order of characters in a string.
 *
 * This function is used to reverse the generation sequence during decryption.
 *
 * @param generations The string to reverse (modified in place).
 */
void reverse_generations(char* generations);

/**
 * @brief Checks if a file exists.
 *
 * @param filename The path to the file to check.
 * @return `true` if the file exists, `false` otherwise.
 */
bool file_exists(const char* filename);

#endif // EVO_FILE_UTILS_H
