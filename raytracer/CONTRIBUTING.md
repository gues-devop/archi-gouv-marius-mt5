# Contributing

Thank you for your interest in contributing to this project.

Please read [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) before participating.

## Set up the development environment

### Dev Container (recommended)

Install Docker (or another Docker-compatible engine), VS Code, and the Dev
Containers extension. Open the repository in VS Code and run **Dev Containers:
Reopen in Container**. The container provides the C++ toolchain, CMake, Ninja,
and GNU Make. It does not configure or build the project automatically; run
`make configure` from the integrated terminal.

### Native setup

Install CMake 3.21 or newer, GNU Make, Git, and a C++20 compiler. The first
configuration fetches LodePNG (and Catch2 when tests are enabled), so it
requires an internet connection.

## Build, run, and test

Run these commands from the repository root:

| Command | Purpose |
|---------|---------|
| `make configure` | Configure the Debug build |
| `make build` | Configure and build the project |
| `make run` | Build and run the demo |
| `make test` | Build and run the tests |
| `make clean` | Remove the generated `build/` directory |

## Test-driven development

Use the red-green-refactor cycle:

1. Add a focused test in `tests/` describing the behavior to implement.
2. Run `make test` and confirm the test fails for the expected reason.
3. Implement the smallest change that makes it pass, then rerun `make test`.
4. Refactor while keeping the tests passing.

## Architecture decision records

Architecture decisions are recorded in [`docs/adr/`](docs/adr/). Read the
relevant ADRs before changing the build, tools, or test setup. Never go against
an accepted ADR. To change a decision, write a new ADR with status `Proposed`
and ask before proceeding; never set an ADR to `Accepted`.

## Submitting a change

Use the issue and pull request templates when opening an issue or pull request.
The CI workflow builds the project and runs its tests in the Dev Container on
every pull request.
