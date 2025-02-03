#include "../mod.h"
#include <cmocka.h>
#include <ctype.h>
#include <string.h>

// Function prototypes
void fn_ampersand_up(char* str);
void fn_ampersand_down(char* str);

// Test cases for XOR Cipher (fn_ampersand_up and fn_ampersand_down)

static void test_fn_ampersand_up_down(void** state) {
  (void)state; // Unused

  char test_str[] = "Hello, World!";
  char original_str[] = "Hello, World!";

  // Apply encryption
  fn_3_up(test_str);
  // Apply decryption
  fn_3_down(test_str);

  // Check if decrypted matches original
  assert_string_equal(test_str, original_str);
}

static void test_fn_ampersand_special_characters(void** state) {
  (void)state;

  char test_str[] = "\x01\x02\x03\x04";
  char original_str[] = "\x01\x02\x03\x04";

  fn_3_up(test_str);
  fn_3_down(test_str);

  assert_memory_equal(test_str, original_str, sizeof(test_str));
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

static void test_fn_ampersand_up_down_mixed_case(void** state) {
  char str[] = "HeLlO";
  char expected[] = "HeLlO";
  fn_ampersand_up(str);
  fn_ampersand_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_ampersand_up_down_combined(void** state) {
  char str[] = "TestString123";
  char original[strlen(str) + 1];
  strncpy(original, str, sizeof(original));
  fn_ampersand_up(str);
  fn_ampersand_down(str);
  assert_string_equal(original, str);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fn_ampersand_up_down),
      cmocka_unit_test(test_fn_ampersand_special_characters),
      cmocka_unit_test(test_fn_ampersand_up_empty_string),
      cmocka_unit_test(test_fn_ampersand_down_empty_string),
      cmocka_unit_test(test_fn_ampersand_up_null_input),
      cmocka_unit_test(test_fn_ampersand_down_null_input),
      cmocka_unit_test(test_fn_ampersand_up_down_mixed_case),
      cmocka_unit_test(test_fn_ampersand_up_down_combined),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
