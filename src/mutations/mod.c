#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mod.h"
#include "../file/utils.h"
#include "../file/input_processing.h"

#define BUFFER_SIZE 1024

void apply_mutation_up(char symbol, char *str) {
  char error_buffer[1024];
  switch (symbol) {
  case '1':
    fn_1_up(str);
    break;
  case '2':
    fn_2_up(str);
    break;
  case '3':
    fn_3_up(str);
    break;
  case '4':
    fn_4_up(str);
    break;
  case '5':
    fn_5_up(str);
    break;
  case '6':
    fn_6_up(str);
    break;
  case '7':
    fn_7_up(str);
    break;
  case '8':
    fn_8_up(str);
    break;
  case '9':
    fn_9_up(str);
    break;
  case '#':
    fn_ampersand_up(str);
    break;
  case '*':
    fn_asterisk_up(str);
    break;
  default:
    snprintf(error_buffer, sizeof(error_buffer),
	     "Unknown mutation symbol: %c\n", symbol);
    fprintf(stderr, "%s", error_buffer);
    break;
    }
}

void apply_mutation_down(char symbol, char *str) {
  char error_buffer[1024];
  switch (symbol) {
  case '1':
    fn_1_down(str);
    break;
  case '2':
    fn_2_down(str);
    break;
  case '3':
    fn_3_down(str);
    break;
  case '4':
    fn_4_down(str);
    break;
  case '5':
    fn_5_down(str);
    break;
  case '6':
    fn_6_down(str);
    break;
  case '7':
    fn_7_down(str);
    break;
  case '8':
    fn_8_down(str);
    break;
  case '9':
    fn_9_down(str);
    break;
  case '#':
    fn_ampersand_down(str);
    break;
  case '*':
    fn_asterisk_down(str);
    break;
  default:
    snprintf(error_buffer, sizeof(error_buffer),
	     "Unknown mutation symbol: %c\n", symbol);
    fprintf(stderr, "%s", error_buffer);
    break;
    }
}

void *apply_mutations_to_chunk(void *arg, const char *generations, bool decrypt)
{
    ChunkProcessingArgs *args = (ChunkProcessingArgs *)arg;
    char *buffer_copy = strdup(args->buffer);
    if (!buffer_copy)
    {
        perror("Failed to allocate memory for buffer copy");
        exit(EXIT_FAILURE);
    }

    char *generations_copy = strdup(generations);
    if (!generations_copy)
    {
        perror("Failed to allocate memory for generations copy");
        free(buffer_copy);
        exit(EXIT_FAILURE);
    }

    if (decrypt)
    {
        reverse_generations(generations_copy);
    }

    // Iterate through the generation sequence
    char *token = strtok(generations_copy, ",");
    while (token != NULL)
    {
        for (size_t j = 0; j < strlen(token); j++)
        {
            char symbol = token[j];
            if (decrypt)
            {
                apply_mutation_down(symbol, buffer_copy);
            }
            else
            {
                apply_mutation_up(symbol, buffer_copy);
            }
        }
        token = strtok(NULL, ",");
    }

    strncpy(args->buffer, buffer_copy,
	    BUFFER_SIZE - 1);		  // Prevent buffer overflow
    args->buffer[BUFFER_SIZE - 1] = '\0'; // Ensure null-termination
    free(buffer_copy);
    free(generations_copy);
    return NULL;
}
