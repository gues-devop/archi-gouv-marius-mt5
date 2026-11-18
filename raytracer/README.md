# C++ Raytracer

A small, cross-platform C++ starter project. It uses CMake to build on Windows,
macOS, and Linux, and includes a VS Code Dev Container for a consistent
Linux-based development environment.

## Requirements

- CMake 3.21 or newer for the Makefile shortcuts (the project itself requires 3.20)
- GNU Make for the shortcut commands below
- A C++20 compiler:
  - Windows: Visual Studio 2022 (Desktop development with C++)
  - macOS: Xcode Command Line Tools
  - Linux: GCC or Clang
- Git, and an internet connection the first time CMake configures the project
  (Catch2 is downloaded and built by CMake)

## Build, run, and test

Run these commands from the repository root:

```sh
make configure
make build
make run
make test
```

Clean the generated build directory:

```sh
make clean
```

The test framework is Catch2 3, fetched and pinned to v3.8.1 via CMake
FetchContent. Tests are enabled by default. To configure without building the
test dependency, use `-DBUILD_TESTING=OFF`.

## TDD workflow

Use the red-green-refactor cycle:

1. Add a focused test in `tests/` describing the next behavior.
2. Run `make test` and confirm the new test fails for the expected reason (red).
3. Implement the smallest change that makes it pass, then rerun the tests
   (green).
4. Refactor while keeping the tests green.

Tests link to the `raytracer_core` library, so application logic can be tested
without launching the demo executable. Catch2 assertions and test cases are
available in `tests/test_greeting.cpp`.

## VS Code Dev Container

Install Docker Desktop (or another Docker-compatible engine) and the VS Code
Dev Containers extension. Open this repository in VS Code, then run
**Dev Containers: Reopen in Container** from the Command Palette. The container
provides a C++ compiler, CMake, Ninja, and GNU Make; build and test using the
commands above from the integrated terminal.

## Project layout

```text
.devcontainer/  VS Code Dev Container configuration
include/        Public project headers
src/            Demo executable and implementation
tests/          Catch2 tests
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for setup and contribution instructions,
[CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) for community expectations, and
[LICENSE](LICENSE) for licensing terms. Issue and pull request templates are
available under `.github/`.
