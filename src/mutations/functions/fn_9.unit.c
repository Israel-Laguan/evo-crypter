#include "../mod.h"
#include <cmocka.h>
#include <ctype.h>
#include <string.h>

// Function prototypes
void fn_9_up(char* str);
void fn_9_down(char* str);

// Test cases for Morse Code (fn_9_up and fn_9_down)

static void test_fn_9_up_basic(void** state) {
  char str[] = "hello world";
  char expected[] = ".... . .-.. .-.. ---   .-- --- .-. .-.. -..";
  fn_9_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_9_down_basic(void** state) {
  char str[] = ".... . .-.. .-.. ---   .-- --- .-. .-.. -.. ";
  char expected[] = "HELLOWORLD";
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
  char expected[] = "";
  fn_9_up(str);
  assert_string_equal(expected,
		      str); // Non-alphanumeric characters should be ignored
}

static void test_fn_9_down_invalid_morse(void** state) {
  char str[] = "....."; // Invalid Morse code
  char expected[] = "?";
  fn_9_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_9_up_mixed_case(void** state) {
  char str[] = "HeLlO wOrLd";
  char expected[] = ".... . .-.. .-.. ---   .-- --- .-. .-.. -.. ";
  fn_9_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_9_down_multiple_spaces(void** state) {
  char str[] = ".... . .-.. .-.. ---     .-- --- .-. .-.. -.. "; // Extra spaces
  char expected[] = "HELLOWORLD";
  fn_9_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_9_up_down_combined(void** state) {
  char str[] = "TestString";
  char original[strlen(str) * 5 + 1]; // Morse can be up to 5 times longer
  strncpy(original, str, sizeof(original));
  original[sizeof(original) - 1] = '\0';
  fn_9_up(str);
  fn_9_down(str);
  for (int i = 0; str[i] != '\0'; i++) {
    str[i] = toupper(str[i]);
  }
  assert_string_equal(original, str);
}

static void test_fn_9_down_only_spaces(void** state) {
  char str[] = "      "; // Only spaces
  char expected[] = "";
  fn_9_down(str);
  assert_string_equal(expected, str);
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
      cmocka_unit_test(test_fn_9_down_invalid_morse),
      cmocka_unit_test(test_fn_9_up_mixed_case),
      cmocka_unit_test(test_fn_9_down_multiple_spaces),
      cmocka_unit_test(test_fn_9_up_down_combined),
      cmocka_unit_test(test_fn_9_down_only_spaces),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
