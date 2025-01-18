# evo-crypter

## Overview

**evo-crypter** is a customizable file encryption tool that utilizes an evolutionary approach to apply a series of transformation functions (mutations) to data. The core idea is to simulate a simplified evolutionary process where a sequence of mutations, defined by a "generation sequence," is applied iteratively to a file's contents. This project draws inspiration from the concept of genetic mutations and applies it to the realm of data encryption.

The project's mascot is **Evo**, a friendly dinosaur/reptile creature representing the software's evolution. Evo progresses through various stages, each symbolizing a version of the software. These stages are: Hatchling, Fledgling, Slithering, Raptor, Drake, Dragon, Flying, Wyvern, Old, Elder, and Ancient.

## Algorithm

The algorithm can be described as an iterative, function composition-based encryption scheme inspired by evolutionary mutations. The user provides a comma-separated string (e.g., "1,a,#,4") that specifies the sequence of mutations to be applied. The length of the generation sequence determines the number of iterations (generations) the mutations will be applied. Each iteration represents a "generation" of mutation.

**Security Considerations:**

*   The security of this system relies on the strength of the individual mutation functions and the secrecy of the generation sequence.
*   **Do not** commit sensitive encryption functions or keys to a public repository.
*   This project is primarily for educational and experimental purposes. For real-world security applications, consider using established and thoroughly vetted encryption libraries.

## Roadmap

The project is currently in the **Fledgling** stage (v0.2.0). Here's a brief overview of the planned development stages:

*   **Fledgling (0.2.0):** Focus on testing, error handling, and implementing a Base64 mutation.
*   **Slithering (0.3.0):** Introduce function splitting/merging for key management and basic obfuscation.
*   **Raptor (0.4.0):** Add a feedback mechanism and allow optional parameters for mutation functions.
*   **Drake (0.5.0):** Implement dynamic loading of mutation functions and improve security/efficiency.
*   **Dragon (0.6.0):** Create a simple GUI and improve documentation.
*   **Flying (0.7.0):** Develop a plugin system and add an option for random generation sequence generation.
*   **Wyvern (0.8.0):** Implement a network mode and support authenticated encryption.
*   **Old (0.9.0):** Conduct a security audit and optimize performance.
*   **Elder (1.0.0) - Ancient (1.1.0):** Long-term support and maintenance.

For a more detailed roadmap, see `docs/ROADMAP.md`.

## Getting Started

### Prerequisites

*   **CMake** (version 3.10 or higher)
*   **A C compiler** (e.g., GCC, Clang, MSVC)
*   **Make** (or a compatible build tool, like Ninja)
*   **git**

## Setup

1. Clone the repository:

    ```bash
    git clone https://github.com/Israel-Laguan/evo-crypter.git
    cd evo-crypter
    ```

2. Build the project using CMake:

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
*   `<generation_sequence>`: A comma-separated string representing the sequence of mutations to apply (e.g., "1,2,a,#").
*   `[-d]`: Optional flag to decrypt instead of encrypt.

Example:

```bash
./evo --input test_input.txt --threads 4 --generations 1,2,#
./evo --input encrypted.txt --threads 4 --generations 1,2,# -d
```

## Scripts

*   `build.sh`: Builds the executable.
*   `lint.sh`: Runs the linters for static code analysis.
*   `test.sh`: Runs the unit tests.
*   `update_version.sh`: Updates the project version and optionally creates a Git tag.

## Contributing

We welcome contributions! See `docs/CONTRIBUTING.md` for guidelines.

## Versioning

`evo-crypter` follows Semantic Versioning (SemVer). See `docs/VERSIONING.md` for details on the versioning strategy and automated workflows.

*   The version number is stored in the `version.txt` file.
*   Version updates are typically handled automatically by the GitHub Actions workflows.
*   If you need to update the version manually, you can edit `version.txt` and run `./scripts/update_version.sh <new_version>`.

## Acknowledges

- [code coverage with cmake article](https://www.google.com/url?sa=E&q=https%3A%2F%2Fdanielsieger.com%2Fblog%2F2024%2F08%2F03%2Fcode-coverage-with-cmake.html)

## License

`evo-crypter` is licensed under the MIT License. See the `LICENSE` file for more details.
