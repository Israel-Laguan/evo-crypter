#include "utils.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Helper function to create a temporary file for testing
static char* create_temp_file(const char* content) {
  char* temp_filename = strdup("test_file_XXXXXX");
  if (!temp_filename) {
    return NULL;
  }
  int fd = mkstemp(temp_filename);
  if (fd == -1) {
    free(temp_filename);
    return NULL;
  }
  if (content) {
    write(fd, content, strlen(content));
  }
  close(fd);
  return temp_filename;
}

// Test cases for reverse_generations

static void test_reverse_generations_empty_string(void** state) {
  char str[] = "";
  reverse_generations(str);
  assert_string_equal("", str);
}

static void test_reverse_generations_single_char(void** state) {
  char str[] = "a";
  reverse_generations(str);
  assert_string_equal("a", str);
}

static void test_reverse_generations_even_length(void** state) {
  char str[] = "1234";
  reverse_generations(str);
  assert_string_equal("4321", str);
}

static void test_reverse_generations_odd_length(void** state) {
  char str[] = "abcde";
  reverse_generations(str);
  assert_string_equal("edcba", str);
}

static void test_reverse_generations_special_chars(void** state) {
  char str[] = "#*$,.";
  reverse_generations(str);
  assert_string_equal(".,$*#", str);
}

// Test cases for file_exists

static void test_file_exists_existing_file(void** state) {
  char* temp_filename = create_temp_file("This is a test file.");
  assert_non_null(temp_filename);
  assert_true(file_exists(temp_filename));
  remove(temp_filename); // Delete the temporary file
  free(temp_filename);
}

static void test_file_exists_nonexistent_file(void** state) {
  assert_false(file_exists("nonexistent_file.txt"));
}

static void test_file_exists_empty_file(void** state) {
  char* temp_filename = create_temp_file("");
  assert_non_null(temp_filename);
  assert_true(file_exists(temp_filename));
  remove(temp_filename); // Delete the temporary file
  free(temp_filename);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_reverse_generations_empty_string),
      cmocka_unit_test(test_reverse_generations_single_char),
      cmocka_unit_test(test_reverse_generations_even_length),
      cmocka_unit_test(test_reverse_generations_odd_length),
      cmocka_unit_test(test_reverse_generations_special_chars),
      cmocka_unit_test(test_file_exists_existing_file),
      cmocka_unit_test(test_file_exists_nonexistent_file),
      cmocka_unit_test(test_file_exists_empty_file),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
