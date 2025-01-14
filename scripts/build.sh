#!/bin/bash

set -e

# Set the build directory
BUILD_DIR="build"

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
cd "$BUILD_DIR"

# Configure CMake
echo "Configuring CMake..."
cmake ..

# Build the project
echo "Building the project..."
cmake --build .

# Check if the build was successful
if [ $? -eq 0 ]; then
  echo "Build successful. Executable: $BUILD_DIR/evo"
  exit 0
else
  echo "Build failed."
  exit 1
fi
