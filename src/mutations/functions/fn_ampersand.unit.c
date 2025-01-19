#include "../mod.h"
#include <cmocka.h>
#include <ctype.h>
#include <string.h>

// Function prototypes
void fn_ampersand_up(char* str);
void fn_ampersand_down(char* str);

// Test cases for Baconian Cipher (fn_ampersand_up and fn_ampersand_down)

static void test_fn_ampersand_up_basic(void** state) {
  char str[] = "hello";
  char expected[] = "AABBB AABAA ABBAB ABBAB ABBBB ";
  fn_ampersand_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_ampersand_down_basic(void** state) {
  char str[] = "AABBB AABAA ABBAB ABBAB ABBBB ";
  char expected[] = "HELLO";
  fn_ampersand_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_ampersand_up_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_ampersand_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_ampersand_down_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_ampersand_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_ampersand_up_null_input(void** state) {
  fn_ampersand_up(NULL); // Just check that it doesn't crash
}

static void test_fn_ampersand_down_null_input(void** state) {
  fn_ampersand_down(NULL); // Just check that it doesn't crash
}

static void test_fn_ampersand_up_non_alpha(void** state) {
  char str[] = "123 !@#";
  char expected[] = "";
  fn_ampersand_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_ampersand_down_invalid(void** state) {
  char str[] =
      "AAAAA AAAAA AAAAAA"; // Invalid: more than one space between codes
  char expected[] = "???";
  fn_ampersand_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_ampersand_up_mixed_case(void** state) {
  char str[] = "HeLlO";
  char expected[] = "AABBB AABAA ABBAB ABBAB ABBBB ";
  fn_ampersand_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_ampersand_down_extra_spaces(void** state) {
  char str[] = "AABBB  AABAA  ABBAB  ABBAB  ABBBB  "; // Extra spaces
  char expected[] = "H ELLO";
  fn_ampersand_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_ampersand_up_down_combined(void** state) {
  char str[] = "Test";
  char original[strlen(str) * 6 + 1]; // Baconian can be up to 6 times longer
  strncpy(original, str, sizeof(original));
  original[sizeof(original) - 1] = '\0';
  fn_ampersand_up(str);
  fn_ampersand_down(str);
  for (int i = 0; str[i] != '\0'; i++) {
    str[i] = toupper(str[i]);
  }
  assert_string_equal(original, str);
}

static void test_fn_ampersand_down_invalid_code(void** state) {
  char str[] = "AAAAA AABAX ABBAB"; // Invalid code with 'X'
  char expected[] = "A?B";
  fn_ampersand_down(str);
  assert_string_equal(expected, str);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fn_ampersand_up_basic),
      cmocka_unit_test(test_fn_ampersand_down_basic),
      cmocka_unit_test(test_fn_ampersand_up_empty_string),
      cmocka_unit_test(test_fn_ampersand_down_empty_string),
      cmocka_unit_test(test_fn_ampersand_up_null_input),
      cmocka_unit_test(test_fn_ampersand_down_null_input),
      cmocka_unit_test(test_fn_ampersand_up_non_alpha),
      cmocka_unit_test(test_fn_ampersand_down_invalid),
      cmocka_unit_test(test_fn_ampersand_up_mixed_case),
      cmocka_unit_test(test_fn_ampersand_down_extra_spaces),
      cmocka_unit_test(test_fn_ampersand_up_down_combined),
      cmocka_unit_test(test_fn_ampersand_down_invalid_code),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
