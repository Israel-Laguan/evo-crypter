# Algorithm Details for evo-crypter

The `evo-crypter` project uses an iterative, function composition-based encryption scheme that is inspired by the concept of evolutionary mutations in biology. Here's a more detailed explanation of the algorithm:

## 1. Mutation Functions

*   The core of the algorithm lies in the mutation functions, which are defined in `src/mutations/mod.c`.
*   Each mutation function comes in a pair:
		*   `fn_<mutation_identifier>_up`: Used for encryption.
		*   `fn_<mutation_identifier>_down`: Used for decryption.
*   `<mutation_identifier>` is a unique symbol (e.g., a number, letter, or special character like # or \*) that identifies the mutation.
*   These functions take a string (representing a chunk of the file being processed) as input and modify it in place.
*   It is **crucial** that `fn_<mutation_identifier>_down` is the exact inverse of `fn_<mutation_identifier>_up`. Otherwise, decryption will not correctly restore the original data.

## 2. Generation Sequence

*   The user provides a comma-separated string (e.g., "1,a,#,4") that determines the sequence of mutations to be applied. This is called the "generation sequence."
*   **The length of the generation sequence determines the number of iterations (generations) the mutations will be applied.** For example, if the generation sequence is "1,2", the sequence "1,2" will be applied twice to each chunk of the input file.
*   The generation sequence is passed to `evo-crypter` using the `--generations` command-line argument.

## 3. Encryption Process

1. **Input:** The input file is read in chunks of a predefined size (see `BUFFER_SIZE` in the code).
2. **Mutation Dispatch:** The `apply_mutation_up` function acts as a dispatcher. Based on the current symbol in the generation sequence, it selects the appropriate `fn_<mutation_identifier>_up` function to apply.
3. **Mutation Application:** The selected `fn_<mutation_identifier>_up` function is called, modifying the current data chunk.
4. **Iteration:** Steps 2 and 3 are repeated for each symbol in the generation sequence. This effectively applies multiple mutations in the specified order.
5. **Generations:** Steps 2-4 are repeated for a number of times equal to the length of the generation sequence. Each iteration represents a "generation" of mutation.
6. **Output:** The transformed data chunk is written to the output file (named `encrypted.txt` by default).

## 4. Decryption Process

1. **Input:** The encrypted file is read in chunks.
2. **Reverse Dispatch:** The `apply_mutation_down` function acts as a dispatcher, similar to `apply_mutation_up`, but it selects the corresponding `fn_<mutation_identifier>_down` function.
3. **Reverse Mutation Application:** The `fn_<mutation_identifier>_down` functions are applied in the **reverse** order compared to the encryption process. This is crucial for correct decryption.
4. **Iteration:** Steps 2 and 3 are repeated for each symbol in the reversed generation sequence.
5. **Generations:** Steps 2-4 are repeated for the same number of generations as the encryption.
6. **Output:** The decrypted data chunk is written to the output file (named `decrypted.txt` by default).

## 5. Multi-threading

*   `evo-crypter` supports multi-threaded processing to improve performance.
*   The `--threads` command-line argument controls the number of threads used.
*   The input file is divided into chunks, and each thread processes a chunk independently.

## Example

Let's say the generation sequence is "1,a" and the input file contains "Hello".

**Encryption:**

1. **Generation 1:**
		*   `fn_1_up` is applied to "Hello" (let's assume it shifts letters by 1: "Hello" -> "Ifmmp").
		*   `fn_a_up` is applied to "Ifmmp" (let's assume it converts to uppercase: "Ifmmp" -> "IFMMP").
2. **Generation 2:**
		*   `fn_1_up` is applied to "IFMMP" (shifted by 1: "IFMMP" -> "JGNNQ").
		*   `fn_a_up` is applied to "JGNNQ" (converted to uppercase: "JGNNQ" -> "JGNNQ").
3. The output is "JGNNQ".

**Decryption:**

1. **Generation 1:**
		*   `fn_a_down` is applied to "JGNNQ" (converted to lowercase: "JGNNQ" -> "jgnnq").
		*   `fn_1_down` is applied to "jgnnq" (shifted back by 1: "jgnnq" -> "ifmmp").
2. **Generation 2:**
		*   `fn_a_down` is applied to "ifmmp" (converted to lowercase: "ifmmp" -> "ifmmp").
		*   `fn_1_down` is applied to "ifmmp" (shifted back by 1: "ifmmp" -> "hello").
3. The output is "hello".
