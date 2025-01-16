#!/bin/bash

set -e

# Check if being run from the root directory
if [ ! -f "src/main.c" ]; then
  echo "Error: lint.sh must be run from the project root directory."
  exit 1
fi

# Run cppcheck
echo "Running cppcheck..."
cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem src

# Check for cppcheck errors
if [ $? -ne 0 ]; then
  echo "cppcheck found issues (see above)."
  exit 1
fi

# Set the build output directory for clang-tidy
BUILD_OUTPUT_DIR="build"

# Run clang-tidy
echo "Running clang-tidy..."
cmake -B "${BUILD_OUTPUT_DIR}" -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release -S .
find src/ -regex '.*\.\(c\|h\)' -print0 | xargs -0 clang-tidy -p "${BUILD_OUTPUT_DIR}" --warnings-as-errors=* --quiet

# Check for clang-tidy errors
if [ $? -ne 0 ]; then
  echo "clang-tidy found issues (see above)."
  exit 1
fi

# Run clang-format (check mode)
echo "Running clang-format (check mode)..."
FORMAT_OUTPUT=$(find src -iname '*.h' -o -iname '*.c' | xargs clang-format --dry-run)

# Check for clang-format errors
if [ $? -ne 0 ]; then
    echo "clang-format found formatting issues. Applying fixes..."
    find src -iname '*.h' -o -iname '*.c' | xargs clang-format -i
    echo "clang-format fixes applied."
else
    echo "No formatting errors found by clang-format."
fi

echo "No linting or formatting errors found."
