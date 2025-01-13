#include "input_processing.h"
#include "../mutations/mod.h"
#include "utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * @brief Prepares a chunk of data for processing.
 *
 * This function allocates memory for a new buffer and copies the input buffer
 * into it. It handles potential memory allocation errors.
 *
 * @param buffer The input buffer containing the chunk of data.
 * @return A pointer to the newly allocated buffer, or NULL if allocation fails.
 */
static char* prepare_chunk(const char* buffer) {
  char* prepared_buffer = strdup(buffer);
  if (!prepared_buffer) {
    perror("Failed to allocate memory for prepared buffer");
    return NULL; // Return NULL on allocation failure
  }
  return prepared_buffer;
}

/**
 * @brief Processes a single chunk of data by applying mutations.
 *
 * This function is designed to be used either directly (in single-threaded
 * mode) or as a thread function (in multi-threaded mode). It applies the
 * sequence of mutations defined in the `generations` string to the input
 * `buffer`.
 *
 * @param arg A pointer to a `ChunkProcessingArgs` struct containing:
 *            - buffer: The chunk of data to process.
 *            - generations: The sequence of mutations to apply.
 *            - decrypt: A flag indicating whether to decrypt or encrypt.
 * @return Always returns NULL. This is only a placeholder to satisfy the
 *         requirements of `pthread_create`, where the function must return
 * `void *`.
 */
static void* process_chunk(void* arg) {
  ChunkProcessingArgs* args = (ChunkProcessingArgs*)arg;
  int generations_len = strlen(args->generations);
  for (int i = 0; i < generations_len; i++) {
    apply_mutations_to_chunk(args, args->generations, args->decrypt);
  }
  return NULL;
}

void process_input_single_thread(const char* input_file,
				 const char* output_file,
				 const char* generations, bool decrypt) {
  FILE* input = fopen(input_file, "r");
  if (!input) {
    perror("Failed to open input file");
    exit(EXIT_FAILURE);
  }

  FILE* output = fopen(output_file, "w");
  if (!output) {
    perror("Failed to open output file");
    fclose(input);
    exit(EXIT_FAILURE);
  }

  char buffer[BUFFER_SIZE];
  while (fgets(buffer, sizeof(buffer), input)) {
    char* prepared_buffer = prepare_chunk(buffer);
    if (!prepared_buffer) {
      fclose(input);
      fclose(output);
      exit(EXIT_FAILURE); // Exit on allocation failure
    }
    ChunkProcessingArgs args = {prepared_buffer, generations, decrypt};
    process_chunk(&args);
    fputs(prepared_buffer, output);
    free(prepared_buffer);
  }

  if (!decrypt && ftell(output) > 0) {
    fflush(output); // Flush the output buffer before seeking
    fseek(output, -1, SEEK_END);
    char last_char = fgetc(output);
    if (last_char != '\n') {
      fflush(output);
      fputc('\n', output);
    }
  }

  fclose(input);
  fclose(output);
}

void process_input_multi_thread(const char* input_file, const char* output_file,
				const char* generations, bool decrypt,
				int threads) {
  FILE* input = fopen(input_file, "r");
  if (!input) {
    perror("Failed to open input file");
    exit(EXIT_FAILURE);
  }

  FILE* output = fopen(output_file, "w");
  if (!output) {
    perror("Failed to open output file");
    fclose(input);
    exit(EXIT_FAILURE);
  }

  pthread_t* thread_ids = malloc(threads * sizeof(pthread_t));
  ChunkProcessingArgs* thread_args =
      malloc(threads * sizeof(ChunkProcessingArgs));

  char** buffers = malloc(threads * sizeof(char*));
  for (int i = 0; i < threads; i++) {
    buffers[i] = malloc(BUFFER_SIZE);
    if (buffers[i] == NULL) { // Check if malloc was successful
      // Handle error, free previously allocated memory
      for (int j = 0; j < i; j++) {
	free(buffers[j]);
      }
      free(buffers);
      perror("Failed to allocate memory for buffers");
      exit(EXIT_FAILURE);
    }
    buffers[i][0] = '\0'; // Initialize the buffer
  }

  int i = 0;
  bool last_line = false;
  while (!last_line) {
    if (fgets(buffers[i], BUFFER_SIZE, input) == NULL) {
      last_line = true;
      if (i == 0)
	break;
    } else {
      size_t len = strlen(buffers[i]);
      if (len == 0 || buffers[i][len - 1] != '\n') {
	last_line = true;
      }
    }

    // Prepare the chunk (allocate memory)
    thread_args[i].buffer = prepare_chunk(buffers[i]);
    if (!thread_args[i].buffer) {
      // Clean up allocated resources before exiting
      for (int j = 0; j < i; j++) {
	free(thread_args[j].buffer);
      }
      for (int j = 0; j < threads; j++) {
	free(buffers[j]);
      }
      free(buffers);
      free(thread_ids);
      free(thread_args);
      fclose(input);
      fclose(output);
      exit(EXIT_FAILURE); // Exit on allocation failure
    }
    thread_args[i].generations = generations;
    thread_args[i].decrypt = decrypt;

    pthread_create(&thread_ids[i], NULL, process_chunk, &thread_args[i]);

    i = (i + 1) % threads;
    if (i == 0 || last_line) {
      for (int j = 0; j < (last_line ? i : threads); j++) {
	pthread_join(thread_ids[j], NULL);
	fputs(thread_args[j].buffer, output);
	free(thread_args[j].buffer);
      }
    }
  }

  if (!decrypt && i > 0) {
    size_t len = strlen(buffers[i - 1]);
    if (len > 0 && buffers[i - 1][len - 1] != '\n') {
      fflush(output);
      fputc('\n', output);
    }
  }

  for (int j = 0; j < threads; j++) {
    free(buffers[j]);
  }
  free(buffers);
  free(thread_ids);
  free(thread_args);

  fclose(input);
  fclose(output);
}
