#include "../mod.h"
#include <cmocka.h>
#include <ctype.h>
#include <string.h>

// Function prototypes
void fn_9_up(char* str);
void fn_9_down(char* str);

// Test cases for Atbash Cipher (fn_9_up and fn_9_down)

static void test_fn_9_up_basic(void** state) {
  char str[] = "Hello World";
  char expected[] = "Svool Dliow";
  fn_9_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_9_down_basic(void** state) {
  char str[] = "Svool Dliow";
  char expected[] = "Hello World";
  fn_9_down(str);
  assert_string_equal(expected, str);
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

static void test_fn_9_up_non_alpha(void** state) {
  char str[] = "123 !@#";
  char expected[] = "123 !@#";
  fn_9_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_9_down_non_alpha(void** state) {
  char str[] = "123 !@#";
  char expected[] = "123 !@#";
  fn_9_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_9_up_mixed_case(void** state) {
  char str[] = "HeLlO wOrLd";
  char expected[] = "SvOoL dLiOw";
  fn_9_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_9_down_mixed_case(void** state) {
  char str[] = "SvOoL dLiOw";
  char expected[] = "HeLlO wOrLd";
  fn_9_down(str);
  assert_string_equal(expected, str);
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
      cmocka_unit_test(test_fn_9_up_basic),
      cmocka_unit_test(test_fn_9_down_basic),
      cmocka_unit_test(test_fn_9_up_empty_string),
      cmocka_unit_test(test_fn_9_down_empty_string),
      cmocka_unit_test(test_fn_9_up_null_input),
      cmocka_unit_test(test_fn_9_down_null_input),
      cmocka_unit_test(test_fn_9_up_non_alpha),
      cmocka_unit_test(test_fn_9_down_non_alpha),
      cmocka_unit_test(test_fn_9_up_mixed_case),
      cmocka_unit_test(test_fn_9_down_mixed_case),
      cmocka_unit_test(test_fn_9_up_down_combined),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
