#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mod.h"
#include "utils.h"

Config parse_config(int argc, char *argv[]) {
    Config config = {NULL, NULL, 1, false, false, false};

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            config.help = true;
            return config;
        }

        if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                config.input_file = strdup(argv[++i]);
                if (config.input_file == NULL) {
                    perror("Error allocating memory for input_file");
                    config.error = true;
                    return config;
                }
            } else {
                fprintf(stderr, "Error: Missing or invalid value for --input.\n");
                config.error = true;
                return config;
            }
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--threads") == 0) {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                config.threads = atoi(argv[++i]);
                if (config.threads <= 0) {
                    fprintf(stderr, "Error: --threads value must be a positive integer.\n");
                    config.error = true;
                    return config;
                }
            } else {
                fprintf(stderr, "Error: Missing or invalid value for --threads.\n");
                config.error = true;
                return config;
            }
        } else if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--generations") == 0) {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                config.generations = strdup(argv[++i]);
                if (config.generations == NULL) {
                    perror("Error allocating memory for generations");
                    config.error = true;
                    return config;
                }
                for (int j = 0; config.generations[j] != '\0'; j++) {
                    if (isupper(config.generations[j])) {
                        config.generations[j] = tolower(config.generations[j]);
                    }
                }
                if (!is_valid_generations(config.generations)) {
                    fprintf(stderr, "Error: Invalid characters in --generations. Allowed: 0-9, a-z, #, *\n");
                    config.error = true;
                    return config;
                }
            } else {
                fprintf(stderr, "Error: Missing or invalid value for --generations.\n");
                config.error = true;
                return config;
            }
        } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--decrypt") == 0) {
            config.decrypt = true;
        } else {
            fprintf(stderr, "Error: Unknown argument: %s\n", argv[i]);
            config.error = true;
            return config;
        }
    }

    if (config.input_file == NULL) {
        fprintf(stderr, "Error: --input argument is required.\n");
        config.error = true;
    }

    if (config.generations == NULL) {
        config.generations = strdup("1");
        if (config.generations == NULL) {
            perror("Error allocating memory for default generations");
            config.error = true;
            return config;
        }
        printf("Warning: --generations not provided, using default generations '1'.\n");
    }

    return config;
}

void free_config(Config *config) {
    if (config->input_file) {
        free(config->input_file);
        config->input_file = NULL;
    }
    if (config->generations) {
        free(config->generations);
        config->generations = NULL;
    }
}