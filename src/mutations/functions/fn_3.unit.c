#include "fn_3.h"
#include "../mod.h"
#include <cmocka.h>
#include <string.h>

// Function prototypes
void fn_3_up(char* str);
void fn_3_down(char* str);

// Test cases for Vigenere Cipher (fn_3_up and fn_3_down)

static void test_fn_3_up_basic(void** state) {
  char str[] = "helloworld";
  char expected[] = "aopzlttohk";
  fn_3_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_3_down_basic(void** state) {
  char str[] = "aopzlttohk";
  char expected[] = "helloworld";
  fn_3_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_3_up_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_3_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_3_down_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_3_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_3_up_null_input(void** state) {
  fn_3_up(NULL); // Just check that it doesn't crash
}

static void test_fn_3_down_null_input(void** state) {
  fn_3_down(NULL); // Just check that it doesn't crash
}

static void test_fn_3_up_non_alpha(void** state) {
  char str[] = "123 !@#";
  char expected[] = "123 !@#";
  fn_3_up(str);
  assert_string_equal(expected,
		      str); // Non-alpha characters should remain unchanged
}

static void test_fn_3_down_non_alpha(void** state) {
  char str[] = "123 !@#";
  char expected[] = "123 !@#";
  fn_3_down(str);
  assert_string_equal(expected,
		      str); // Non-alpha characters should remain unchanged
}

static void test_fn_3_up_mixed_case(void** state) {
  char str[] = "HelloWorld";
  char expected[] = "AopzLttohk";
  fn_3_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_3_down_mixed_case(void** state) {
  char str[] = "AopzLttohk";
  char expected[] = "HelloWorld";
  fn_3_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_3_up_with_spaces(void** state) {
  char str[] = "hello world";
  char expected[] = "aopzl ttohk";
  fn_3_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_3_down_with_spaces(void** state) {
  char str[] = "aopzl ttohk";
  char expected[] = "hello world";
  fn_3_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_3_up_down_combined(void** state) {
  char str[] = "TestStringWithSymbols!@#123";
  char original[sizeof(str)];
  strncpy(original, str, sizeof(original));
  original[sizeof(original) - 1] = '\0';
  fn_3_up(str);
  fn_3_down(str);
  assert_string_equal(original, str);
}

static void test_fn_3_up_empty_key(void** state) {
  // Temporarily set the key to an empty string
  extern char vigenere_key[];
  char original_key[strlen(vigenere_key) + 1];
  strncpy(original_key, vigenere_key, sizeof(original_key));
  original_key[sizeof(original_key) - 1] = '\0';
  vigenere_key[0] = '\0';

  char str[] = "teststring";
  char expected[] = "teststring";
  fn_3_up(str);
  assert_string_equal(expected, str);

  // Restore the original key
  strncpy(vigenere_key, original_key, strlen(original_key) + 1);
}

static void test_fn_3_down_empty_key(void** state) {
  // Temporarily set the key to an empty string
  extern char vigenere_key[];
  char original_key[strlen(vigenere_key) + 1];
  strncpy(original_key, vigenere_key, sizeof(original_key));
  original_key[sizeof(original_key) - 1] = '\0';
  vigenere_key[0] = '\0';

  char str[] = "teststring";
  char expected[] = "teststring";
  fn_3_down(str);
  assert_string_equal(expected, str);

  // Restore the original key
  strncpy(vigenere_key, original_key, strlen(original_key) + 1);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fn_3_up_basic),
      cmocka_unit_test(test_fn_3_down_basic),
      cmocka_unit_test(test_fn_3_up_empty_string),
      cmocka_unit_test(test_fn_3_down_empty_string),
      cmocka_unit_test(test_fn_3_up_null_input),
      cmocka_unit_test(test_fn_3_down_null_input),
      cmocka_unit_test(test_fn_3_up_non_alpha),
      cmocka_unit_test(test_fn_3_down_non_alpha),
      cmocka_unit_test(test_fn_3_up_mixed_case),
      cmocka_unit_test(test_fn_3_down_mixed_case),
      cmocka_unit_test(test_fn_3_up_with_spaces),
      cmocka_unit_test(test_fn_3_down_with_spaces),
      cmocka_unit_test(test_fn_3_up_down_combined),
      cmocka_unit_test(test_fn_3_up_empty_key),
      cmocka_unit_test(test_fn_3_down_empty_key),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
