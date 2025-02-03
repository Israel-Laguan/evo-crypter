cmake_minimum_required(VERSION 3.10)

# Read the version from version.txt
file(READ "${CMAKE_SOURCE_DIR}/version.txt" PROJECT_VERSION)
string(REGEX REPLACE "\n$" "" PROJECT_VERSION "${PROJECT_VERSION}")

project(evo-crypter VERSION ${PROJECT_VERSION})

# Include dependencies management
include(cmake/Dependencies.cmake)

# Include compiler options
include(cmake/CompilerOptions.cmake)

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

# Set compile options for the library (defined in CompilerOptions.cmake)
set_library_compile_options(evo_lib)

# Link pthreads to the library
target_link_libraries(evo_lib Threads::Threads)

# Add executable target, specifying the correct path to main.c
add_executable(evo src/main.c)

# Link the executable to the static library
target_link_libraries(evo evo_lib)

# Install target (optional)
install(TARGETS evo DESTINATION bin)

# Include testing setup (defined in Testing.cmake)
include(cmake/Testing.cmake)
