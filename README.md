# evo-crypter

## Overview

**evo-crypter** is a customizable file encryption tool that utilizes an evolutionary approach to apply a series of transformation functions (mutations) to data. The core idea is to simulate a simplified evolutionary process where a sequence of mutations, defined by a "generation sequence," is applied iteratively to a file's contents. This project draws inspiration from the concept of genetic mutations and applies it to the realm of data encryption.

The project's mascot is **Evo**, a friendly dinosaur/reptile creature representing the software's evolution. Evo progresses through various stages, each symbolizing a version of the software. These stages are: Hatchling, Fledgling, Slithering, Raptor, Drake, Dragon, Flying, Wyvern, Old, Elder, and Ancient.

## Algorithm

The algorithm can be described as an iterative, function composition-based encryption scheme inspired by evolutionary mutations:

1. **Mutation Definition:**
    *   Developers define pairs of functions: `fn_<mutation_identifier>_up` for encryption and `fn_<mutation_identifier>_down` for decryption, where `<mutation_identifier>` is a unique symbol (e.g., number, letter, #, \*).
    *   These functions are implemented in `src/mutations/mod.c`.
    *   Each `fn_<mutation_identifier>_up` function takes a string (a chunk of the file) as input and modifies it in place, simulating a mutation.
    *   The corresponding `fn_<mutation_identifier>_down` function reverses the operation of `fn_<mutation_identifier>_up`.

2. **Generation Sequence:**
    *   The user provides a comma-separated string (e.g., "1,a,#,4") that specifies the sequence of mutations to be applied.
    *   This sequence is referred to as the "generation sequence."
    *   **The length of the generation sequence determines the number of iterations (generations) the mutations will be applied.** For example, if the generation sequence is "1,2", the sequence "1,2" will be applied twice to each chunk of the input file.
    *   The generation sequence is passed as a command-line argument (`--generations`).

3. **Encryption Process:**
    *   The input file is read in chunks.
    *   The `apply_mutation_up` function acts as a dispatcher, selecting the appropriate `fn_<mutation_identifier>_up` function based on the current symbol in the generation sequence.
    *   The selected `fn_<mutation_identifier>_up` function is applied to the data chunk.
    *   This process is repeated for each symbol in the generation sequence, effectively applying multiple mutations in order.
    *   **The mutations are applied iteratively for a number of times equal to the length of the generation sequence. Each iteration represents a "generation" of mutation.**
    *   The transformed data is written to the output file (`encrypted.txt`).

4. **Decryption Process:**
    *   The encrypted file is read in chunks.
    *   The `apply_mutation_down` function acts as a dispatcher, selecting the appropriate `fn_<mutation_identifier>_down` function.
    *   The `fn_<mutation_identifier>_down` functions are applied in the reverse order of encryption.
    *   Each `fn_<mutation_identifier>_down` function reverses the transformation, restoring the original data.
    *   **The mutations are reversed for the same number of generations as the encryption.**
    *   The decrypted data is written to the output file (`decrypted.txt`).

5. **Multi-threading:**
    *   The `--threads` argument allows for multi-threaded processing.
    *   The file is processed in chunks. The number of threads determines how many chunks are processed concurrently.

**Security Considerations:**

*   The security of this system relies on the strength of the individual mutation functions and the secrecy of the generation sequence.
*   It's **crucial** that developers implement strong encryption/decryption functions in `mutations.c`.
*   **Do not** commit sensitive encryption functions or keys to a public repository.
*   This project is primarily for educational and experimental purposes. For real-world security applications, consider using established and thoroughly vetted encryption libraries.

## Roadmap

| Version | Codename     | Features                                                                                                                                                                                                                                           |
| :------ | :----------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 0.1.0   | Hatchling    | - Basic encryption/decryption with a sequence of functions. <br> - Single/multi-threaded operation. <br> - Iterative application of functions (generations = length of order string). <br> - Evolutionary-themed naming. <br> - Project identity (evo-crypter, mascot). <br> - Refactor of the code and documentation |
| 0.2.0   | Fledgling    | - Add tests, including unit tests, integration tests, and property-based testing. <br> - Improve error handling and reporting. <br> - Implement the Base64 mutation function.                                                                              |
| 0.3.0   | Slithering   | - Implement the function splitting and merging as a form of key management ( `-k` flag). <br> - Basic obfuscation of split function files. <br> - Implement file splitting/merging for enhanced multi-threading.                                        |
| 0.4.0   | Raptor       | - Add a feedback mechanism (fitness function) to guide the evolutionary process. <br> - Allow optional parameters to customize the behavior of mutation functions (e.g., shift value for Caesar cipher).                                             |
| 0.5.0   | Drake        | - Implement dynamic loading of mutation functions from shared libraries. <br> - Improve the security and efficiency of the core encryption/decryption algorithm.                                                                                            |
| 0.6.0   | Dragon       | - Create a simple GUI for `evo-crypter`. <br> - Improve documentation and create tutorials.                                                                                                                                               |
| 0.7.0   | Flying       | - Add a plugin system to allow users to easily extend `evo-crypter` with custom mutation functions and features. <br> - Introduce a command-line option to generate random, secure generation sequences.                                               |
| 0.8.0   | Wyvern       | - Implement a network mode where `evo-crypter` can encrypt/decrypt data streams over a network connection. <br> - Add support for authenticated encryption.                                                                                              |
| 0.9.0   | Old          | - Conduct a security audit and address any identified vulnerabilities. <br> - Optimize performance for large files and high parallelism levels.                                                                                                           |
| 10.0.0  | Elder        | - Long-term support and maintenance. <br> - Update dependencies. <br> - Address bug fixes and minor improvements.                                                                                                                                    |
| 11.0.0  | Ancient      | - Long-term support and maintenance. <br> - Update dependencies. <br> - Address bug fixes and minor improvements.                                                                                                                                    |

## Setup

1. Clone the repository:

    ```bash
    git clone <repository_url>
    cd evo-crypter
    ```

2. Build the project:

    ```bash
    make all
    ```

    or

    ```bash
    ./scripts/build.sh
    ```

## Usage

Run the encryption tool:

```bash
./evo --input <input_file> --threads <num_threads> --generations <generation_sequence> [-d]
```

*   `<input_file>`: The path to the input file.
*   `<threads>`: The number of threads to use for processing (1 for single-threaded).
*   `<generation_sequence>`: A comma-separated string representing the sequence of mutations to apply (e.g., "1,2,a,#"). The symbols used here must match the symbols in your `fn_<mutation_identifier>_up/down` functions. **The length of this sequence determines the number of iterations (generations).**
*   `[-d]`: Optional flag to decrypt instead of encrypt.

Example:

```bash
./evo --input test_input.txt --threads 4 --generations 1,2,#
./evo --input encrypted.txt --threads 4 --generations 1,2,# -d
```

## Scripts

*   `build.sh`: Builds the executable.
*   `migrate.sh`: Migrates the old code to the new structure.
*   `evolution_rate.sh`: to be implemented in the future.
*   `epoch_integration.sh`: to be implemented in the future.
*   `lineage_verification.sh`: to be implemented in the future.

**Usage Examples:**

```bash
./scripts/build.sh
./scripts/migrate.sh
```

## Contributing

See `docs/MUTATIONS.md` for instructions on adding new functions and contributing to the project.

**Important Note for Developers:**

*   The `src/mutations/mod.c` file is where you implement your encryption/decryption logic.
*   **Do not** commit sensitive encryption functions or keys to a public repository.

**How to Use:**

1. **Clone:** `git clone https://github.com/Israel-Laguan/evo-crypter.git`
2. **Build:**

    ```bash
    make all
    ```

    or

    ```bash
    ./scripts/build.sh
    ```

3. **Run:**

    ```bash
    ./evo --input test_input.txt --threads 4 --generations 1,2,#
    ```

**Project Structure:**

```
evo-crypter/
├── docs/
│   ├── FLAGS.md
│   └── MUTATIONS.md
├── scripts/
│   ├── build.sh
│   ├── migrate.sh
│   ├── evolution_rate.sh (empty for now)
│   ├── epoch_integration.sh (empty for now)
│   └── lineage_verification.sh (empty for now)
├── src/
│   ├── config/
│   │   ├── mod.h
│   │   ├── mod.c
│   │   ├── cli.h
│   │   ├── cli.c
│   │   ├── utils.h
│   │   └── utils.c
│   ├── file/
│   │   ├── mod.h
│   │   ├── mod.c
│   │   ├── utils.h
│   │   ├── utils.c
│   │   └── input_processing.h
│   │   └── input_processing.c
│   ├── mutations/
│   │   ├── mod.h
│   │   ├── mod.c
│   │   └── functions/
│   │       ├── fn_1.c
│   │       ├── fn_2.c
│   │       ├── fn_3.c
│   │       ├── fn_4.c
│   │       ├── fn_5.c
│   │       ├── fn_6.c
│   │       ├── fn_7.c
│   │       ├── fn_8.c
│   │       ├── fn_9.c
│   │       ├── fn_ampersand.c
│   │       └── fn_asterisk.c
│   └── main.c
└── License
└── Makefile
└── README.md
```
