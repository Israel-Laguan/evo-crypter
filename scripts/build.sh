#!/bin/bash

set -e

# Set the build directory (default: build/)
BUILD_DIR="${1:-build}"

# Set the build type (default: Release)
BUILD_TYPE="${2:-Release}"

# Check if being run from the root directory
if [ ! -f "src/main.c" ]; then
  echo "Error: build.sh must be run from the project root directory."
  exit 1
fi

# Clean the build directory if it exists
if [ -d "$BUILD_DIR" ]; then
  echo "Cleaning build directory..."
  rm -rf "$BUILD_DIR"
fi

# Create the build directory
mkdir -p "$BUILD_DIR"

# Change to the build directory
# cd "$BUILD_DIR"

# Configure CMake (using environment variable for build type)
echo "Configuring CMake..."
cmake -B "$BUILD_DIR" -S . -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE"

# Build the project
echo "Building the project..."
cmake --build "$BUILD_DIR" --config "$CMAKE_BUILD_TYPE"

# Check if the build was successful
if [ $? -eq 0 ]; then
  echo "Build successful. Executable: $BUILD_DIR/evo"
  exit 0
else
  echo "Build failed."
  exit 1
fi
