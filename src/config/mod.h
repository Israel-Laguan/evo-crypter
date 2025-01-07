#ifndef EVO_CONFIG_MOD_H
#define EVO_CONFIG_MOD_H

#include <stdbool.h>

typedef struct
{
    char *input_file;
    char *generations;
    int threads;
    bool decrypt;
    bool error;
    bool help;
} Config;

Config parse_config(int argc, char *argv[]);
void free_config(Config *config);

#endif // EVO_CONFIG_MOD_H
