// src/mutations/mod.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mutation_functions.h"
#include "functions/fn_1.c"
#include "functions/fn_2.c"
#include "functions/fn_3.c"
#include "functions/fn_4.c"
#include "functions/fn_5.c"
#include "functions/fn_6.c"
#include "functions/fn_7.c"
#include "functions/fn_8.c"
#include "functions/fn_9.c"
#include "functions/fn_ampersand.c"
#include "functions/fn_asterisk.c"

typedef struct
{
    char *buffer;
} EvoThreadArgs;

void apply_mutation_up(char symbol, char *str) {
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
            fprintf(stderr, "Unknown mutation symbol: %c\n", symbol);
            break;
    }
}

void apply_mutation_down(char symbol, char *str) {
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
            fprintf(stderr, "Unknown mutation symbol: %c\n", symbol);
            break;
    }
}

void *apply_mutations_to_chunk(void *arg, const char *generations, bool decrypt)
{
    EvoThreadArgs *args = (EvoThreadArgs *)arg;
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

    for (int i = 0; i < strlen(generations_copy); i++)
    {
        char *token = strtok(i == 0 ? generations_copy : NULL, ",");
        while (token != NULL)
        {
            for (int j = 0; j < strlen(token); j++)
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
    }

    strcpy(args->buffer, buffer_copy);
    free(buffer_copy);
    free(generations_copy);
    return NULL;
}