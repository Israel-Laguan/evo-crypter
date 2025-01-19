#include "mod.h"
#include "utils.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

// Helper function to create argv
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

// Test cases for initialize_config

static void test_initialize_config_valid(void** state) {
  int argc = 7;
  const char* args[] = {"./evo", "-i", "input.txt", "-t", "4", "-g", "1,2,3"};

  char** argv = create_test_argv(argc, args);
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
  const char* args[] = {"./evo"};

  char** argv = create_test_argv(argc, args);
  Config config = initialize_config(argc, argv);

  assert_true(
      config.error); // Should have an error because input file is missing

  free_argv(argc, argv);
  free_config(&config);
}

static void test_initialize_config_default_generations(void** state) {
  int argc = 3;
  const char* args[] = {"./evo", "-i", "input.txt"};

  char** argv = create_test_argv(argc, args);
  Config config = initialize_config(argc, argv);

  assert_false(config.error);
  assert_string_equal(config.generations, "1");

  free_argv(argc, argv);
  free_config(&config);
}

static void test_initialize_config_invalid_generations(void** state) {
  int argc = 5;
  const char* args[] = {"./evo", "-i", "input.txt", "-g", "1,2,!,"};

  char** argv = create_test_argv(argc, args);
  Config config = initialize_config(argc, argv);

  assert_true(config.error);

  free_argv(argc, argv);
  free_config(&config);
}

static void test_initialize_config_uppercase_generations(void** state) {
  int argc = 5;
  const char* args[] = {"./evo", "-i", "input.txt", "-g", "1,A,2,B"};

  char** argv = create_test_argv(argc, args);
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
