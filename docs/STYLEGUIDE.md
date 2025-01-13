# Evo-Crypter Coding Style Guide

This document outlines the coding style guidelines to be followed when contributing to the `evo-crypter` project. Consistency in coding style is important for maintainability, readability, and collaboration.

We generally follow the **Linux Kernel coding style** with a few modifications, enforced using **cppcheck** and **clang-format**.

## 1. Indentation

*   Use **tabs** for indentation, not spaces.
*   Each tab should represent **2 spaces**.

## 2. Line Length

*   Keep lines under **80 characters** in length.
*   Break long lines into logical segments at appropriate places (e.g., after commas, operators).

## 3. Comments

*   Use `/* ... */` for multi-line comments.
*   Use `//` for single-line comments.
*   Comment your code generously. Explain the **why**, not just the **what**.
*   Keep comments up-to-date with the code.
*   Use **Doxygen-style comments** with `@` tags for functions, structs, enums, and typedefs.

**Example:**

```c
/**
 * @brief Encrypts a string using the Caesar cipher.
 *
 * This function shifts each character in the input string by a fixed number
 * of positions.
 *
 * @param str The string to encrypt (modified in place).
 * @param shift The number of positions to shift each character.
 */
void caesar_encrypt(char *str, int shift) {
    // ... implementation ...
}
```

## 4. Naming Conventions

*   **Variables:**
    *   Use lowercase with underscores (snake_case): `int num_threads;`, `char *input_file;`
    *   Be descriptive, but concise.
    *   Single-letter variable names are generally only acceptable for loop counters.

*   **Functions:**
    *   Use lowercase with underscores (snake_case): `void apply_mutation(char *str);`
    *   Use verbs or verb phrases to describe what the function does.

*   **Constants:**
    *   Use uppercase with underscores: `#define BUFFER_SIZE 1024`, `const int MAX_THREADS = 16;`

*   **Structs, Enums, Typedefs:**
    *   Use uppercase for the first letter (CamelCase): `typedef struct ChunkProcessingArgs { ... };`

*   **File Names:**
    *   Use lowercase with underscores: `input_processing.c`, `config_parser.h`

* **Header File Definitions**
    * Use uppercase with underscores (Screaming Snake Case) in the format `EVO_<FOLDER>_<FILE>_H`
    * For example, for `src/config/cli.h` the header file definition should be `EVO_CONFIG_CLI_H`

## 5. Braces

*   Opening braces go on the **same line** as the statement:

```c
if (condition) {
    // ...
} else {
    // ...
}

for (int i = 0; i < n; i++) {
    // ...
}
```

*   Always use braces for `if`, `else`, `for`, `while`, and `do-while` statements, even if the body contains only a single statement.

## 6. Spaces

*   Add spaces:
    *   Around operators: `x = a + b;`, `i < n`
    *   After commas: `int a, b, c;`, `printf("%d, %s", num, str);`
    *   After keywords like `if`, `for`, `while`, `switch`, `return`: `if (x > 0) { ... }`, `return 0;`

*   Do not add spaces:
    *   After a function name in a function call: `result = my_function(arg1, arg2);`
    *   Inside parentheses: `(a + b)`, not `( a + b )`

## 7. Function Definitions

*   Keep functions relatively short and focused on a single task.
*   Provide a Doxygen-style doc comment before each function definition.
*   Place the return type on the same line as the function name.

```c
/**
 * @brief Calculates the sum of two integers.
 *
 * @param a The first integer.
 * @param b The second integer.
 *
 * @return The sum of a and b.
 */
int add_numbers(int a, int b) {
    return a + b;
}
```

## 8. Header Files

*   Use header guards to prevent multiple inclusions:

```c
#ifndef EVO_CONFIG_CLI_H
#define EVO_CONFIG_CLI_H

// ... declarations ...

#endif // EVO_CONFIG_CLI_H
```

*   Include only the necessary headers in each file.
*   Prefer local includes (`"my_header.h"`) over system includes (`<my_header.h>`) for project-specific headers.

## 9. Error Handling

*   Check for errors after system calls and library functions that can fail (e.g., `fopen`, `malloc`, `pthread_create`).
*   Return appropriate error codes or use other mechanisms (e.g., setting a global error flag) to indicate errors.
*   Provide informative error messages to the user.

## 10. Other

*   Avoid using global variables whenever possible.
*   Use `const` correctness where applicable.
*   Don't use magic numbers; define constants instead.
*   Avoid overly complex or deeply nested code.

## 11. Tools

*   Use `clang-format` to automatically format your code. A `.clang-format` file is provided in the project root.
*   Run `cppcheck` to check for common coding errors.

## 12. Deviations from Linux Kernel Style

*   We allow single-line comments (`//`) for short comments.
*   We use CamelCase for struct, enum, and typedef names.
*   We use 2 spaces for indentation instead of 8 (or 4 in the Linux Kernel).

## 13. Doxygen Documentation

* We use doxygen comments to document the code
* You can use `@` or `\` for doxygen commands
* We use `/** ... */` for doxygen comments
* Use `@brief` to start a brief description
* Use `@param` to describe a function parameter
* Use `@return` to describe the return value of a function
* Use `@see` to add a cross-reference to a related function, variable, or type
* Use `@ref` to add a cross-reference to a specific struct, enum or typedef
* Use `@code` and `@endcode` to add a code example
* Use `@note` to add a note
* Use `@warning` to add a warning
* Use `@pre` to describe a precondition
* Use `@post` to describe a postcondition
* Use `@invariant` to describe an invariant
* Use `@throws` to describe an exception
* Use `@todo` to add a todo item
* Use `@deprecated` to mark a function or variable as deprecated
* Use `@since` to indicate the version when a function or variable was added
* Use `@author` to add the author of a function or variable
* Use `@date` to add the date when a function or variable was added
* Use `@version` to add the version of a function or variable
* Use `@bug` to add a bug description
* Use `@test` to add a test case
* Use `@example` to add an example
* Use `@dir` to document a directory
* Use `@file` to document a file
* Use `@namespace` to document a namespace
* Use `@class` to document a class
* Use `@struct` to document a structure
* Use `@enum` to document an enumeration
* Use `@union` to document a union
* Use `@var` to document a variable
* Use `@fn` to document a function
* Use `@typedef` to document a typedef
* Use `@defgroup` to define a group of related functions, variables, types, etc.
* Use `@ingroup` to add a function, variable, type, etc. to a group
* Use `@{` and `@}` to group related functions, variables, types, etc.

## 14. VS Code Integration
* The project includes a `.vscode` folder with recommended settings for VS Code.
* It is recommended to install the following extensions:
  - C/C++ Extension Pack
  - CMake Tools
  - Clang-Format
  - Doxygen Documentation Generator

## 15. EditorConfig

* The project includes an `.editorconfig` file to ensure consistent coding style across different editors and IDEs.
* Make sure your editor/IDE has EditorConfig support enabled.

**Note:** This coding style guide is a living document and may be updated as the project evolves. When in doubt, follow the style of the surrounding code. If you have any questions or suggestions, please open an issue on the project's GitHub repository.
