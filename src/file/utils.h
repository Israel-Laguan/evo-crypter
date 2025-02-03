/**
 * @file utils.h
 * @brief Defines utility functions for file operations in evo-crypter.
 */

#ifndef EVO_FILE_UTILS_H
#define EVO_FILE_UTILS_H

#include <setjmp.h>  // jmp_buf
#include <stdbool.h> // bool
#include <stdio.h> // fopen, stderr, fprintf, fputc, fgetc, fseek, fflush, ftell, fgets, fclose, perror
#include <stdlib.h> // free, exit
#include <string.h> // strlen, strncpy, strdup

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
