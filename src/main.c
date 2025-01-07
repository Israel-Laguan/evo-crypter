#include <stdio.h>
#include <stdlib.h>
#include "config/config_parser.h"
#include "file/evo_file_utils.h"
#include "mutations/mutation_functions.h"

int main(int argc, char *argv[])
{
    Config config = parse_config(argc, argv);

    if (config.error || config.help)
    {
        print_usage(argv[0]);
        free_config(&config);
        return 1;
    }

    if (config.decrypt)
    {
        evolve_file(config.input_file, "decrypted", config.generations, config.threads, true);
    }
    else
    {
        evolve_file(config.input_file, "encrypted", config.generations, config.threads, false);
    }

    free_config(&config);
    return 0;
}
