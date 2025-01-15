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

    if(CMAKE_SYSTEM_NAME MATCHES "Linux")
        # Check if apt is available
        find_program(APT_EXECUTABLE apt)
        if(APT_EXECUTABLE)
            execute_process(
                COMMAND sudo apt-get update
                COMMAND sudo apt-get install -y libcmocka-dev
                RESULT_VARIABLE APT_INSTALL_RESULT
            )
            if(NOT APT_INSTALL_RESULT EQUAL 0)
                message(FATAL_ERROR "Failed to install cmocka using apt-get. Please install it manually.")
            endif()
        else()
            message(FATAL_ERROR "apt package manager not found. Please install cmocka manually.")
        endif()
    elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
        # Check if brew is available
        find_program(BREW_EXECUTABLE brew)
        if(BREW_EXECUTABLE)
            execute_process(
                COMMAND brew update
                COMMAND brew install cmocka
                RESULT_VARIABLE BREW_INSTALL_RESULT
            )
            if(NOT BREW_INSTALL_RESULT EQUAL 0)
                message(FATAL_ERROR "Failed to install cmocka using brew. Please install it manually.")
            endif()
						set(CMAKE_C_FLAGS_DEBUG "-I/usr/local/include/cmocka.h")
						message(WARNING "cmocka installed and linked.")
        else()
            message(FATAL_ERROR "brew package manager not found. Please install cmocka manually.")
        endif()
    else()
        message(FATAL_ERROR "Unsupported operating system. Please install cmocka manually.")
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
    -g  # Enable debugging symbols
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

# Add the test targets to the default build
add_custom_target(tests DEPENDS config_tests file_tests mutations_tests)

# Add commands to run the tests
add_test(NAME config_tests COMMAND config_tests)
add_test(NAME file_tests COMMAND file_tests)
add_test(NAME mutations_tests COMMAND mutations_tests)
