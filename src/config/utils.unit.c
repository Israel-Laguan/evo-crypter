#include "utils.h"
#include <cmocka.h>
#include <stdio.h>
#include <string.h>

// Test cases for print_usage
// (Testing void functions that print to stdout/stderr can be tricky.
// One approach is to redirect stdout/stderr to a file and then check the file's
// contents. However, for simplicity, we will just call the function and verify
// it doesn't crash.)

static void test_print_usage_no_crash(void** state) {
  print_usage("evo"); // Just check that it doesn't crash
}

// Test cases for is_valid_generations

static void test_is_valid_generations_valid(void** state) {
  assert_true(is_valid_generations("1,2,3,a,b,c,#,*"));
}

static void test_is_valid_generations_invalid_char(void** state) {
  assert_false(is_valid_generations("1,2,!,$,%"));
}

static void test_is_valid_generations_empty(void** state) {
  assert_false(is_valid_generations(""));
}

static void test_is_valid_generations_only_commas(void** state) {
  assert_false(is_valid_generations(",,,"));
}

static void test_is_valid_generations_valid_with_uppercase(void** state) {
  assert_false(is_valid_generations("1,A,2,B,3,C,#,*"));
}

static void test_is_valid_generations_mixed_valid_invalid(void** state) {
  assert_false(is_valid_generations("1,2,a,!,b,$,#,%,*"));
}

static void test_is_valid_generations_null_input(void** state) {
  assert_false(is_valid_generations(NULL));
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_print_usage_no_crash),
      cmocka_unit_test(test_is_valid_generations_valid),
      cmocka_unit_test(test_is_valid_generations_invalid_char),
      cmocka_unit_test(test_is_valid_generations_empty),
      cmocka_unit_test(test_is_valid_generations_only_commas),
      cmocka_unit_test(test_is_valid_generations_valid_with_uppercase),
      cmocka_unit_test(test_is_valid_generations_mixed_valid_invalid),
      cmocka_unit_test(test_is_valid_generations_null_input),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
