#!/bin/bash

set -e

echo "Running cppcheck..."

cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem src

if [ $? -eq 0 ]; then
    echo "cppcheck found no issues."
else
    echo "cppcheck found issues (see above)."
    exit 1
fi
