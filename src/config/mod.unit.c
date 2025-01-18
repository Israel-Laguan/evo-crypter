#include "mod.h"
#include "utils.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strncpy

// Helper function to create argv
static char** create_argv(int argc, ...) {
  char** argv = malloc(argc * sizeof(char*));
  va_list args;
  va_start(args, argc);
  for (int i = 0; i < argc; i++) {
    argv[i] = strdup(va_arg(args, const char*));
  }
  va_end(args);
  return argv;
}

static void free_argv(int argc, char** argv) {
  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }
  free(argv);
}

// Test cases for initialize_config

static void test_initialize_config_valid(void** state) {
  int argc = 7;
  char** argv =
      create_argv(argc, "./evo", "-i", "input.txt", "-t", "4", "-g", "1,2,3");
  Config config = initialize_config(argc, argv);

  assert_false(config.error);
  assert_string_equal(config.input_file, "input.txt");
  assert_int_equal(config.threads, 4);
  assert_string_equal(config.generations, "1,2,3");
  assert_false(config.decrypt);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_initialize_config_no_input(void** state) {
  int argc = 1;
  char** argv = create_argv(argc, "./evo");
  Config config = initialize_config(argc, argv);

  assert_true(
      config.error); // Should have an error because input file is missing

  free_argv(argc, argv);
  free_config(&config);
}

static void test_initialize_config_default_generations(void** state) {
  int argc = 3;
  char** argv = create_argv(argc, "./evo", "-i", "input.txt");
  Config config = initialize_config(argc, argv);

  assert_false(config.error);
  assert_string_equal(config.generations, "1");

  free_argv(argc, argv);
  free_config(&config);
}

static void test_initialize_config_invalid_generations(void** state) {
  int argc = 5;
  char** argv = create_argv(argc, "./evo", "-i", "input.txt", "-g", "1,2,!,");
  Config config = initialize_config(argc, argv);

  assert_true(config.error);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_initialize_config_uppercase_generations(void** state) {
  int argc = 5;
  char** argv = create_argv(argc, "./evo", "-i", "input.txt", "-g", "1,A,2,B");
  Config config = initialize_config(argc, argv);

  assert_false(config.error);
  assert_string_equal(config.generations, "1,a,2,b");

  free_argv(argc, argv);
  free_config(&config);
}
// Test cases for free_config
// (These are simple - just check for no crashes)

static void test_free_config_no_crash(void** state) {
  Config config = {NULL, NULL, 0, false, false, false};
  free_config(&config); // Should not crash
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_initialize_config_valid),
      cmocka_unit_test(test_initialize_config_no_input),
      cmocka_unit_test(test_initialize_config_default_generations),
      cmocka_unit_test(test_initialize_config_invalid_generations),
      cmocka_unit_test(test_initialize_config_uppercase_generations),
      cmocka_unit_test(test_free_config_no_crash),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
