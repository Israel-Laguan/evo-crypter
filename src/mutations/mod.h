#ifndef EVO_MUTATIONS_MOD_H
#define EVO_MUTATIONS_MOD_H

#include <stdbool.h>

// Structure to hold arguments for the chunk processing function
typedef struct
{
    char *buffer;
    const char *generations;
    bool decrypt;
} ChunkProcessingArgs;

// all mutation functions
void fn_1_up(char *str);
void fn_1_down(char *str);
void fn_2_up(char *str);
void fn_2_down(char *str);
void fn_3_up(char *str);
void fn_3_down(char *str);
void fn_4_up(char *str);
void fn_4_down(char *str);
void fn_5_up(char *str);
void fn_5_down(char *str);
void fn_6_up(char *str);
void fn_6_down(char *str);
void fn_7_up(char *str);
void fn_7_down(char *str);
void fn_8_up(char *str);
void fn_8_down(char *str);
void fn_9_up(char *str);
void fn_9_down(char *str);
void fn_ampersand_up(char *str);
void fn_ampersand_down(char *str);
void fn_asterisk_up(char *str);
void fn_asterisk_down(char *str);

// Dispatch functions
void apply_mutation_up(char symbol, char *str);
void apply_mutation_down(char symbol, char *str);
void *apply_mutations_to_chunk(void *arg, const char *generations, bool decrypt);

#endif // EVO_MUTATIONS_MOD_H