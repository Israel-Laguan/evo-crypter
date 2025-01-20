#include "../mod.h"
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void fn_8_up(char* str);
void fn_8_down(char* str);

// Test cases for XOR with Position-Based Key

static void test_fn_8_up_down(void** state) {
  (void)state;
  char test_str[] = "HelloWorld";
  char original_str[] = "HelloWorld";

  fn_8_up(test_str);
  fn_8_down(test_str);

  assert_string_equal(test_str, original_str);
}

static void test_fn_8_up_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_8_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_down_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_8_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_up_null_input(void** state) {
  fn_8_up(NULL); // Just check that it doesn't crash
}

static void test_fn_8_down_null_input(void** state) {
  fn_8_down(NULL); // Just check that it doesn't crash
}

static void test_fn_8_up_one_char(void** state) {
  char str[] = "a";
  char expected[] = "A";
  fn_8_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_down_one_char(void** state) {
  char str[] = "A";
  char expected[] = "a";
  fn_8_down(str);
  assert_string_equal(expected, str);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fn_8_up_down),
      cmocka_unit_test(test_fn_8_up_empty_string),
      cmocka_unit_test(test_fn_8_down_empty_string),
      cmocka_unit_test(test_fn_8_up_null_input),
      cmocka_unit_test(test_fn_8_down_null_input),
      cmocka_unit_test(test_fn_8_up_one_char),
      cmocka_unit_test(test_fn_8_down_one_char),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
