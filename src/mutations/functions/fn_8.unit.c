#include "../mod.h"
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void fn_8_up(char* str);
void fn_8_down(char* str);

// Test cases for Custom Function (fn_8_up and fn_8_down)

static void test_fn_8_up_basic(void** state) {
  char str[] = "abcdefghi";
  char expected[] = "abcXdefXghi";
  fn_8_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_down_basic(void** state) {
  char str[] = "abcXdefXghi";
  char expected[] = "abcdefghi";
  fn_8_down(str);
  assert_string_equal(expected, str);
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
  char expected[] = "a";
  fn_8_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_down_one_char(void** state) {
  char str[] = "a";
  char expected[] = "a";
  fn_8_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_up_boundary(void** state) {
  char str[] = "abcdef";
  char expected[] = "abcXdef";
  fn_8_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_down_boundary(void** state) {
  char str[] = "abcXdef";
  char expected[] = "abcdef";
  fn_8_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_down_x_at_end(void** state) {
  char str[] = "abcXdefX";
  char expected[] = "abcdef";
  fn_8_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_up_no_insertion(void** state) {
  char str[] = "ab";
  char expected[] = "ab";
  fn_8_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_down_no_removal(void** state) {
  char str[] = "ab";
  char expected[] = "ab";
  fn_8_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_up_x_in_input(void** state) {
  char str[] = "abcXdef";
  char expected[] = "abcXXdeXf";
  fn_8_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_down_x_in_input(void** state) {
  char str[] = "abcXXdeXf";
  char expected[] = "abcdef";
  fn_8_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_8_up_down_combined(void** state) {
  char str[] = "TestStringWithSymbols!@#123";
  char original[strlen(str) + 1];
  strncpy(original, str, sizeof(original));
  original[sizeof(original) - 1] = '\0';
  fn_8_up(str);
  fn_8_down(str);
  assert_string_equal(original, str);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fn_8_up_basic),
      cmocka_unit_test(test_fn_8_down_basic),
      cmocka_unit_test(test_fn_8_up_empty_string),
      cmocka_unit_test(test_fn_8_down_empty_string),
      cmocka_unit_test(test_fn_8_up_null_input),
      cmocka_unit_test(test_fn_8_down_null_input),
      cmocka_unit_test(test_fn_8_up_one_char),
      cmocka_unit_test(test_fn_8_down_one_char),
      cmocka_unit_test(test_fn_8_up_boundary),
      cmocka_unit_test(test_fn_8_down_boundary),
      cmocka_unit_test(test_fn_8_down_x_at_end),
      cmocka_unit_test(test_fn_8_up_no_insertion),
      cmocka_unit_test(test_fn_8_down_no_removal),
      cmocka_unit_test(test_fn_8_up_x_in_input),
      cmocka_unit_test(test_fn_8_down_x_in_input),
      cmocka_unit_test(test_fn_8_up_down_combined),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
