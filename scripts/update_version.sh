#!/bin/bash

set -e

VERSION_FILE="version.txt"
CURRENT_VERSION=$(cat "$VERSION_FILE")

# Function to validate SemVer format
validate_semver() {
  local version="$1"
  if [[ ! "$version" =~ ^(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)(\-[0-9A-Za-z-]+(\.[0-9A-Za-z-]+)*)?(\+[0-9A-Za-z-]+(\.[0-9A-Za-z-]+)*)?$ ]]; then
    echo "Error: Invalid SemVer version format: $version"
    exit 1
  fi
}

# Check if a new version is provided as an argument
if [ -z "$1" ]; then
  echo "Current version: $CURRENT_VERSION"
  exit 0
fi

NEW_VERSION="$1"

# Validate the new version using SemVer regex
validate_semver "$NEW_VERSION"

# Update the version file
echo "$NEW_VERSION" > "$VERSION_FILE"

echo "Version updated to: $NEW_VERSION"
