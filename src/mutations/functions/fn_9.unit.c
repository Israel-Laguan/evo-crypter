#include "../mod.h"
#include <cmocka.h>
#include <ctype.h>
#include <string.h>

// Function prototypes
void fn_9_up(char* str);
void fn_9_down(char* str);

// Test Reverse Words Cypher

static void test_fn_9_up_down(void** state) {
  (void)state;
  char test_str[] = "Hello World";
  char original_str[] = "Hello World";

  fn_9_up(test_str);
  fn_9_down(test_str);

  assert_string_equal(test_str, original_str);
}

static void test_fn_9_up_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_9_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_9_down_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_9_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_9_up_null_input(void** state) {
  fn_9_up(NULL); // Just check that it doesn't crash
}

static void test_fn_9_down_null_input(void** state) {
  fn_9_down(NULL); // Just check that it doesn't crash
}

static void test_fn_9_up_down_combined(void** state) {
  char str[] = "TestString123";
  char original[strlen(str) + 1];
  strncpy(original, str, sizeof(original));
  fn_9_up(str);
  fn_9_down(str);
  assert_string_equal(original, str);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fn_9_up_down),
      cmocka_unit_test(test_fn_9_up_empty_string),
      cmocka_unit_test(test_fn_9_down_empty_string),
      cmocka_unit_test(test_fn_9_up_null_input),
      cmocka_unit_test(test_fn_9_down_null_input),
      cmocka_unit_test(test_fn_9_up_down_combined),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
