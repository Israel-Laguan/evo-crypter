#include "mod.h"
#include <cmocka.h>

#define BUFFER_SIZE 1024

// Mock functions for apply_mutation_up, apply_mutation_down, and
// reverse_generations
// cppcheck-suppress unusedFunction
void __wrap_apply_mutation_up( // NOLINT(readability-identifier-naming)
    char symbol, char* str) {
  check_expected(symbol);
  check_expected(str);
}

// cppcheck-suppress unusedFunction
void __wrap_apply_mutation_down( // NOLINT(readability-identifier-naming)
    char symbol, char* str) {
  check_expected(symbol);
  check_expected(str);
}

void __wrap_reverse_generations( // NOLINT(readability-identifier-naming)
    char* generations) {
  check_expected(generations);
}

// Test cases for apply_mutations_to_chunk

static void test_apply_mutations_to_chunk_encryption(void** state) {
  char buffer[BUFFER_SIZE] = "test_string";
  char expected_buffer[BUFFER_SIZE] = "jqluwv_wvhw";
  ChunkProcessingArgs args = {buffer, "1,2", false};

  apply_mutations_to_chunk(&args, "1,2", false);
  assert_string_equal(expected_buffer, buffer);
}

static void test_apply_mutations_to_chunk_decryption(void** state) {
  char buffer[BUFFER_SIZE] = "jqluwv_wvhw";
  char expected_buffer[BUFFER_SIZE] = "test_string";
  ChunkProcessingArgs args = {buffer, "1,2", true};

  // Expect these calls within apply_mutations_to_chunk
  expect_string(__wrap_reverse_generations, generations, "1,2");

  apply_mutations_to_chunk(&args, "1,2", true);
  assert_string_equal(expected_buffer, buffer);
}

static void test_apply_mutations_to_chunk_empty_generations(void** state) {
  char buffer[BUFFER_SIZE] = "test_string";
  char expected_buffer[BUFFER_SIZE] = "test_string";
  ChunkProcessingArgs args = {buffer, "", false};

  apply_mutations_to_chunk(&args, "", false);
  assert_string_equal(expected_buffer, buffer);
}

static void test_apply_mutations_to_chunk_null_buffer(void** state) {
  char* buffer = NULL;
  ChunkProcessingArgs args = {buffer, "1,2", false};

  // Ensure the function handles a NULL buffer gracefully (doesn't crash)
  apply_mutations_to_chunk(&args, "1,2", false);
  // No assertion needed, just checking for no crash
}

static void test_apply_mutations_to_chunk_combined(void** state) {
  char buffer[BUFFER_SIZE] = "Test String";
  char expected_buffer[BUFFER_SIZE] = "Test String";
  ChunkProcessingArgs args_up = {buffer, "1,2,4,5,6,7,8,9,*,#", false};
  ChunkProcessingArgs args_down = {buffer, "1,2,4,5,6,7,8,9,*,#", true};
  expect_string(__wrap_reverse_generations, generations, "1,2,4,5,6,7,8,9,*,#");
  apply_mutations_to_chunk(&args_up, "1,2,4,5,6,7,8,9,*,#", false);
  apply_mutations_to_chunk(&args_down, "1,2,4,5,6,7,8,9,*,#", true);
  assert_string_equal(expected_buffer, buffer);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_apply_mutations_to_chunk_encryption),
      cmocka_unit_test(test_apply_mutations_to_chunk_decryption),
      cmocka_unit_test(test_apply_mutations_to_chunk_empty_generations),
      cmocka_unit_test(test_apply_mutations_to_chunk_null_buffer),
      cmocka_unit_test(test_apply_mutations_to_chunk_combined),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
