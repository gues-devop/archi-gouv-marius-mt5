#pragma once

#include "geometry/hit_info.h"
#include "ray/ray.h"

#include <optional>

class Shape {
public:
    virtual ~Shape() = default;

    // Returns the nearest hit with t > 0 and a unit normal, or no hit.
    virtual std::optional<HitInfo> hit(const Ray& ray) const = 0;
};
