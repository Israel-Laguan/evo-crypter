#ifndef EVO_FILE_MOD_H
#define EVO_FILE_MOD_H

#include <stdbool.h>

void evolve_file(const char* input_file, const char* output_file,
		 const char* generations, int threads, bool decrypt);

#endif // EVO_FILE_MOD_H
