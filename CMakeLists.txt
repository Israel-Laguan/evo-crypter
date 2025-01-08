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

if(MSVC)
    # Find pthreads4w
    find_path(PTHREADS4W_INCLUDE_DIR
        NAMES pthread.h
        PATHS "C:/pthreads4w/include" # Adjust this to where you extracted pthreads4w
    )

    find_library(PTHREADS4W_LIBRARY
        NAMES pthreadVC2.lib # Or the appropriate .lib file for your pthreads4w version
        PATHS "C:/pthreads4w/lib" # Adjust this to where you extracted pthreads4w
    )

    if (PTHREADS4W_INCLUDE_DIR AND PTHREADS4W_LIBRARY)
        message(STATUS "Found pthreads4w: ${PTHREADS4W_INCLUDE_DIR}")
        target_include_directories(evo PRIVATE ${PTHREADS4W_INCLUDE_DIR})
        target_link_libraries(evo PRIVATE ${PTHREADS4W_LIBRARY})
        set(THREADS_FOUND TRUE)
    else()
        message(FATAL_ERROR "Could not find pthreads4w. Please install it and set PTHREADS4W_INCLUDE_DIR and PTHREADS4W_LIBRARY.")
    endif()
endif()

# Install target (optional)
install(TARGETS evo DESTINATION bin)

# Enable testing
enable_testing()

# Add a sample test (we don't have tests yet, so this is a placeholder)
add_test(NAME no_op_test COMMAND ${CMAKE_COMMAND} -E echo "No-op test passed")
