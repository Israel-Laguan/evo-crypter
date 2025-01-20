#include "../mod.h"
#include <cmocka.h>
#include <string.h>

// Function prototypes
void fn_5_up(char* str);
void fn_5_down(char* str);

// Test cases for Substitution Cipher (fn_5_up and fn_5_down)

static void test_fn_5_up_down_basic(void** state) {
  (void)state;
  char test_str[] = "HelloWorld";
  char original_str[] = "HelloWorld";

  fn_5_up(test_str);
  fn_5_down(test_str);

  assert_string_equal(test_str, original_str);
}

static void test_fn_5_up_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_5_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_5_down_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_5_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_5_up_null_input(void** state) {
  fn_5_up(NULL); // Just check that it doesn't crash
}

static void test_fn_5_down_null_input(void** state) {
  fn_5_down(NULL); // Just check that it doesn't crash
}

static void test_fn_5_up_down_non_alpha(void** state) {
  (void)state;
  char test_str[] = "!@#$%^&*()";
  char original_str[] = "!@#$%^&*()";

  fn_6_up(test_str);
  fn_6_down(test_str);

  assert_string_equal(test_str, original_str);
}

static void test_fn_5_up_down_combined(void** state) {
  char str[] = "TestStringWithSymbols!@#123";
  char original[sizeof(str)];
  strncpy(original, str, sizeof(original));
  original[sizeof(original) - 1] = '\0';
  fn_5_up(str);
  fn_5_down(str);
  assert_string_equal(original, str);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fn_5_up_down_basic),
      cmocka_unit_test(test_fn_5_up_empty_string),
      cmocka_unit_test(test_fn_5_down_empty_string),
      cmocka_unit_test(test_fn_5_up_null_input),
      cmocka_unit_test(test_fn_5_down_null_input),
      cmocka_unit_test(test_fn_5_up_down_non_alpha),
      cmocka_unit_test(test_fn_5_up_down_combined),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
