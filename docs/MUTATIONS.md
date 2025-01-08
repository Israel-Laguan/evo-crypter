This document outlines the guidelines for contributing to the `evo-crypter` project, particularly for adding new mutation functions.

## Adding New Mutation Functions

1. **Implement the functions in `src/mutations/functions`:**

    *   Create a new file or use a file with an empty implementation.
    *   Create two functions for each mutation:
        *   `fn_<mutation_identifier>_up`: Encrypts the input string.
        *   `fn_<mutation_identifier>_down`: Decrypts the input string.
        *   Replace `<mutation_identifier>` with a unique symbol (e.g., a number, letter, or special character like # or \*).
    *   The functions should take a `char *` (string) as input and modify it in place.
    *   Ensure that `fn_<mutation_identifier>_down` perfectly reverses the operation of `fn_<mutation_identifier>_up`.

    **Example:**

    ```c
    // src/mutations/functions/fn_1.c

    // Caesar cipher with a shift of 3
    void fn_1_up(char *str) {
        // ... implementation ...
    }

    void fn_1_down(char *str) {
        // ... implementation ...
    }
    ```

2. **Declare the functions in `src/mutations/mod.h`:**

    ```c
    // src/mutations/mod.h

    void fn_1_up(char *str);
    void fn_1_down(char *str);
    ```

3. **Update the dispatch functions in `src/mutations/mod.c`:**

    *   Modify the `apply_mutation_up` and `apply_mutation_down` functions to include your new mutation functions.
    *   Use a `switch` statement based on the `symbol` to call the appropriate function.

    ```c
    // src/mutations/mod.c

    void apply_mutation_up(char symbol, char *str) {
        switch (symbol) {
            case '1':
                fn_1_up(str);
                break;
            // ... other cases ...
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
            // ... other cases ...
            default:
                fprintf(stderr, "Unknown mutation symbol: %c\n", symbol);
                break;
        }
    }
    ```

4. **Build and Test:**

    *   Rebuild the project using `make all` or `./scripts/build.sh`.
    *   Test your new mutation functions using the command-line interface:

        ```bash
        ./evo --input <input_file> --threads <num_threads> --generations <your_mutation_symbol>
        ```

## Guidelines

*   **Uniqueness:** Ensure your mutation identifier is unique and does not clash with existing ones.
*   **Inverse Functions:** Make absolutely sure that the `_down` function is the exact inverse of the `_up` function. Any error here will lead to data corruption.
*   **Efficiency:** Strive for efficiency in your implementations, especially if the functions are to be used on large files.
*   **Error Handling:** Include basic error handling in your functions (e.g., checking for invalid input).
*   **Comments:** Add clear and concise comments to your code, explaining the logic behind your mutation functions.
*   **Security:** If you are implementing cryptographic functions, be aware of security best practices. Avoid rolling your own crypto for production use unless you are a cryptography expert.

## Contributing to Other Parts of the Project

If you want to contribute to other parts of the project (e.g., improving the core logic, adding new features), please follow these general guidelines:

1. **Fork the repository.**
2. **Create a new branch for your feature or bug fix.**
3. **Make your changes.**
4. **Write tests for your changes.**
5. **Ensure the project builds and all tests pass.**
6. **Submit a pull request.**

Thank you for contributing to `evo-crypter`!
