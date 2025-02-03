# Roadmap for evo-crypter

This document outlines the planned development roadmap for `evo-crypter`. The project is currently in the **Fledgling** stage (v0.2.0).

| Version | Codename     | Features                                                                                                                                                                                                                                           | Status       |
| :------ | :----------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :----------- |
| 0.1.0   | Hatchling    | - Basic encryption/decryption with a sequence of functions. <br> - Single/multi-threaded operation. <br> - Iterative application of functions (generations = length of order string). <br> - Evolutionary-themed naming. <br> - Project identity (evo-crypter, mascot). <br> - Refactor of the code and documentation <br> - CI/CD with GitHub Actions. <br> - CMake build system. <br> - Version management. <br> - Code quality tools (clang-format, clang-tidy, cppcheck). <br> - Basic documentation. | Completed    |
| 0.2.0   | Fledgling    | - Add tests, including unit tests, integration tests, and property-based testing. <br> - Improve error handling and reporting. <br> - Implement the Base64 mutation function.                                                                              | In Progress  |
| 0.3.0   | Slithering   | - Implement the function splitting and merging as a form of key management ( `-k` flag). <br> - Basic obfuscation of split function files. <br> - Implement file splitting/merging for enhanced multi-threading.                                        | Planned      |
| 0.4.0   | Raptor       | - Add a feedback mechanism (fitness function) to guide the evolutionary process. <br> - Allow optional parameters to customize the behavior of mutation functions (e.g., shift value for Caesar cipher).                                             | Planned      |
| 0.5.0   | Drake        | - Implement dynamic loading of mutation functions from shared libraries. <br> - Improve the security and efficiency of the core encryption/decryption algorithm.                                                                                            | Planned      |
| 0.6.0   | Dragon       | - Create a simple GUI for `evo-crypter`. <br> - Improve documentation and create tutorials.                                                                                                                                               | Planned      |
| 0.7.0   | Flying       | - Add a plugin system to allow users to easily extend `evo-crypter` with custom mutation functions and features. <br> - Introduce a command-line option to generate random, secure generation sequences.                                               | Planned      |
| 0.8.0   | Wyvern       | - Implement a network mode where `evo-crypter` can encrypt/decrypt data streams over a network connection. <br> - Add support for authenticated encryption.                                                                                              | Planned      |
| 0.9.0   | Old          | - Conduct a security audit and address any identified vulnerabilities. <br> - Optimize performance for large files and high parallelism levels.                                                                                                           | Planned      |
| 1.0.0   | Elder        | - Long-term support and maintenance. <br> - Update dependencies. <br> - Address bug fixes and minor improvements.                                                                                                                                    | Planned      |
| 1.1.0   | Ancient      | - Long-term support and maintenance. <br> - Update dependencies. <br> - Address bug fixes and minor improvements.                                                                                                                                    | Planned      |

## Feature Details

### Slithering (0.3.0)

*   **Function Splitting and Merging:** This feature will introduce a form of key management by allowing the splitting of mutation functions into separate files. The order in which these files are merged will act as a key.
*   **Basic Obfuscation:** Implement basic obfuscation techniques to make it more difficult to reverse-engineer the split function files.
*   **File Splitting/Merging:** Enhance multi-threading by splitting the input file into smaller chunks that can be processed independently and then merged back together.

### Raptor (0.4.0)

*   **Feedback Mechanism (Fitness Function):** Introduce a way to evaluate the effectiveness of the encryption process. This could involve analyzing the entropy or randomness of the encrypted data to guide the evolutionary process toward stronger encryption.
*   **Optional Parameters for Mutation Functions:** Allow users to customize the behavior of mutation functions by providing optional parameters (e.g., the shift value for a Caesar cipher).

### Drake (0.5.0)

*   **Dynamic Loading of Mutation Functions:** Implement a system to load mutation functions from shared libraries (e.g., `.so` files on Linux or `.dll` files on Windows). This will make it easier to extend `evo-crypter` with new mutation functions without recompiling the entire project.
*   **Security and Efficiency Improvements:** Refactor the core encryption/decryption algorithm to improve its security and performance. This may involve using more robust cryptographic primitives or optimizing the existing code.

### Dragon (0.6.0)

*   **GUI:** Create a simple graphical user interface (GUI) for `evo-crypter` to make it more user-friendly.
*   **Documentation and Tutorials:** Improve the project's documentation and create tutorials to help users get started with `evo-crypter`.

### Flying (0.7.0)

*   **Plugin System:** Develop a plugin system that allows users to easily extend `evo-crypter` with custom mutation functions, fitness functions, and other features.
*   **Random Generation Sequence Generation:** Add a command-line option to generate random, secure generation sequences.

### Wyvern (0.8.0)

*   **Network Mode:** Implement a network mode where `evo-crypter` can encrypt and decrypt data streams over a network connection.
*   **Authenticated Encryption:** Add support for authenticated encryption to ensure both confidentiality and data integrity.

### Old (0.9.0)

*   **Security Audit:** Conduct a thorough security audit to identify and address any potential vulnerabilities.
*   **Performance Optimization:** Optimize the performance of `evo-crypter` for large files and high levels of parallelism.

### Elder (1.0.0) and Ancient (1.1.0)

*   **Long-Term Support and Maintenance:** These versions will focus on long-term support, including updating dependencies, addressing bug fixes, and making minor improvements.

This roadmap is subject to change based on community feedback and development progress.
