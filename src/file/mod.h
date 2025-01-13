/**
 * @file mod.h
 * @brief Defines the main file processing function for evo-crypter.
 */

#ifndef EVO_FILE_MOD_H
#define EVO_FILE_MOD_H

#include <stdbool.h>

/**
 * @brief Encrypts or decrypts a file using the specified mutations.
 *
 * This function is the main entry point for file processing. It takes an input
 * file, an output file, a generation sequence, the number of threads to use,
 * and a flag indicating whether to decrypt or encrypt. It then applies the
 * specified mutations iteratively to the input file and writes the result to
 * the output file.
 *
 * @param input_file The path to the input file.
 * @param output_file The path to the output file.
 * @param generations The generation sequence string.
 * @param threads The number of threads to use for processing.
 * @param decrypt A flag indicating whether to decrypt (`true`) or encrypt
 * (`false`).
 */
void evolve_file(const char* input_file, const char* output_file,
		 const char* generations, int threads, bool decrypt);

#endif // EVO_FILE_MOD_H
