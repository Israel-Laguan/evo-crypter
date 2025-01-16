# Scripts in evo-crypter

The `evo-crypter` project includes several utility scripts to help with building, testing, linting, and version management.

## `build.sh`

*   **Purpose:** Builds the `evo` executable.
*   **Usage:**
		```bash
		./scripts/build.sh [build_directory] [build_type]
		```
		*   `build_directory` (optional): Specifies the directory where build files will be placed. Defaults to `build`.
		*   `build_type` (optional): Specifies the CMake build type (e.g., `Debug`, `Release`, `RelWithDebInfo`, `MinSizeRel`). Defaults to `Debug`.
*   **Example:**
		```bash
		./scripts/build.sh build Release
		```

## `lint.sh`

*   **Purpose:** Runs static analysis tools (linters) to check for potential code issues.
*   **Tools Used:**
		*   `cppcheck`: Checks for common coding errors, memory leaks, undefined behavior, etc.
		*   `clang-tidy`: Provides more in-depth static analysis and can enforce coding style guidelines.
		*   `clang-format`: Checks code formatting against the project's style guide (and can automatically fix formatting issues).
*   **Usage:**
		```bash
		./scripts/lint.sh
		```

## `test.sh`

*   **Purpose:** Builds the project (if necessary) and runs the unit tests.
*   **Usage:**
		```bash
		./scripts/test.sh
		```

## `update_version.sh`

*   **Purpose:** Updates the project's version number in `version.txt` and optionally creates and pushes a Git tag.
*   **Usage:**
		```bash
		./scripts/update_version.sh <new_version> [-y]
		```
		*   `<new_version>`: The new version number in SemVer format (e.g., `0.2.0`).
		*   `-y`: Optional flag to automatically answer "yes" to prompts about creating and pushing Git tags.
*   **Example:**
		```bash
		./scripts/update_version.sh 0.3.0 -y
		```
