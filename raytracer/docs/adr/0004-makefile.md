# 0004 — Add GNU Make Shortcuts

## Context

The project already uses CMake presets, but contributors want memorable
commands for configuring, building, running, testing, and cleaning. Calling
CMake directly remains an alternative.

## Decision

Provide a Makefile with GNU Make targets that wrap the existing CMake presets
and targets. CMake remains the build system.

## Status

Proposed

## Consequences

**Positive:**

- `make build`, `make run`, and `make test` provide short, consistent commands.
- The recipes continue to use the project's CMake configuration and test setup.

**Negative:**

- Contributors need GNU Make in addition to CMake.
- Preset-based shortcuts require CMake 3.21 or newer.
