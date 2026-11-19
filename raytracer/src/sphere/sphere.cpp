#include "sphere/sphere.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

Sphere::Sphere(
    const Vector& center,
    double radius,
    std::shared_ptr<Material> material
) : _center(center), _radius(radius), _material(std::move(material)) {
    if (_radius <= 0) {
        throw std::invalid_argument("Sphere radius must be positive");
    }
    if (!_material) {
        throw std::invalid_argument("Sphere material must not be null");
    }
}

const Vector& Sphere::center() const { return _center; }
double Sphere::radius() const { return _radius; }

std::optional<HitInfo> Sphere::hit(const Ray& ray) const {
    const Vector D = ray.direction();
    const Vector O = ray.origin();
    const Vector C = _center;

    const Vector L = O - C;

    const double a = D.dot(D);
    if (a == 0) {
        return std::nullopt;
    }

    const double b = 2 * D.dot(L);
    const double c = L.dot(L) - _radius * _radius;

    const double delta = b * b - 4 * a * c;
    if (delta < 0) {
        return std::nullopt;
    }

    const double t1 = (-b + std::sqrt(delta)) / (2 * a);
    const double t2 = (-b - std::sqrt(delta)) / (2 * a);
    const double nearT = std::min(t1, t2);
    const double farT = std::max(t1, t2);

    if (farT <= 0 || !std::isfinite(farT)) {
        return std::nullopt;
    }

    const double hitT = nearT > 0 ? nearT : farT;
    const Vector point = ray.at(hitT);
    const Vector normal = (point - _center).normalised();
    return HitInfo{hitT, point, normal, _material};
}