#!/bin/bash

# Set the build directory
BUILD_DIR="build"

# Create the build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    mkdir -p "$BUILD_DIR"
fi

# Change to the build directory
cd "$BUILD_DIR"

# Configure CMake
cmake ..

# Build the project
cmake --build .

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build successful. Executable: $BUILD_DIR/evo"
    exit 0
else
    echo "Build failed."
    exit 1
fi
