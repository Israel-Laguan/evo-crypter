#include "../mod.h"
#include <cmocka.h>
#include <string.h>

// Function prototypes
void fn_6_up(char* str);
void fn_6_down(char* str);

// Test cases for Rail Fence Cipher (fn_6_up and fn_6_down)

static void test_fn_6_up_basic(void** state) {
  char str[] = "helloworld";
  char expected[] = "holelwrdlo";
  fn_6_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_6_down_basic(void** state) {
  char str[] = "holelwrdlo";
  char expected[] = "helloworld";
  fn_6_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_6_up_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_6_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_6_down_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_6_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_6_up_null_input(void** state) {
  fn_6_up(NULL); // Just check that it doesn't crash
}

static void test_fn_6_down_null_input(void** state) {
  fn_6_down(NULL); // Just check that it doesn't crash
}

static void test_fn_6_up_down_combined(void** state) {
  char str[] = "TestStringWithSymbols!@#123";
  char original[sizeof(str)];
  strncpy(original, str, sizeof(original));
  original[sizeof(original) - 1] = '\0';
  fn_6_up(str);
  fn_6_down(str);
  assert_string_equal(original, str);
}

static void test_fn_6_up_single_char(void** state) {
  char str[] = "a";
  char expected[] = "a";
  fn_6_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_6_down_single_char(void** state) {
  char str[] = "a";
  char expected[] = "a";
  fn_6_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_6_up_all_same_rail(void** state) {
  char str[] = "aaaa";
  char expected[] = "aaaa";
  fn_6_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_6_down_all_same_rail(void** state) {
  char str[] = "aaaa";
  char expected[] = "aaaa";
  fn_6_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_6_up_longer_string(void** state) {
  char str[] = "ThisIsALongerTestString";
  char expected[] = "TIortihssLneTsSrniAgetg";
  fn_6_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_6_down_longer_string(void** state) {
  char str[] = "TIortihssLneTsSrniAgetg";
  char expected[] = "ThisIsALongerTestString";
  fn_6_down(str);
  assert_string_equal(expected, str);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fn_6_up_basic),
      cmocka_unit_test(test_fn_6_down_basic),
      cmocka_unit_test(test_fn_6_up_empty_string),
      cmocka_unit_test(test_fn_6_down_empty_string),
      cmocka_unit_test(test_fn_6_up_null_input),
      cmocka_unit_test(test_fn_6_down_null_input),
      cmocka_unit_test(test_fn_6_up_down_combined),
      cmocka_unit_test(test_fn_6_up_single_char),
      cmocka_unit_test(test_fn_6_down_single_char),
      cmocka_unit_test(test_fn_6_up_all_same_rail),
      cmocka_unit_test(test_fn_6_down_all_same_rail),
      cmocka_unit_test(test_fn_6_up_longer_string),
      cmocka_unit_test(test_fn_6_down_longer_string),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
