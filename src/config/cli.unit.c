#include "cli.h"
#include <cmocka.h>

// Helper function to simulate command-line arguments
static char** create_test_argv(int argc, const char* args[]) {
  if (argc <= 0 || args == NULL) {
    return NULL;
  }

  char** argv = malloc(argc * sizeof(char*));
  if (argv == NULL) {
    return NULL;
  }

  for (int i = 0; i < argc; i++) {
    if (args[i] == NULL) {
      // Clean up on NULL argument
      for (int j = 0; j < i; j++) {
	free(argv[j]);
      }
      free(argv);
      return NULL;
    }

    argv[i] = strdup(args[i]);
    if (argv[i] == NULL) {
      // Clean up on allocation failure
      for (int j = 0; j < i; j++) {
	free(argv[j]);
      }
      free(argv);
      return NULL;
    }
  }

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
  const char* args[] = {"./evo", "-i", "input.txt", "-t", "4", "-g", "1,2,3"};

  char** argv = create_test_argv(argc, args);
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
  const char* args[] = {"./evo"};

  char** argv = create_test_argv(argc, args);
  Config config = parse_command_line_args(argc, argv);

  assert_false(config.error); // Should not have an error at this stage

  free_argv(argc, argv);
  free_config(&config);
}

static void test_parse_command_line_args_input_only(void** state) {
  int argc = 3;
  const char* args[] = {"./evo", "-i", "input.txt"};

  char** argv = create_test_argv(argc, args);
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
  const char* args[] = {"./evo", "-i", "input.txt", "-d"};

  char** argv = create_test_argv(argc, args);
  Config config = parse_command_line_args(argc, argv);

  assert_false(config.error);
  assert_true(config.decrypt);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_parse_command_line_args_help_flag(void** state) {
  int argc = 4;
  const char* args[] = {"./evo", "-i", "input.txt", "-h"};

  char** argv = create_test_argv(argc, args);
  Config config = parse_command_line_args(argc, argv);

  assert_false(config.error);
  assert_true(config.help);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_parse_command_line_args_unknown_flag(void** state) {
  int argc = 3;
  const char* args[] = {"./evo", "-x", "input.txt"};

  char** argv = create_test_argv(argc, args);
  Config config = parse_command_line_args(argc, argv);

  assert_true(config.error);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_parse_command_line_args_missing_value(void** state) {
  int argc = 2;
  const char* args[] = {"./evo", "-i"};

  char** argv = create_test_argv(argc, args);
  Config config = parse_command_line_args(argc, argv);

  assert_true(config.error);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_parse_command_line_args_long_flags(void** state) {
  int argc = 7;
  const char* args[] = {"./evo", "--input",	  "input.txt", "--threads",
			"4",	 "--generations", "1,2,3"};

  char** argv = create_test_argv(argc, args);
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
