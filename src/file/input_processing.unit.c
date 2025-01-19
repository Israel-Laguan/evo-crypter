#include "input_processing.h"
#include "utils.h"
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Mock version of apply_mutations_to_chunk
// cppcheck-suppress unusedFunction
void* __wrap_apply_mutations_to_chunk( // NOLINT(readability-identifier-naming)
    void* arg, const char* generations, bool decrypt) {
  // Simulate mutation by reversing the string, excluding the newline character,
  // if present
  ChunkProcessingArgs* args = (ChunkProcessingArgs*)arg;
  if (args->buffer == NULL) {
    return NULL;
  }
  int len = strlen(args->buffer);
  int newline_pos = -1;

  // Find the position of the newline character, if it exists
  if (args->buffer[len - 1] == '\n') {
    newline_pos = len - 1;
    len--;
  }

  for (int i = 0; i < len / 2; i++) {
    char temp = args->buffer[i];
    args->buffer[i] = args->buffer[len - i - 1];
    args->buffer[len - i - 1] = temp;
  }

  // Restore the newline character to its original position
  if (newline_pos != -1) {
    for (int i = newline_pos; i > len; i--) {
      args->buffer[i] = args->buffer[i - 1];
    }
    args->buffer[len] = '\n';
  }

  return NULL;
}

// Helper function to create a temporary file with specific content
static char* create_temp_file(const char* content) {
  char template[] = "/tmp/evo_test_XXXXXX";
  int fd = mkstemp(template);
  if (fd == -1) {
    return NULL;
  }
  write(fd, content, strlen(content));
  close(fd);
  return strdup(template);
}

// Test cases for process_input_single_thread

static void test_process_input_single_thread_encryption(void** state) {
  char* input_file = create_temp_file("hello\nworld\n");
  char output_file[] = "/tmp/evo_test_output_XXXXXX";
  mkstemp(output_file); // Create temp file without closing the fd

  process_input_single_thread(input_file, output_file, "1", false);

  FILE* output = fopen(output_file, "r");
  char buffer[1024];
  fgets(buffer, sizeof(buffer), output);
  assert_string_equal("olleh\n", buffer);
  fgets(buffer, sizeof(buffer), output);
  assert_string_equal("dlrow\n", buffer);
  fclose(output);

  remove(input_file);
  remove(output_file);
  free(input_file);
}

static void test_process_input_single_thread_decryption(void** state) {
  char* input_file = create_temp_file("olleh\ndlrow\n");
  char output_file[] = "/tmp/evo_test_output_XXXXXX";
  mkstemp(output_file); // Create temp file without closing the fd

  process_input_single_thread(input_file, output_file, "1", true);

  FILE* output = fopen(output_file, "r");
  char buffer[1024];
  fgets(buffer, sizeof(buffer), output);
  assert_string_equal("hello\n", buffer);
  fgets(buffer, sizeof(buffer), output);
  assert_string_equal("world\n", buffer);
  fclose(output);

  remove(input_file);
  remove(output_file);
  free(input_file);
}

// Test cases for process_input_multi_thread

static void test_process_input_multi_thread_encryption(void** state) {
  char* input_file = create_temp_file("hello\nworld\n");
  char output_file[] = "/tmp/evo_test_output_XXXXXX";
  mkstemp(output_file); // Create temp file without closing the fd

  process_input_multi_thread(input_file, output_file, "1", false, 2);

  FILE* output = fopen(output_file, "r");
  char buffer[1024];
  fgets(buffer, sizeof(buffer), output);
  assert_string_equal("olleh\n", buffer);
  fgets(buffer, sizeof(buffer), output);
  assert_string_equal("dlrow\n", buffer);
  fclose(output);

  remove(input_file);
  remove(output_file);
  free(input_file);
}

static void test_process_input_multi_thread_decryption(void** state) {
  char* input_file = create_temp_file("olleh\ndlrow\n");
  char output_file[] = "/tmp/evo_test_output_XXXXXX";
  mkstemp(output_file); // Create temp file without closing the fd

  process_input_multi_thread(input_file, output_file, "1", true, 2);

  FILE* output = fopen(output_file, "r");
  char buffer[1024];
  fgets(buffer, sizeof(buffer), output);
  assert_string_equal("hello\n", buffer);
  fgets(buffer, sizeof(buffer), output);
  assert_string_equal("world\n", buffer);
  fclose(output);

  remove(input_file);
  remove(output_file);
  free(input_file);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_process_input_single_thread_encryption),
      cmocka_unit_test(test_process_input_single_thread_decryption),
      cmocka_unit_test(test_process_input_multi_thread_encryption),
      cmocka_unit_test(test_process_input_multi_thread_decryption),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
