#pragma once

#include "material/material.h"
#include "math/vector.h"

#include <memory>

struct HitInfo {
    double t;
    Vector point;
    Vector normal;
    std::shared_ptr<Material> material;
};
