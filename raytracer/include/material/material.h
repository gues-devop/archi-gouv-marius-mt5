#pragma once

#include "colour/colour.h"

class Light;
struct HitInfo;
class Vector;

class Material {
public:
    virtual ~Material() = default;

    // The hit normal and toLight must be unit vectors.
    virtual Colour shade(
        const HitInfo& hitInfo,
        const Vector& toLight
    ) const = 0;
    virtual Colour shade(
        const HitInfo& hitInfo,
        const Light& light
    ) const = 0;
};
