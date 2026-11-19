#pragma once

#include "material/material.h"

class FlatShader : public Material {
public:
    explicit FlatShader(const Colour& colour);

    Colour shade(
        const HitInfo& hitInfo,
        const Vector& toLight
    ) const override;
    Colour shade(
        const HitInfo& hitInfo,
        const Light& light
    ) const override;

private:
    Colour _colour;
};
