#!/bin/bash

set -e

VERSION_FILE="version.txt"
CURRENT_VERSION=$(cat "$VERSION_FILE")

# Check if a new version is provided as an argument
if [ -z "$1" ]; then
    echo "Current version: $CURRENT_VERSION"
    exit 0
fi

NEW_VERSION="$1"

# Validate the new version using SemVer regex
if ! [[ "$NEW_VERSION" =~ ^(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)(\-[0-9A-Za-z-]+(\.[0-9A-Za-z-]+)*)?(\+[0-9A-Za-z-]+(\.[0-9A-Za-z-]+)*)?$ ]]; then
    echo "Error: Invalid SemVer version format: $NEW_VERSION"
    exit 1
fi

# Update the version file
echo "$NEW_VERSION" > "$VERSION_FILE"

echo "Version updated to: $NEW_VERSION"

# Ask if the user wants to create a Git tag
read -r -p "Create Git tag for this version? [y/N] " response
if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]; then
    git tag -a "v$NEW_VERSION" -m "Version $NEW_VERSION"
    echo "Git tag 'v$NEW_VERSION' created."

    read -r -p "Push the tag to remote? [y/N] " response2
    if [[ "$response2" =~ ^([yY][eE][sS]|[yY])$ ]]; then
        git push origin "v$NEW_VERSION"
        echo "Git tag 'v$NEW_VERSION' pushed to remote."
    fi
fi
