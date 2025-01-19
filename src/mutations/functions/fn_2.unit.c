#include "../mod.h"
#include <cmocka.h>
#include <string.h>

// Function prototypes
void fn_2_up(char* str);
void fn_2_down(char* str);

// Test cases for Reverse String (fn_2_up and fn_2_down)

static void test_fn_2_up_basic(void** state) {
  char str[] = "abcdefg";
  char expected[] = "gfedcba";
  fn_2_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_2_down_basic(void** state) {
  char str[] = "gfedcba";
  char expected[] = "abcdefg";
  fn_2_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_2_up_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_2_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_2_down_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_2_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_2_up_null_input(void** state) {
  fn_2_up(NULL); // Just check that it doesn't crash
}

static void test_fn_2_down_null_input(void** state) {
  fn_2_down(NULL); // Just check that it doesn't crash
}

static void test_fn_2_up_one_char(void** state) {
  char str[] = "a";
  char expected[] = "a";
  fn_2_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_2_down_one_char(void** state) {
  char str[] = "a";
  char expected[] = "a";
  fn_2_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_2_up_newline(void** state) {
  char str[] = "abc\nxyz";
  char expected[] = "zyx\ncba";
  fn_2_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_2_down_newline(void** state) {
  char str[] = "zyx\ncba";
  char expected[] = "abc\nxyz";
  fn_2_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_2_up_down_combined(void** state) {
  char str[] = "TestString123\nAnotherLine";
  char expected[] = "TestString123\nAnotherLine";
  fn_2_up(str);
  fn_2_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_2_up_with_symbols(void** state) {
  char str[] = "Hello World! 123 #$%";
  char expected[] = "%$# 321 !dlroW olleH";
  fn_2_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_2_down_with_symbols(void** state) {
  char str[] = "%$# 321 !dlroW olleH";
  char expected[] = "Hello World! 123 #$%";
  fn_2_down(str);
  assert_string_equal(expected, str);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fn_2_up_basic),
      cmocka_unit_test(test_fn_2_down_basic),
      cmocka_unit_test(test_fn_2_up_empty_string),
      cmocka_unit_test(test_fn_2_down_empty_string),
      cmocka_unit_test(test_fn_2_up_null_input),
      cmocka_unit_test(test_fn_2_down_null_input),
      cmocka_unit_test(test_fn_2_up_one_char),
      cmocka_unit_test(test_fn_2_down_one_char),
      cmocka_unit_test(test_fn_2_up_newline),
      cmocka_unit_test(test_fn_2_down_newline),
      cmocka_unit_test(test_fn_2_up_down_combined),
      cmocka_unit_test(test_fn_2_up_with_symbols),
      cmocka_unit_test(test_fn_2_down_with_symbols),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
