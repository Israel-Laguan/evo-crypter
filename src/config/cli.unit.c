#include "cli.h"
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strdup

// Helper function to simulate command-line arguments
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

// Test cases for parse_command_line_args

static void test_parse_command_line_args_all_flags(void** state) {
  int argc = 7;
  char** argv =
      create_argv(argc, "./evo", "-i", "input.txt", "-t", "4", "-g", "1,2,3");
  Config config = parse_command_line_args(argc, argv);

  assert_false(config.error);
  assert_string_equal(config.input_file, "input.txt");
  assert_int_equal(config.threads, 4);
  assert_string_equal(config.generations, "1,2,3");
  assert_false(config.decrypt);
  assert_false(config.help);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_parse_command_line_args_no_flags(void** state) {
  int argc = 1;
  char** argv = create_argv(argc, "./evo");
  Config config = parse_command_line_args(argc, argv);

  assert_false(config.error); // Should not have an error at this stage

  free_argv(argc, argv);
  free_config(&config);
}

static void test_parse_command_line_args_input_only(void** state) {
  int argc = 3;
  char** argv = create_argv(argc, "./evo", "-i", "input.txt");
  Config config = parse_command_line_args(argc, argv);

  assert_false(config.error);
  assert_string_equal(config.input_file, "input.txt");
  assert_int_equal(config.threads, 1); // Default value
  assert_null(config.generations);     // Default value will be assigned later
  assert_false(config.decrypt);
  assert_false(config.help);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_parse_command_line_args_decrypt_flag(void** state) {
  int argc = 4;
  char** argv = create_argv(argc, "./evo", "-i", "input.txt", "-d");
  Config config = parse_command_line_args(argc, argv);

  assert_false(config.error);
  assert_true(config.decrypt);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_parse_command_line_args_help_flag(void** state) {
  int argc = 4;
  char** argv = create_argv(argc, "./evo", "-i", "input.txt", "-h");
  Config config = parse_command_line_args(argc, argv);

  assert_false(config.error);
  assert_true(config.help);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_parse_command_line_args_unknown_flag(void** state) {
  int argc = 3;
  char** argv = create_argv(argc, "./evo", "-x", "input.txt");
  Config config = parse_command_line_args(argc, argv);

  assert_true(config.error);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_parse_command_line_args_missing_value(void** state) {
  int argc = 2;
  char** argv = create_argv(argc, "./evo", "-i");
  Config config = parse_command_line_args(argc, argv);

  assert_true(config.error);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_parse_command_line_args_long_flags(void** state) {
  int argc = 7;
  char** argv = create_argv(argc, "./evo", "--input", "input.txt", "--threads",
			    "4", "--generations", "1,2,3");
  Config config = parse_command_line_args(argc, argv);

  assert_false(config.error);
  assert_string_equal(config.input_file, "input.txt");
  assert_int_equal(config.threads, 4);
  assert_string_equal(config.generations, "1,2,3");
  assert_false(config.decrypt);
  assert_false(config.help);

  free_argv(argc, argv);
  free_config(&config);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_parse_command_line_args_all_flags),
      cmocka_unit_test(test_parse_command_line_args_no_flags),
      cmocka_unit_test(test_parse_command_line_args_input_only),
      cmocka_unit_test(test_parse_command_line_args_decrypt_flag),
      cmocka_unit_test(test_parse_command_line_args_help_flag),
      cmocka_unit_test(test_parse_command_line_args_unknown_flag),
      cmocka_unit_test(test_parse_command_line_args_missing_value),
      cmocka_unit_test(test_parse_command_line_args_long_flags),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
