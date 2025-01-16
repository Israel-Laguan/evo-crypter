# Versioning Strategy for evo-crypter

This document outlines the versioning strategy used in the `evo-crypter` project, which is based on [Semantic Versioning 2.0.0](https://semver.org/) (SemVer) and incorporates elements of [Gitflow Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow).

## Semantic Versioning (SemVer)

We use Semantic Versioning to manage the project's releases. SemVer defines a version number as:

`MAJOR.MINOR.PATCH`

Where:

*   **MAJOR** version is incremented when incompatible API changes are made.
*   **MINOR** version is incremented when functionality is added in a backward-compatible manner.
*   **PATCH** version is incremented when backward-compatible bug fixes are made.

## Gitflow Workflow and Branching Model

We utilize a simplified Gitflow model with the following branches:

*   **`main`:** Represents the production-ready code. Only merges from `dev`, `release/*`, and `hotfix/*` branches are allowed.
*   **`dev`:** The main development branch. All feature branches merge into `dev`.
*   **`feature/*` or `feat/*`:** Branches for developing new features. These are created from `dev` and merge back into `dev`.
*   **`release/*`:** Branches for preparing releases. These are created from `dev` and merge into both `main` and `dev`.
*   **`hotfix/*`:** Branches for critical bug fixes in production. These are created from `main` and merge into both `main` and `dev`.

## Version Updates in GitHub Actions

Our GitHub Actions workflows automate version updates based on the branch being merged and the source branch of the pull request:

**`push-checks.yml`:**

*   Runs on pushes to any branch **except** `main`.
*   If the push is to a `feature/*` or `feat/*` branch, the **PATCH** version is automatically incremented.

**`dev-build.yml`:**

*   Runs on pushes to the `dev` branch.
*   Automatically increments the **PATCH** version.

**`main-build.yml`:**

*   Runs on pushes to the `main` branch (typically through merges).
*   Determines the version update based on the source branch of the merge:
    *   **`dev`:** Increments the **MINOR** version and resets the **PATCH** version to 0.
    *   **`release/*`:** Increments the **MAJOR** version and resets the **MINOR** and **PATCH** versions to 0.
    *   **`hotfix/*` or direct pushes:** Increments the **PATCH** version.

## Branch Protection Rules

To enforce this workflow, we use GitHub branch protection rules:

*   **`main` branch:**
    *   Require pull request reviews before merging.
    *   Require status checks to pass before merging (ensuring `main-build.yml` passes).
    *   Prohibit direct pushes (except for very specific cases, where the **PATCH** version will be incremented).
    *   Only allow merges from `dev`, `release/*`, and `hotfix/*` branches.
*   **`dev` branch:**
    *   Require pull request reviews before merging.
    *   Require status checks to pass before merging (ensuring `dev-build.yml` passes).
    *   Only allow merges from `feature/*`, `feat/*`, and `release/*` branches.
*   **`feature/*`, `feat/*`, `release/*`, and `hotfix/*` branches:**
    *   Require status checks to pass before merging (ensuring `push-checks.yml` passes).

## Examples

**Scenario 1: New Feature Development**

1. A developer creates a branch `feature/new-encryption` from `dev`.
2. Code is developed and pushed to `feature/new-encryption`. `push-checks.yml` runs and increments the **PATCH** version (e.g., 0.1.0 becomes 0.1.1).
3. A pull request is created to merge `feature/new-encryption` into `dev`.
4. `pr-checks.yml` runs to ensure code quality.
5. After review, the pull request is merged into `dev`.
6. `dev-build.yml` runs and increments the **PATCH** version again (e.g., 0.1.1 becomes 0.1.2).

**Scenario 2: Release Preparation**

1. A branch `release/1.0.0` is created from `dev`.
2. Final testing and adjustments are made on the `release/1.0.0` branch.
3. A pull request is created to merge `release/1.0.0` into `main`.
4. `pr-checks.yml` runs.
5. After review, the pull request is merged into `main`.
6. `main-build.yml` runs, detects the `release/*` branch, increments the **MAJOR** version (e.g., 0.1.2 becomes 1.0.0), and creates a GitHub release.
7. The `release/1.0.0` branch is also merged back into `dev` (potentially with manual conflict resolution if necessary).

**Scenario 3: Hotfix**

1. A critical bug is found in production (version 1.0.0).
2. A branch `hotfix/typo-fix` is created from `main`.
3. The bug fix is implemented and pushed to `hotfix/typo-fix`. `push-checks.yml` runs.
4. A pull request is created to merge `hotfix/typo-fix` into `main`.
5. `pr-checks.yml` runs.
6. After review, the pull request is merged into `main`.
7. `main-build.yml` runs, detects the `hotfix/*` branch, increments the **PATCH** version (e.g., 1.0.0 becomes 1.0.1), and creates a GitHub release.
8. The `hotfix/typo-fix` branch is also merged into `dev`.

## Conclusion

This versioning strategy, combined with GitHub Actions and branch protection rules, provides a structured and automated way to manage releases, ensuring code quality and consistency in the `evo-crypter` project.
