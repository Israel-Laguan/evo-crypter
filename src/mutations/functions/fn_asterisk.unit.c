#include "../mod.h"
#include <cmocka.h>
#include <stdlib.h>

// Function prototypes
void fn_asterisk_up(char* str);
void fn_asterisk_down(char* str);

// Test cases for Dictionary Move (fn_asterisk_up and fn_asterisk_down)

static void test_fn_asterisk_up_basic(void** state) {
  char* str = strdup("apple dog red");
  char expected[] = "dog red apple";
  fn_asterisk_up(str);
  assert_string_equal(expected, str);
  free(str);
}

static void test_fn_asterisk_down_basic(void** state) {
  char* str = strdup("dog red apple");
  char expected[] = "apple dog red";
  fn_asterisk_down(str);
  assert_string_equal(expected, str);
  free(str);
}

static void test_fn_asterisk_up_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_asterisk_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_asterisk_down_empty_string(void** state) {
  char str[] = "";
  char expected[] = "";
  fn_asterisk_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_asterisk_up_null_input(void** state) {
  fn_asterisk_up(NULL); // Just check that it doesn't crash
}

static void test_fn_asterisk_down_null_input(void** state) {
  fn_asterisk_down(NULL); // Just check that it doesn't crash
}

static void test_fn_asterisk_up_word_not_found(void** state) {
  char str[] = "apple unknown word";
  char expected[] = "dog unknown word";
  fn_asterisk_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_asterisk_down_word_not_found(void** state) {
  char str[] = "dog unknown word";
  char expected[] = "apple unknown word";
  fn_asterisk_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_asterisk_up_case_insensitive(void** state) {
  char str[] = "aPPlE DoG rEd";
  char expected[] = "dog red apple";
  fn_asterisk_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_asterisk_down_case_insensitive(void** state) {
  char str[] = "DoG rEd aPPlE";
  char expected[] = "apple dog red";
  fn_asterisk_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_asterisk_up_down_combined(void** state) {
  char str[] = "apple banana orange";
  char expected[] = "apple banana orange";
  fn_asterisk_up(str);
  fn_asterisk_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_asterisk_up_multiple_spaces(void** state) {
  char str[] = "apple  dog   red";
  char expected[] = "dog red apple";
  fn_asterisk_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_asterisk_down_multiple_spaces(void** state) {
  char str[] = "dog  red   apple";
  char expected[] = "apple dog red";
  fn_asterisk_down(str);
  assert_string_equal(expected, str);
}

static void test_fn_asterisk_up_only_spaces(void** state) {
  char str[] = "      ";
  char expected[] = "";
  fn_asterisk_up(str);
  assert_string_equal(expected, str);
}

static void test_fn_asterisk_down_only_spaces(void** state) {
  char str[] = "      ";
  char expected[] = "";
  fn_asterisk_down(str);
  assert_string_equal(expected, str);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_fn_asterisk_up_basic),
      cmocka_unit_test(test_fn_asterisk_down_basic),
      cmocka_unit_test(test_fn_asterisk_up_empty_string),
      cmocka_unit_test(test_fn_asterisk_down_empty_string),
      cmocka_unit_test(test_fn_asterisk_up_null_input),
      cmocka_unit_test(test_fn_asterisk_down_null_input),
      cmocka_unit_test(test_fn_asterisk_up_word_not_found),
      cmocka_unit_test(test_fn_asterisk_down_word_not_found),
      cmocka_unit_test(test_fn_asterisk_up_case_insensitive),
      cmocka_unit_test(test_fn_asterisk_down_case_insensitive),
      cmocka_unit_test(test_fn_asterisk_up_down_combined),
      cmocka_unit_test(test_fn_asterisk_up_multiple_spaces),
      cmocka_unit_test(test_fn_asterisk_down_multiple_spaces),
      cmocka_unit_test(test_fn_asterisk_up_only_spaces),
      cmocka_unit_test(test_fn_asterisk_down_only_spaces),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
