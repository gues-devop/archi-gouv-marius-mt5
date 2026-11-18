# 0002 — Use CMake (with CTest)

## Context

The project must build on Windows, macOS, and Linux, and support VS Code with CMake Tools, Zed, and plain terminal workflows. It also needs to fetch Catch2 at configure time without requiring a separate package manager.

Alternatives considered:

- **Make / GNU Make** — a simple option, but would require additional tooling on some platforms and IDE integration.
- **Meson** — a modern build system, but would add a different tool to learn and integrate.
- **Bazel** — capable of handling large projects, but adds complexity for this small course project.

## Decision

Use CMake 3.20 or newer to configure and build the project, with CTest for running tests. Use `FetchContent` to fetch Catch2 v3.8.1 at configure time, and `catch_discover_tests` to register each test case with CTest.

## Status

Proposed

## Consequences

**Positive:**

- The same build configuration supports the target platforms and can be used from the terminal and VS Code's CMake Tools.
- `FetchContent` avoids requiring a separate package manager for Catch2.
- CTest provides a uniform command for running registered tests.

**Negative:**

- CMake's syntax can have a learning curve for participants unfamiliar with it.
- The cross-platform preset shortcuts require CMake 3.21 or newer; manual configuration still supports the project's 3.20 minimum.
- `FetchContent` downloads Catch2 during configuration, requiring Git and internet access on the first configure.
- The minimum CMake version may not be pre-installed on older systems.
- The repository configures VS Code's CMake Tools, but has no Zed-specific configuration.
