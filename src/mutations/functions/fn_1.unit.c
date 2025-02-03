#include "../mod.h"
#include <cmocka.h>
#include <string.h>

// Caesar Cipher with shift 3
void fn_1_up(char* str);
void fn_1_down(char* str);

// Test cases for Caesar Cipher (fn_1_up and fn_1_down)

static void test_fn_1_up_basic(void** state) {
  char str[] = "abcxyzABCXYZ";
  char expected[] = "defabcDEFABC";
  fn_1_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_1_down_basic(void** state) {
  char str[] = "defabcDEFABC";
  char expected[] = "abcxyzABCXYZ";
  fn_1_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_1_up_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_1_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_1_down_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_1_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_1_up_null_input(void** state) {
  fn_1_up(NULL); // Just check that it doesn't crash
}

static void test_fn_1_down_null_input(void** state) {
  fn_1_down(NULL); // Just check that it doesn't crash
}

static void test_fn_1_up_non_alpha(void** state) {
  char str[] = "123 !@#";
  char expected[] = "123 !@#";
  fn_1_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_1_down_non_alpha(void** state) {
  char str[] = "123 !@#";
  char expected[] = "123 !@#";
  fn_1_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_1_up_mixed(void** state) {
  char str[] = "Hello World!";
  char expected[] = "Khoor Zruog!";
  fn_1_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_1_down_mixed(void** state) {
  char str[] = "Khoor Zruog!";
  char expected[] = "Hello World!";
  fn_1_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_1_up_down_combined(void** state) {
  char str[] = "TestString123";
  char original[sizeof(str)];
  strncpy(original, str, sizeof(original));
  original[sizeof(original) - 1] = '\0';
  fn_1_up(str);
  fn_1_down(str);
  assert_string_equal(original, str);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fn_1_up_basic),
      cmocka_unit_test(test_fn_1_down_basic),
      cmocka_unit_test(test_fn_1_up_empty_string),
      cmocka_unit_test(test_fn_1_down_empty_string),
      cmocka_unit_test(test_fn_1_up_null_input),
      cmocka_unit_test(test_fn_1_down_null_input),
      cmocka_unit_test(test_fn_1_up_non_alpha),
      cmocka_unit_test(test_fn_1_down_non_alpha),
      cmocka_unit_test(test_fn_1_up_mixed),
      cmocka_unit_test(test_fn_1_down_mixed),
      cmocka_unit_test(test_fn_1_up_down_combined),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
