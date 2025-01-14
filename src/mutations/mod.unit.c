#include "mod.h"
#include "../file/input_processing.h"
#include <cmocka.h>
#include <stdio.h>
#include <string.h>

// Define a struct to hold the mutation symbol and its corresponding up and down
// functions
typedef struct {
  char symbol;
  void (*up_fn)(char*);
  void (*down_fn)(char*);
} MutationFunc;

// Define an array of MutationFunc structs, one for each mutation function
MutationFunc mutation_functions[] = {
    {'1', fn_1_up, fn_1_down},
    {'2', fn_2_up, fn_2_down},
    {'3', fn_3_up, fn_3_down},
    {'4', fn_4_up, fn_4_down},
    {'5', fn_5_up, fn_5_down},
    {'6', fn_6_up, fn_6_down},
    {'7', fn_7_up, fn_7_down},
    {'8', fn_8_up, fn_8_down},
    {'9', fn_9_up, fn_9_down},
    {'#', fn_ampersand_up, fn_ampersand_down},
    {'*', fn_asterisk_up, fn_asterisk_down},
    // Add more mutation functions here
};

// Test case for apply_mutation_up and apply_mutation_down using a loop

static void test_apply_mutations_up_and_down(void** state) {
  char test_str[1024] =
      "test_string"; // Increase size to avoid potential overflow
  char original_str[1024] = "test_string"; // Keep a copy for comparison

  // Iterate over all mutation functions
  for (int i = 0;
       i < sizeof(mutation_functions) / sizeof(mutation_functions[0]); i++) {
    // Test apply_mutation_up
    apply_mutation_up(mutation_functions[i].symbol, test_str);
    // test_str is modified by apply_mutation_up
    // Apply the corresponding down function to revert the change
    apply_mutation_down(mutation_functions[i].symbol, test_str);
    // Assert that the string is reverted back to the original
    assert_string_equal(original_str, test_str);

    // Reset test_str for the next test
    strncpy(test_str, original_str, sizeof(test_str)); // Use strncpy
    test_str[sizeof(test_str) - 1] = '\0'; // Ensure null-termination
  }
}

static void test_apply_mutations_down_and_up(void** state) {
  char test_str[1024] = "test_string";	   // Increase size
  char original_str[1024] = "test_string"; // Keep a copy for comparison

  // Iterate over all mutation functions
  for (int i = 0;
       i < sizeof(mutation_functions) / sizeof(mutation_functions[0]); i++) {
    // Test apply_mutation_down
    apply_mutation_down(mutation_functions[i].symbol, test_str);
    // test_str is modified by apply_mutation_down
    // Apply the corresponding up function to revert the change
    apply_mutation_up(mutation_functions[i].symbol, test_str);

    // Assert that the string is reverted back to the original
    assert_string_equal(original_str, test_str);

    // Reset test_str for the next test
    strncpy(test_str, original_str, sizeof(test_str)); // Use strncpy
    test_str[sizeof(test_str) - 1] = '\0'; // Ensure null-termination
  }
}

// Test cases for unknown symbols

static void test_apply_mutation_up_unknown(void** state) {
  char test_str[] = "test_string";
  // We expect an error message to be printed to stderr, but we can't easily
  // test that with CMocka. We'll just check that the function doesn't crash.
  apply_mutation_up('?', test_str);
}

static void test_apply_mutation_down_unknown(void** state) {
  char test_str[] = "test_string";
  // Similar to the above, just check for no crash.
  apply_mutation_down('?', test_str);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_apply_mutations_up_and_down),
      cmocka_unit_test(test_apply_mutations_down_and_up),
      cmocka_unit_test(test_apply_mutation_up_unknown),
      cmocka_unit_test(test_apply_mutation_down_unknown),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
