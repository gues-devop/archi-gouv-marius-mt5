#include "geometry/plane.h"

#include <stdexcept>
#include <utility>

Plane::Plane(
    const Vector& point,
    const Vector& normal,
    std::shared_ptr<Material> material
) : _point(point),
    _normal(normal),
    _material(std::move(material)) {
    if (normal.length() == 0) {
        throw std::invalid_argument("Plane normal must not be zero");
    }
    if (!_material) {
        throw std::invalid_argument("Plane material must not be null");
    }
    _normal = normal.normalised();
}

const Vector& Plane::point() const {
    return _point;
}

const Vector& Plane::normal() const {
    return _normal;
}

std::optional<HitInfo> Plane::hit(const Ray& ray) const {
    const double normalDotDirection = _normal.dot(ray.direction());
    if (normalDotDirection == 0) {
        return std::nullopt;
    }

    const double t =
        _normal.dot(_point - ray.origin()) / normalDotDirection;
    if (t <= 0) {
        return std::nullopt;
    }

    return HitInfo{t, ray.at(t), _normal, _material};
}
