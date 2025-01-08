cmake_minimum_required(VERSION 3.10)

# Read the version from version.txt
file(READ "${CMAKE_SOURCE_DIR}/version.txt" PROJECT_VERSION)
string(REGEX REPLACE "\n$" "" PROJECT_VERSION "${PROJECT_VERSION}")  # Remove trailing newline

project(evo-crypter VERSION ${PROJECT_VERSION})

# Find pthreads
find_package(Threads REQUIRED)

# Collect source files
file(GLOB_RECURSE SOURCES
    "src/*.h"
    "src/*.c"
)

# Exclude specific files or patterns from compilation
set(SOURCES ${SOURCES}
    PARENT_SCOPE
)

# Add executable target
add_executable(evo ${SOURCES})

# Link pthreads
target_link_libraries(evo Threads::Threads)

# Set compile options
target_compile_options(evo PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:MSVC>:/W3>
    -g
)

# Install target (optional)
install(TARGETS evo DESTINATION bin)

# Enable testing
enable_testing()

# Add a sample test (we don't have tests yet, so this is a placeholder)
add_test(NAME no_op_test COMMAND ${CMAKE_COMMAND} -E echo "No-op test passed")
