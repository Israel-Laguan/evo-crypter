cmake_minimum_required(VERSION 3.10)

# Read the version from version.txt
file(READ "${CMAKE_SOURCE_DIR}/version.txt" PROJECT_VERSION)
string(REGEX REPLACE "\n$" "" PROJECT_VERSION "${PROJECT_VERSION}")  # Remove trailing newline

project(evo-crypter VERSION ${PROJECT_VERSION})

# Find pthreads
find_package(Threads REQUIRED)

# Find cmocka
find_package(cmocka)

if(NOT cmocka_FOUND)
    message(WARNING "cmocka not found. Trying to install it...")

    execute_process(
        COMMAND sudo apt-get update
        COMMAND sudo apt-get install -y libcmocka-dev
        RESULT_VARIABLE INSTALL_RESULT
    )

    if(NOT INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to install cmocka. Please install it manually.")
    endif()

    find_package(cmocka REQUIRED)
endif()

# Collect source files (excluding unit test files and main.c)
file(GLOB_RECURSE SOURCES
    "src/*.h"
    "src/*.c"
    "src/*/*.h"
    "src/*/*.c"
)
list(FILTER SOURCES EXCLUDE REGEX "\\.unit\\.c$|main\\.c$")

# Add a static library target for the main project's code
add_library(evo_lib ${SOURCES})

# Set compile options for the library
target_compile_options(evo_lib PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:MSVC>:/W3>
)

# Link pthreads to the library
target_link_libraries(evo_lib Threads::Threads)

# Add executable target, specifying the correct path to main.c
add_executable(evo src/main.c)

# Link the executable to the static library
target_link_libraries(evo evo_lib)

# Set compile options for the executable (if any specific ones are needed)
# target_compile_options(evo PRIVATE ...)

# Install target (optional)
install(TARGETS evo DESTINATION bin)

# Enable testing
enable_testing()

# Add unit tests for config/utils.c
add_executable(config_tests src/config/utils.unit.c)
target_link_libraries(config_tests cmocka ${CMAKE_DL_LIBS} evo_lib) # Link against evo_lib
target_include_directories(config_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Add unit tests for file/utils.c
add_executable(file_tests src/file/utils.unit.c)
target_link_libraries(file_tests cmocka ${CMAKE_DL_LIBS} evo_lib) # Link against evo_lib
target_include_directories(file_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Add unit tests for mutations/mod.c
add_executable(mutations_tests src/mutations/mod.unit.c)
target_link_libraries(mutations_tests cmocka ${CMAKE_DL_LIBS} evo_lib) # Link against evo_lib
target_include_directories(mutations_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_options(mutations_tests PRIVATE -fno-builtin)
target_link_options(mutations_tests PRIVATE -Wl,--wrap=apply_mutation_up -Wl,--wrap=apply_mutation_down -Wl,--wrap=reverse_generations)

# Add unit tests for config/cli.c
add_executable(config_cli_tests src/config/cli.unit.c)
target_link_libraries(config_cli_tests cmocka ${CMAKE_DL_LIBS} evo_lib)
target_include_directories(config_cli_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Add unit tests for config/mod.c
add_executable(config_mod_tests src/config/mod.unit.c)
target_link_libraries(config_mod_tests cmocka ${CMAKE_DL_LIBS} evo_lib)
target_include_directories(config_mod_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Add unit tests for file/input_processing.c
add_executable(file_input_processing_tests src/file/input_processing.unit.c)
target_link_libraries(file_input_processing_tests cmocka ${CMAKE_DL_LIBS} evo_lib)
target_include_directories(file_input_processing_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_options(file_input_processing_tests PRIVATE -fno-builtin)
target_link_options(file_input_processing_tests PRIVATE -Wl,--wrap=apply_mutations_to_chunk)

# Add the test targets to the default build
add_custom_target(tests DEPENDS config_tests file_tests mutations_tests config_cli_tests config_mod_tests file_input_processing_tests)

# Add commands to run the tests
add_test(NAME config_tests COMMAND config_tests)
add_test(NAME file_tests COMMAND file_tests)
add_test(NAME mutations_tests COMMAND mutations_tests)
add_test(NAME config_cli_tests COMMAND config_cli_tests)
add_test(NAME config_mod_tests COMMAND config_mod_tests)
add_test(NAME file_input_processing_tests COMMAND file_input_processing_tests)

# --- Code Coverage Setup ---
# Check if a coverage build is requested
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    message(STATUS "Enabling debug/coverage build")

		# Include CTest module for coverage reporting
		include(CTest)

    # Set coverage options for the library
    target_compile_options(evo_lib PRIVATE -g --coverage)
    target_link_options(evo_lib PRIVATE --coverage)

    # Set coverage options for the executable
    target_compile_options(evo PRIVATE -g --coverage)
    target_link_options(evo PRIVATE --coverage)

    # Set coverage options for the test executables
    target_compile_options(config_tests PRIVATE -g --coverage)
    target_link_options(config_tests PRIVATE --coverage)
    target_compile_options(file_tests PRIVATE -g --coverage)
    target_link_options(file_tests PRIVATE --coverage)
    target_compile_options(mutations_tests PRIVATE -g --coverage)
    target_link_options(mutations_tests PRIVATE --coverage)
    target_compile_options(config_mod_tests PRIVATE -g --coverage)
    target_link_options(config_mod_tests PRIVATE --coverage)
    target_compile_options(config_cli_tests PRIVATE -g --coverage)
    target_link_options(config_cli_tests PRIVATE --coverage)
    target_compile_options(file_input_processing_tests PRIVATE -g --coverage)
    target_link_options(file_input_processing_tests PRIVATE --coverage)
endif()
