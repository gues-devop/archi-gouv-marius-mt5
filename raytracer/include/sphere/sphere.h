#pragma once

#include "geometry/shape.h"
#include "material/material.h"
#include "math/vector.h"
#include "ray/ray.h"

#include <memory>

class Sphere : public Shape {
private:
    Vector _center;
    double _radius;
    std::shared_ptr<Material> _material;

public:
    Sphere(
        const Vector& center,
        double radius,
        std::shared_ptr<Material> material
    );

    const Vector& center() const;
    double radius() const;

    // Est-ce que ce rayon me touche? 
    std::optional<HitInfo> hit(const Ray& ray) const override;
};