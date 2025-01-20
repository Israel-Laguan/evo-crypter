cmake_minimum_required(VERSION 3.10)

# Read the version from version.txt
file(READ "${CMAKE_SOURCE_DIR}/version.txt" PROJECT_VERSION)
string(REGEX REPLACE "\n$" "" PROJECT_VERSION "${PROJECT_VERSION}")  # Remove trailing newline

project(evo-crypter VERSION ${PROJECT_VERSION})

# Find pthreads
find_package(Threads REQUIRED)

# Collect source files (excluding unit test files and main.c)
file(GLOB_RECURSE SOURCES
    "src/*.h"
    "src/*.c"
    "src/*/*.h"
    "src/*/*.c"
)
# Collect also all the header files in the functions directory
file(GLOB_RECURSE FUNCTION_HEADERS "src/mutations/functions/*.h")
list(APPEND SOURCES ${FUNCTION_HEADERS})
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

# Install target (optional)
install(TARGETS evo DESTINATION bin)

# --- Code Coverage Setup ---
option(ENABLE_COVERAGE "Enable code coverage" OFF)

if(ENABLE_COVERAGE)
    message(STATUS "Enabling debug/coverage build")

    # Set coverage options for the library
    target_compile_options(evo_lib PRIVATE -g --coverage)
    target_link_options(evo_lib PRIVATE --coverage)

    # Set coverage options for the executable
    target_compile_options(evo PRIVATE -g --coverage)
    target_link_options(evo PRIVATE --coverage)

    # Include CTest module for coverage reporting
    include(CTest)
endif()

# --- Testing Setup ---
if(ENABLE_COVERAGE OR CMAKE_BUILD_TYPE STREQUAL "Testing")
    # Find cmocka
    find_package(cmocka REQUIRED)

    if(NOT cmocka_FOUND)
        message(FATAL_ERROR "cmocka not found. Please install it manually.")
    endif()

    # Enable testing
    enable_testing()

    # Function to add a test executable
    function(add_test_executable name source)
        add_executable(${name} ${source})
        target_link_libraries(${name} cmocka ${CMAKE_DL_LIBS} evo_lib)
        target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/src)
        if(ENABLE_COVERAGE)
            target_compile_options(${name} PRIVATE -g --coverage)
            target_link_options(${name} PRIVATE --coverage)
        endif()
        add_test(NAME ${name} COMMAND ${name})
    endfunction()

    # Add unit tests
    add_test_executable(config_tests src/config/utils.unit.c)
    add_test_executable(file_tests src/file/utils.unit.c)
    add_test_executable(mutations_tests src/mutations/mod.unit.c)
		target_compile_options(mutations_tests PRIVATE -fno-builtin)
		target_link_options(mutations_tests PRIVATE -Wl,--wrap=apply_mutation_up -Wl,--wrap=apply_mutation_down -Wl,--wrap=reverse_generations)
    add_test_executable(config_cli_tests src/config/cli.unit.c)
    add_test_executable(config_mod_tests src/config/mod.unit.c)
    add_test_executable(file_input_processing_tests src/file/input_processing.unit.c)
		target_compile_options(file_input_processing_tests PRIVATE -fno-builtin)
		target_link_options(file_input_processing_tests PRIVATE -Wl,--wrap=apply_mutations_to_chunk)
    add_test_executable(file_mod_tests src/file/mod.unit.c)
		target_compile_options(file_mod_tests PRIVATE -fno-builtin)
		target_link_options(file_mod_tests PRIVATE -Wl,--wrap=process_input_single_thread -Wl,--wrap=process_input_multi_thread)
    add_test_executable(fn_1_tests src/mutations/functions/fn_1.unit.c)
    add_test_executable(fn_2_tests src/mutations/functions/fn_2.unit.c)
    add_test_executable(fn_3_tests src/mutations/functions/fn_3.unit.c)
    add_test_executable(fn_4_tests src/mutations/functions/fn_4.unit.c)
    add_test_executable(fn_5_tests src/mutations/functions/fn_5.unit.c)
    add_test_executable(fn_6_tests src/mutations/functions/fn_6.unit.c)
    add_test_executable(fn_7_tests src/mutations/functions/fn_7.unit.c)
    add_test_executable(fn_8_tests src/mutations/functions/fn_8.unit.c)
    add_test_executable(fn_9_tests src/mutations/functions/fn_9.unit.c)
    add_test_executable(fn_ampersand_tests src/mutations/functions/fn_ampersand.unit.c)
    add_test_executable(fn_asterisk_tests src/mutations/functions/fn_asterisk.unit.c)

    # Add the test targets to the default build
    add_custom_target(tests DEPENDS
        config_tests file_tests mutations_tests config_cli_tests config_mod_tests
        file_input_processing_tests file_mod_tests fn_1_tests fn_2_tests fn_3_tests
        fn_4_tests fn_5_tests fn_6_tests fn_7_tests fn_8_tests fn_9_tests
        fn_ampersand_tests fn_asterisk_tests
    )
endif()
