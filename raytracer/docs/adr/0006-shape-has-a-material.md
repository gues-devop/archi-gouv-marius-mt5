# 0006 — A Shape Has a Material

## Status

Proposed

## Context

The renderer needs to add shapes and shading strategies independently. Giving
each shape a colour directly would couple geometry to one shading method.
Creating a separate class for each shape-and-shader combination would multiply
classes as new shapes and materials are added.

## Decision

Each concrete `Shape` stores a `std::shared_ptr<Material>` and includes that
material in its `HitInfo`. `Shape` implementations own their intersection
math; `Material` implementations own their shading behavior. `Scene` owns
shapes through `std::unique_ptr<Shape>`.

## Consequences

- A sphere or plane can use any material strategy without changing its
  intersection algorithm.
- A new shape can be added without modifying existing shape implementations.
- Shapes can share a material strategy. The shared ownership is intentional;
  the scene remains the sole owner of each shape.
- The alternative—embedding colour or shading behavior in each shape—would
  couple geometry and appearance and encourage shape/material combinations.
