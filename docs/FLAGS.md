# Adding New Command-Line Flags to evo-crypter

This tutorial explains how to add new command-line flags to `evo-crypter`. The project uses a lookup table approach, implemented in `src/config/cli.c`, which makes adding new flags straightforward and organized.

## Understanding the Structure

The core of the flag handling mechanism is the `FlagHandler` struct and the `flag_handlers` array:

```c
// In src/config/cli.c

typedef struct {
    const char *short_name;
    const char *long_name;
    void (*handler)(Config *config, char *value);
} FlagHandler;

FlagHandler flag_handlers[] = {
    // ... existing flags ...
    {NULL, NULL, NULL} // Sentinel value - don't remove!
};
```

*   **`short_name`:** The short, one-character version of the flag (e.g., `-i`).
*   **`long_name`:** The long, descriptive version of the flag (e.g., `--input`).
*   **`handler`:** A function pointer to the function that will process the flag's value (if any).

## Steps to Add a New Flag

1. **Choose Short and Long Names:**
    *   **Short Name:**
        *   Choose a **single, unique character**. Avoid letters already used by other flags.
        *   If you run out of letters you can use numbers or symbols
        *   **To avoid clashes**, check the existing `flag_handlers` array in `cli.c`.
    *   **Long Name:**
        *   Choose a descriptive name, typically starting with two dashes (e.g., `--my-flag`).
        *   Long names are less prone to clashes, but it's still good practice to ensure uniqueness.

2. **Create a Handler Function:**
    *   Create a new function in `src/config/cli.c` to handle the flag's logic.
    *   The function must have the following signature:

        ```c
        void handle_my_new_flag(Config *config, char *value);
        ```

    *   **`config`:** A pointer to the `Config` struct where you'll store the flag's value.
    *   **`value`:** A string containing the value associated with the flag (or `NULL` for boolean flags).

3. **Add an Entry to `flag_handlers`:**
    *   Add a new entry to the `flag_handlers` array in `cli.c`:

        ```c
        {
            "-x", "--my-flag", handle_my_new_flag
        },
        ```

    *   Replace `"-x"` and `"--my-flag"` with your chosen short and long names.
    *   Replace `handle_my_new_flag` with the name of your handler function.

## Examples

Here are three examples demonstrating how to add different types of flags:

### 1. Boolean Flag (e.g., `--verbose`)

A boolean flag doesn't take a value; its presence indicates `true`, and its absence indicates `false`.

**Handler Function:**

```c
// in src/config/cli.c

void handle_verbose_flag(Config *config, char *value) {
    // No 'value' is used for boolean flags.
    config->verbose = true; // Add a 'verbose' field (bool) to the Config struct in mod.h
}
```

**`flag_handlers` Entry:**

```c
{
    "-v", "--verbose", handle_verbose_flag
},
```

**Usage:**

```bash
./evo -i input.txt -g 1,2 -v  # Verbose mode enabled
./evo --input input.txt --generations 1,2 --verbose # Same as above
./evo -i input.txt -g 1,2  # Verbose mode disabled (default)
```

### 2. String or Number Flag (e.g., `--output <filename>` or `--level <number>`)

This type of flag takes a single string or number as its value.

**Handler Function:**

```c
// in src/config/cli.c

void handle_output_flag(Config *config, char *value) {
    config->output_file = strdup(value); // Add 'output_file' (char *) to Config in mod.h
    if (config->output_file == NULL) {
        perror("Error allocating memory for output file");
        config->error = true;
    }
}

void handle_level_flag(Config *config, char *value) {
    config->level = atoi(value); // Add 'level' (int) to Config in mod.h
    if (config->level < 0) {
        fprintf(stderr, "Error: Level must be a non-negative number.\n");
        config->error = true;
    }
}
```

**`flag_handlers` Entry:**

```c
{
    "-o", "--output", handle_output_flag
},
{
    "-l", "--level", handle_level_flag
},
```

**Usage:**

```bash
./evo -i input.txt -g 1,2 -o output.txt
./evo --input input.txt --generations 1,2 --output output.txt
./evo -i input.txt -g 1,2 -l 3
./evo --input input.txt --generations 1,2 --level 3
```

### 3. Array/List Flag (e.g., `--exclude <item1,item2,...>`)

This is a more advanced case where you want to accept a comma-separated list of values.

**Handler Function:**

```c
// in src/config/cli.c
#include <string.h>

void handle_exclude_flag(Config *config, char *value) {
    // Add 'exclude_list' (char **) and 'exclude_count' (int) to Config in mod.h

    char *token;
    int count = 0;
    char *value_copy = strdup(value); // Create a copy to avoid modifying the original

    // First, count the number of items
    token = strtok(value_copy, ",");
    while (token != NULL) {
        count++;
        token = strtok(NULL, ",");
    }
    free(value_copy);

    // Now, allocate the array and store the items
    config->exclude_list = malloc(count * sizeof(char *));
    if (config->exclude_list == NULL) {
        perror("Error allocating memory for exclude list");
        config->error = true;
        return;
    }

    value_copy = strdup(value);
    token = strtok(value_copy, ",");
    for(int i = 0; token != NULL; i++){
        config->exclude_list[i] = strdup(token);
        if (config->exclude_list[i] == NULL) {
            perror("Error allocating memory for exclude item");
            config->error = true;
            // Free previously allocated memory before returning
            for (int j = 0; j < i; j++) {
                free(config->exclude_list[j]);
            }
            free(config->exclude_list);
            free(value_copy);
            return;
        }
        token = strtok(NULL, ",");
    }
    config->exclude_count = count;
    free(value_copy);
}
```

**`flag_handlers` Entry:**

```c
{
    "-e", "--exclude", handle_exclude_flag
},
```

**Usage:**

```bash
./evo -i input.txt -g 1,2 -e item1,item2,item3
./evo --input input.txt --generations 1,2 --exclude item1,item2,item3
```

**Important Considerations for Array Flags:**

*   **Memory Management:** Be careful to allocate and free memory properly to avoid memory leaks. In the `handle_exclude_flag` example, we use `strdup` to copy the items and `free` to release the memory later.
*   **Error Handling:** Check for potential errors like memory allocation failures and handle them appropriately.
*   **Freeing Memory:** Remember to free the dynamically allocated memory in your `free_config` function (in `src/config/mod.c`) when the program finishes.
*   **Parsing:** You might need to use functions like `strtok` (as in the example) or other string manipulation techniques to parse the comma-separated list.

## Testing

After adding a new flag:

1. **Rebuild:** Run `make all` or `./scripts/build.sh` to rebuild the `evo` executable.
2. **Test Thoroughly:** Test your new flag with different combinations of arguments to ensure it works as expected and doesn't interfere with other flags.

**Remember to:**

1. **Update `src/config/mod.h`:** Add the new fields (e.g., `verbose`, `output_file`, `level`, `exclude_list`, `exclude_count`) to the `Config` struct as shown in the examples.
2. **Update `src/config/mod.c`:** Add the logic for freeing the new allocated fields (if any) in your `free_config` function. For example, for the `exclude_list` field:

    ```c
    if (config->exclude_list) {
        for (int i = 0; i < config->exclude_count; i++) {
            free(config->exclude_list[i]);
        }
        free(config->exclude_list);
        config->exclude_list = NULL;
    }
    ```

## Conclusion

This lookup table approach makes adding new command-line flags to `evo-crypter` a relatively simple and well-structured process. By following these guidelines, you can extend the functionality of `evo-crypter` in a maintainable and organized way. Remember to choose unique short names, create handler functions to manage the flag's logic, and add the corresponding entry to the `flag_handlers` table. Happy coding!
