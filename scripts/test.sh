#!/bin/bash

set -e

# Check if being run from the root directory
if [ ! -f "src/main.c" ]; then
  echo "Error: test.sh must be run from the project root directory."
  exit 1
fi

# Wipe out any outdated coverage information
find . -name '*.gcda' -delete

# Build the project
CMAKE_BUILD_TYPE=Debug ./scripts/build.sh

# Run tests using ctest
echo "Running tests..."
cd build || exit
ctest -T Test --output-on-failure && ctest -T Coverage

# Check if tests were successful
if [ $? -eq 0 ]; then
  echo "Tests successful."
  exit 0
else
  echo "Tests failed."
  exit 1
fi
