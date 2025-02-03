# Contributing to evo-crypter

Thank you for your interest in contributing to `evo-crypter`! We welcome contributions from everyone, whether you're fixing bugs, adding new features, improving documentation, or suggesting ideas.

## Getting Started

1. **Fork the repository:** Click the "Fork" button on the top right of the `evo-crypter` GitHub page to create a copy of the repository under your own GitHub account.

2. **Clone your fork:**
    ```bash
    git clone https://github.com/YOUR_USERNAME/evo-crypter.git
    cd evo-crypter
    ```
    Replace `YOUR_USERNAME` with your GitHub username.

3. **Create a branch:**
    ```bash
    git checkout -b feature/your-feature-name  # For new features
    # OR
    git checkout -b fix/your-bug-fix-name      # For bug fixes
    ```
    Choose a descriptive name for your branch that reflects the work you'll be doing.

## Development Workflow

1. **Make your changes:** Implement your feature, fix the bug, or improve the documentation.
2. **Follow the coding style:** Adhere to the project's coding style guidelines, which are documented in `docs/STYLEGUIDE.md`.
3. **Write tests:** If you're adding new functionality, make sure to write appropriate unit tests and/or integration tests.
4. **Lint your code:** Run the linter to check for style and potential errors:
    ```bash
    ./scripts/lint.sh
    ```
5. **Run tests:** Make sure all tests pass:
    ```bash
    ./scripts/test.sh
    ```
6. **Commit your changes:**
    ```bash
    git add .
    git commit -m "Your descriptive commit message"
    ```
    Write clear and concise commit messages that explain the purpose of your changes. Follow these guidelines for commit messages:
    *   Use the imperative mood (e.g., "Fix: Resolve issue with file handling").
    *   Keep the first line (subject) under 50 characters.
    *   Provide a more detailed explanation in the body of the commit message (if necessary), separated from the subject by a blank line.

## Pull Request Process

1. **Push your branch:**
    ```bash
    git push origin feature/your-feature-name
    # OR
    git push origin fix/your-bug-fix-name
    ```

2. **Create a pull request (PR):** Go to the original `evo-crypter` repository on GitHub and click the "New pull request" button.

3. **Select the branches:** Choose the `dev` branch as the base branch and your feature/fix branch as the compare branch.

4. **Write a description:** Provide a clear and detailed description of your changes in the PR. Explain the problem you're solving, the approach you took, and any relevant details for reviewers.

5. **Address feedback:** Be responsive to feedback from reviewers and make any necessary changes to your code.

6. **Merge:** Once your PR is approved, it will be merged into the `dev` branch by a maintainer.

## Code of Conduct

We expect all contributors to follow the project's [Code of Conduct](CODE_OF_CONDUCT.md) (you'll need to create this file). Please be respectful and considerate of others in all your interactions.

## Questions and Help

If you have any questions or need help with the contribution process, feel free to open an issue on the GitHub repository.

## Adding New Mutation Functions

If you want to add new mutation functions to `evo-crypter`, please refer to the detailed instructions in `docs/MUTATIONS.md`.

## Versioning

The `evo-crypter` project uses Semantic Versioning (SemVer). The versioning strategy and automated workflows are explained in `docs/VERSIONING.md`.

Thank you for contributing to `evo-crypter`!
