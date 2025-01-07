#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include "utils.h"
#include "file_operations.h"
#include "../mutations/mutation_functions.h"

#define BUFFER_SIZE 1024

void evolve_file(const char *input_file, const char *output_file, const char *generations, int threads, bool decrypt)
{
    FILE *input = fopen(input_file, "r");
    if (!input)
    {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    FILE *output = fopen(output_file, "w");
    if (!output)
    {
        perror("Failed to open output file");
        fclose(input);
        exit(EXIT_FAILURE);
    }

    if (threads == 1)
    {
        char buffer[BUFFER_SIZE];
        while (fgets(buffer, sizeof(buffer), input))
        {
            apply_mutations_to_chunk(buffer, generations, decrypt);
            fputs(buffer, output);
        }
        if (!decrypt && ftell(output) > 0)
        {
            fseek(output, -1, SEEK_END);
            char last_char = fgetc(output);
            if (last_char != '\n')
            {
                fputc('\n', output);
            }
        }
    }
    else
    {
        pthread_t *thread_ids = malloc(threads * sizeof(pthread_t));
        EvoThreadArgs *thread_args = malloc(threads * sizeof(EvoThreadArgs));

        char **buffers = malloc(threads * sizeof(char *));
        for (int i = 0; i < threads; i++)
        {
            buffers[i] = malloc(BUFFER_SIZE);
        }

        int i = 0;
        bool last_line = false;
        while (!last_line)
        {
            if (fgets(buffers[i], BUFFER_SIZE, input) == NULL)
            {
                last_line = true;
                if (i == 0)
                    break;
            }
            else
            {
                size_t len = strlen(buffers[i]);
                if (len == 0 || buffers[i][len - 1] != '\n')
                {
                    last_line = true;
                }
            }

            thread_args[i] = (EvoThreadArgs){buffers[i]};
            pthread_create(&thread_ids[i], NULL, apply_mutations_to_chunk, &thread_args[i]);

            i = (i + 1) % threads;
            if (i == 0 || last_line)
            {
                for (int j = 0; j < (last_line ? i : threads); j++)
                {
                    pthread_join(thread_ids[j], NULL);
                    fputs(buffers[j], output);
                }
            }
        }

        if (!decrypt && i > 0)
        {
            size_t len = strlen(buffers[i - 1]);
            if (len > 0 && buffers[i - 1][len - 1] != '\n')
            {
                fputc('\n', output);
            }
        }

        for (int j = 0; j < threads; j++)
        {
            free(buffers[j]);
        }
        free(buffers);
        free(thread_ids);
        free(thread_args);
    }

    fclose(input);
    fclose(output);
}
