#include "mod.h"
#include "../mutations/mod.h"
#include "input_processing.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void evolve_file(const char* input_file, const char* output_file,
		 const char* generations, int threads, bool decrypt) {
  char error_buffer[1024];
  if (!file_exists(input_file)) {
    snprintf(error_buffer, sizeof(error_buffer),
	     "Error: Input file does not exist: %s\n", input_file);
    fprintf(stderr, "%s", error_buffer);
    exit(EXIT_FAILURE);
  }
  if (threads == 1) {
    process_input_single_thread(input_file, output_file, generations, decrypt);
  } else {
    process_input_multi_thread(input_file, output_file, generations, decrypt,
			       threads);
  }
}
