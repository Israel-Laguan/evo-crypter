/**
 * @file input_processing.h
 * @brief Defines functions for processing input files in evo-crypter.
 */

#ifndef EVO_INPUT_PROCESSING_H
#define EVO_INPUT_PROCESSING_H

#include <stdbool.h>

/**
 * @brief Structure to hold arguments for the chunk processing function.
 *
 * This struct is used to pass data to the `process_chunk` function, which
 * might be executed in a separate thread.
 */
typedef struct {
  char* buffer; /**< The buffer containing the chunk of data to process. */
  const char* generations; /**< The generation sequence string. */
  bool decrypt; /**< Flag indicating whether to decrypt or encrypt. */
} ChunkProcessingArgs;

/**
 * @brief Processes the input file using a single thread.
 *
 * This function reads the input file in chunks, applies the mutations to each
 * chunk, and writes the result to the output file.
 *
 * @param input_file The path to the input file.
 * @param output_file The path to the output file.
 * @param generations The generation sequence string.
 * @param decrypt A flag indicating whether to decrypt (`true`) or encrypt
 * (`false`).
 */
void process_input_single_thread(const char* input_file,
				 const char* output_file,
				 const char* generations, bool decrypt);

/**
 * @brief Processes the input file using multiple threads.
 *
 * This function divides the input file into chunks, assigns each chunk to a
 * separate thread for processing, and writes the results to the output file.
 *
 * @param input_file The path to the input file.
 * @param output_file The path to the output file.
 * @param generations The generation sequence string.
 * @param decrypt A flag indicating whether to decrypt (`true`) or encrypt
 * (`false`).
 * @param threads The number of threads to use for processing.
 */
void process_input_multi_thread(const char* input_file, const char* output_file,
				const char* generations, bool decrypt,
				int threads);

#endif // EVO_INPUT_PROCESSING_H
