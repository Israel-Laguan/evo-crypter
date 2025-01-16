#!/bin/bash

set -e

# --- Configuration ---
INPUT_FILE="/app/LICENSE"
ENCRYPTED_FILE="/app/encrypted"
DECRYPTED_FILE="/app/decrypted"
EVO_EXECUTABLE="/app/build/evo"
GENERATIONS="1,2"

# --- Check for required tools ---
if ! command -v "$EVO_EXECUTABLE" &> /dev/null; then
  echo "Error: evo executable not found at $EVO_EXECUTABLE"
  exit 1
fi

if ! command -v diff &> /dev/null; then
  echo "Error: diff command not found"
  exit 1
fi

# --- Perform encryption ---
echo "Encrypting $INPUT_FILE to $ENCRYPTED_FILE using generations '$GENERATIONS'..."
"$EVO_EXECUTABLE" --input "$INPUT_FILE" --generations "$GENERATIONS"

# --- Perform decryption ---
echo "Decrypting $ENCRYPTED_FILE to $DECRYPTED_FILE..."
"$EVO_EXECUTABLE" --input "$ENCRYPTED_FILE" --generations "$GENERATIONS" --decrypt

# --- Compare the original and decrypted files ---
echo "Comparing $INPUT_FILE and $DECRYPTED_FILE..."
diff "$INPUT_FILE" "$DECRYPTED_FILE"

# --- Check the diff result ---
if [ $? -eq 0 ]; then
  echo "Success: Original and decrypted files are identical."
else
  echo "Error: Original and decrypted files differ!"
  exit 1
fi
