#ifndef EVO_INPUT_PROCESSING_H
#define EVO_INPUT_PROCESSING_H

#include <stdbool.h>

// Structure to hold arguments for the chunk processing function (Moved here)
typedef struct {
  char* buffer;
  const char* generations;
  bool decrypt;
} ChunkProcessingArgs;

void process_input_single_thread(const char* input_file,
				 const char* output_file,
				 const char* generations, bool decrypt);
void process_input_multi_thread(const char* input_file, const char* output_file,
				const char* generations, bool decrypt,
				int threads);

#endif // EVO_INPUT_PROCESSING_H
