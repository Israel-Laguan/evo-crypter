#ifndef EVO_INPUT_PROCESSING_H
#define EVO_INPUT_PROCESSING_H

#include <stdbool.h>

void process_input_single_thread(const char *input_file, const char *output_file, const char *generations, bool decrypt);
void process_input_multi_thread(const char *input_file, const char *output_file, const char *generations, bool decrypt, int threads);

#endif // EVO_INPUT_PROCESSING_H
