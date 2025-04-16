#include "config/mod.h"
#include "config/utils.h"
#include "file/mod.h"
#include "mutations/mod.h"

  // Función para sumar dos números enteros
  int sumar(int a, int b) {
    return a + b;
  }

    // Función para sumar dos números enteros
    int sumar2(int a, int b) {
      return a + b;
    }

int main(int argc, char* argv[]) {
  Config config = initialize_config(argc, argv);

  if (config.error) {
    free_config(&config);
    return 1;
  }

  if (config.help) {
    print_usage(argv[0]);
    free_config(&config);
    return 0;
  }

  if (config.decrypt) {
    evolve_file(config.input_file, "decrypted", config.generations,
		config.threads, true);
  } else {
    evolve_file(config.input_file, "encrypted", config.generations,
		config.threads, false);
  }

  free_config(&config);
  return 0;
}
