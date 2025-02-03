#include "../mod.h"
#include <cmocka.h>
#include <string.h>

// Function prototypes
void fn_4_up(char* str);
void fn_4_down(char* str);

// Test cases for ROT13 Cipher (fn_4_up and fn_4_down)

static void test_fn_4_up_basic(void** state) {
  char str[] = "helloworld";
  char expected[] = "uryybjbeyq";
  fn_4_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_4_down_basic(void** state) {
  char str[] = "uryybjbeyq";
  char expected[] = "helloworld";
  fn_4_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_4_up_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_4_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_4_down_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_4_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_4_up_null_input(void** state) {
  fn_4_up(NULL); // Just check that it doesn't crash
}

static void test_fn_4_down_null_input(void** state) {
  fn_4_down(NULL); // Just check that it doesn't crash
}

static void test_fn_4_up_non_alpha(void** state) {
  char str[] = "123 !@#";
  char expected[] = "123 !@#";
  fn_4_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_4_down_non_alpha(void** state) {
  char str[] = "123 !@#";
  char expected[] = "123 !@#";
  fn_4_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_4_up_mixed_case(void** state) {
  char str[] = "Hello World!";
  char expected[] = "Uryyb Jbeyq!";
  fn_4_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_4_down_mixed_case(void** state) {
  char str[] = "Uryyb Jbeyq!";
  char expected[] = "Hello World!";
  fn_4_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_4_up_down_combined(void** state) {
  char str[] = "TestStringWithSymbols!@#123";
  char original[sizeof(str)];
  strncpy(original, str, sizeof(original));
  original[sizeof(original) - 1] = '\0';
  fn_4_up(str);
  fn_4_down(str);
  assert_string_equal(original, str);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fn_4_up_basic),
      cmocka_unit_test(test_fn_4_down_basic),
      cmocka_unit_test(test_fn_4_up_empty_string),
      cmocka_unit_test(test_fn_4_down_empty_string),
      cmocka_unit_test(test_fn_4_up_null_input),
      cmocka_unit_test(test_fn_4_down_null_input),
      cmocka_unit_test(test_fn_4_up_non_alpha),
      cmocka_unit_test(test_fn_4_down_non_alpha),
      cmocka_unit_test(test_fn_4_up_mixed_case),
      cmocka_unit_test(test_fn_4_down_mixed_case),
      cmocka_unit_test(test_fn_4_up_down_combined),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
