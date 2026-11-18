# 0001 — Use a Dev Container

## Context

Contributors join the project on Windows, macOS, and Linux, each with different compiler versions and tool installations. Differences in compiler versions or missing tools can cause "works on my machine" failures during the course.

Alternatives considered:

- **Native setup with documented prerequisites** — avoids container setup, but requires each participant to install and maintain a compatible toolchain.
- **CI-only standardisation** — catches integration problems but does not provide a shared environment for local development or live demos.

## Decision

Provide a VS Code Dev Container using `mcr.microsoft.com/devcontainers/cpp:1-debian-12`. The image provides the C++ toolchain and CMake; the Dockerfile installs Ninja.

## Status

Proposed

## Consequences

**Positive:**

- Contributors use a shared Linux development environment with the project's build tools.
- New contributors can avoid manually installing and version-matching the toolchain on their host.

**Negative:**

- Using the container requires VS Code, the Dev Containers extension, and a Docker-compatible engine.
- Container startup adds a delay, especially on first open.
- The environment is Linux-based; contributors choosing a native workflow must manage their own toolchain.
