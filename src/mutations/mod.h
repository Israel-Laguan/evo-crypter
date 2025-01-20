/**
 * @file mod.h
 * @brief Defines mutation functions and dispatch logic for evo-crypter.
 */

#ifndef EVO_MUTATIONS_MOD_H
#define EVO_MUTATIONS_MOD_H

#include "../file/input_processing.h"
#include "../file/utils.h"
#include <stddef.h> // size_t for snprintf, strncpy

// Function declarations for all mutation functions
void fn_1_up(char* str);
void fn_1_down(char* str);
void fn_2_up(char* str);
void fn_2_down(char* str);
void fn_3_up(char* str);
void fn_3_down(char* str);
void fn_4_up(char* str);
void fn_4_down(char* str);
void fn_5_up(char* str);
void fn_5_down(char* str);
void fn_6_up(char* str);
void fn_6_down(char* str);
void fn_7_up(char* str);
void fn_7_down(char* str);
void fn_8_up(char* str);
void fn_8_down(char* str);
void fn_9_up(char* str);
void fn_9_down(char* str);
void fn_ampersand_up(char* str);
void fn_ampersand_down(char* str);
void fn_asterisk_up(char* str);
void fn_asterisk_down(char* str);

// Dispatch functions

/**
 * @brief Applies the appropriate encryption mutation function based on the
 * symbol.
 *
 * This function acts as a dispatcher, selecting and applying the correct
 * encryption function (`fn_*_up`) based on the provided symbol.
 *
 * @param symbol The mutation symbol (e.g., '1', 'a', '#').
 * @param str The string to mutate (modified in place).
 */
void apply_mutation_up(char symbol, char* str);

/**
 * @brief Applies the appropriate decryption mutation function based on the
 * symbol.
 *
 * This function acts as a dispatcher, selecting and applying the correct
 * decryption function (`fn_*_down`) based on the provided symbol.
 *
 * @param symbol The mutation symbol (e.g., '1', 'a', '#').
 * @param str The string to mutate (modified in place).
 */
void apply_mutation_down(char symbol, char* str);

/**
 * @brief Applies a sequence of mutations to a chunk of data.
 *
 * @param arg Pointer to a ChunkProcessingArgs struct containing the buffer,
 * generations, and decrypt flag.
 * @param generations The generation sequence string.
 * @param decrypt Flag indicating whether to decrypt (true) or encrypt (false).
 * @return Returns NULL always. Required to be used in pthreads.
 */
void* apply_mutations_to_chunk(void* arg, const char* generations,
			       bool decrypt);

#endif // EVO_MUTATIONS_MOD_H
