#!/bin/bash

# Build the executable
make all

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build successful. Executable: evo"
    exit 0
else
    echo "Build failed."
    exit 1
fi
