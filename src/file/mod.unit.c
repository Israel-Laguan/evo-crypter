#include "mod.h"
#include "input_processing.h"
#include "utils.h"
#include <cmocka.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Mock version of process_input_single_thread
void __wrap_process_input_single_thread( // NOLINT(readability-identifier-naming)
    const char* input_file, const char* output_file, const char* generations,
    bool decrypt) {
  check_expected(input_file);
  check_expected(output_file);
  check_expected(generations);
  check_expected(decrypt);
  // Simulate processing by creating an empty output file
  FILE* output = fopen(output_file, "w");
  fclose(output);
}

// Mock version of process_input_multi_thread
void __wrap_process_input_multi_thread( // NOLINT(readability-identifier-naming)
    const char* input_file, const char* output_file, const char* generations,
    bool decrypt, int threads) {
  check_expected(input_file);
  check_expected(output_file);
  check_expected(generations);
  check_expected(decrypt);
  check_expected(threads);
  // Simulate processing by creating an empty output file
  FILE* output = fopen(output_file, "w");
  fclose(output);
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

// Test cases for evolve_file

static void test_evolve_file_single_thread(void** state) {
  char* input_file = create_temp_file("Test input");
  char output_file[] = "/tmp/evo_test_output_XXXXXX";
  mkstemp(output_file);

  expect_string(__wrap_process_input_single_thread, input_file, input_file);
  expect_string(__wrap_process_input_single_thread, output_file, output_file);
  expect_string(__wrap_process_input_single_thread, generations, "1,2,3");
  expect_value(__wrap_process_input_single_thread, decrypt, false);

  evolve_file(input_file, output_file, "1,2,3", 1, false);

  remove(input_file);
  remove(output_file);
  free(input_file);
}

static void test_evolve_file_multi_thread(void** state) {
  char* input_file = create_temp_file("Test input");
  char output_file[] = "/tmp/evo_test_output_XXXXXX";
  mkstemp(output_file);

  expect_string(__wrap_process_input_multi_thread, input_file, input_file);
  expect_string(__wrap_process_input_multi_thread, output_file, output_file);
  expect_string(__wrap_process_input_multi_thread, generations, "a,b,c");
  expect_value(__wrap_process_input_multi_thread, decrypt, true);
  expect_value(__wrap_process_input_multi_thread, threads, 4);

  evolve_file(input_file, output_file, "a,b,c", 4, true);

  remove(input_file);
  remove(output_file);
  free(input_file);
}

static void test_evolve_file_file_not_found(void** state) {
  // Redirect stderr to suppress error message during test
  int stderr_copy = dup(STDERR_FILENO);
  freopen("/dev/null", "w", stderr); // cppcheck-suppress ignoredReturnValue

  // Call the function and check the exit code in a child process
  pid_t pid = fork();
  if (pid == 0) {
    // Child process
    evolve_file("nonexistent_file.txt", "output.txt", "1,2,3", 1, false);
    exit(0); // Should not reach here if evolve_file exits
  } else if (pid > 0) {
    // Parent process
    int status;
    waitpid(pid, &status, 0);
    assert_true(WIFEXITED(status));
    assert_int_not_equal(0, WEXITSTATUS(status));
  } else {
    fail_msg("Fork failed");
  }

  // Restore stderr
  dup2(stderr_copy, STDERR_FILENO);
  close(stderr_copy);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_evolve_file_single_thread),
      cmocka_unit_test(test_evolve_file_multi_thread),
      cmocka_unit_test(test_evolve_file_file_not_found),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
