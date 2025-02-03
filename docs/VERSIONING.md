# Versioning Strategy for evo-crypter

The `evo-crypter` project uses **Semantic Versioning (SemVer)** as its core versioning scheme. This document outlines how version numbers are assigned, the different types of branches used, and the automated workflows that manage version updates.

## Semantic Versioning (SemVer)

We adhere to the SemVer specification, which means that a version number is composed of three parts:

*   **MAJOR.MINOR.PATCH**

    *   **MAJOR** version is incremented when incompatible API changes are made.
    *   **MINOR** version is incremented when new functionality is added in a backward-compatible manner.
    *   **PATCH** version is incremented when backward-compatible bug fixes are made.

## Branching Model

The `evo-crypter` project employs the following branching model:

*   **`main`:**  The main branch represents the latest stable release of the software. Merges to `main` typically trigger a new release and are associated with a version bump.
*   **`dev`:** The development branch is where new features and bug fixes are integrated before being released to `main`.
*   **`feature/` branches:** Feature branches are created to develop new features. They branch off from `dev` and are merged back into `dev` when the feature is complete and tested.
*   **`release/` branches:** Release branches are used to prepare for a new major release. They branch off from `dev` and are merged into both `main` and `dev` when the release is ready.
*   **`hotfix/` branches:** Hotfix branches are used to address critical bugs in production releases. They branch off from `main` and are merged back into both `main` and `dev` when the hotfix is complete.

## Version Update Workflow

The `evo-crypter` project utilizes GitHub Actions to automate the version update process. The following workflows are defined:

### `update-version.yml`

This workflow is triggered when a pull request is opened, reopened, or synchronized against the `main` or `dev` branch or any other branch. It performs the following actions:

1. **Checks out the code** from the branch where the pull request originates.
2. **Determines the current version** from the `version.txt` file.
3. **Updates the version number** based on the base branch and the head branch of the pull request:
    *   If the base branch is `main` and the head branch is `dev`:
        *   Increments the **MINOR** version.
        *   Resets the **PATCH** version to 0.
    *   If the base branch is `main` and the head branch starts with `release/`:
        *   Increments the **MAJOR** version.
        *   Resets the **MINOR** and **PATCH** versions to 0.
    *   If the base branch is `main` and the head branch starts with `hotfix/`:
        *   Increments the **PATCH** version.
    *   If the base branch is `dev`:
        *   Increments the **PATCH** version.
4. **Updates the `version.txt` file** with the new version.
5. **Commits the change** to `version.txt` with a message like "chore: Bump version to X.Y.Z".
6. **Pushes the commit** back to the pull request's branch using a force push.

### `main-build.yml`

This workflow is triggered when changes are pushed to the `main` branch. It handles the build and release process:

1. **Checks out the code**.
2. **Installs dependencies**.
3. **Builds the project** in Release mode.
4. **Retrieves the current version** from the `version.txt` file.
5. **Creates a GitHub release** tagged with the new version (e.g., `vX.Y.Z`). The executable (`build/evo`) is attached to the release.

### `pr-checks.yml`

This workflow is triggered on pull requests targeting the `main`, `dev` and any other branch. It performs the following checks:

1. **Runs the linter** to ensure code quality.
2. **Runs unit tests** to verify code correctness.
3. **Builds the project** in Debug mode to check for compilation errors.
4. **Perform CodeQL** to check for security vulnerabilities.

### `push-checks.yml`

This workflow is triggered on pushes to branches other than `main`. It performs the following actions:

1. **Checks for existing PRs**: If an open PR already exists for the branch, the workflow exits early, skipping the remaining steps.
2. **Runs the linter** to ensure code quality.
3. **Runs unit tests** to verify code correctness.
4. **Builds the project** in Debug mode to check for compilation errors.

## Manual Version Updates

While the workflows automate most version updates, you can manually update the version number by editing the `version.txt` file and running the `scripts/update_version.sh` script. This script also allows you to create and push a Git tag for the new version.

**Example:**

```bash
./scripts/update_version.sh 0.3.0
```

This will update `version.txt` to `0.3.0`, create a Git tag `v0.3.0`, and optionally push the tag to the remote repository.

## Important Notes

*   The `update-version.yml` workflow requires appropriate permissions to push to branches. Ensure that your repository settings allow GitHub Actions to create and approve pull requests and that the workflow has write permissions.
*   If you have branch protection rules on `main`, make sure they don't prevent the workflow from pushing to pull request branches. You might need to add an exception for the GitHub Actions user.
*   In case of conflicts between the automated version bump and other changes in a pull request, you'll need to resolve them manually.
