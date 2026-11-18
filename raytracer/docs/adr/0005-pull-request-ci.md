# 0005 — Run Pull Request CI in the Dev Container

## Context

Every pull request should build the project and run its tests in the same
environment used for development. Running directly on a hosted runner is an
alternative, but could use a different toolchain than the Dev Container.

## Decision

Use GitHub Actions for pull request CI and the `devcontainers/ci` action to run
`make build` and `make test` in the repository's configured Dev Container.

## Status

Proposed

## Consequences

**Positive:**

- Pull request builds and tests use the project's Dev Container configuration.
- Contributors receive automated build and test results for each pull request.

**Negative:**

- CI depends on GitHub Actions and the `devcontainers/ci` action.
- Building the container image adds time to CI runs.
- Making successful CI a merge requirement also requires repository hosting
  settings; this workflow alone does not enforce that requirement.
