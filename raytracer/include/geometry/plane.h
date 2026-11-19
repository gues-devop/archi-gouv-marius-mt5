#pragma once

#include "geometry/shape.h"

#include <memory>
#include <optional>

class Plane : public Shape {
public:
    Plane(
        const Vector& point,
        const Vector& normal,
        std::shared_ptr<Material> material
    );

    const Vector& point() const;
    const Vector& normal() const;
    std::optional<HitInfo> hit(const Ray& ray) const override;

private:
    Vector _point;
    Vector _normal;
    std::shared_ptr<Material> _material;
};
