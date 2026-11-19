#include "scene/scene.h"

#include <stdexcept>
#include <utility>

Scene::Scene(const Vector& toLight) : _toLight(toLight) {
    if (_toLight.length() == 0) {
        throw std::invalid_argument("Direction to light must not be zero");
    }
    _toLight = _toLight.normalised();
}

const Vector& Scene::toLight() const {
    return _toLight;
}

void Scene::add(std::unique_ptr<Shape> shape) {
    if (!shape) {
        throw std::invalid_argument("Scene shape must not be null");
    }
    _shapes.push_back(std::move(shape));
}

std::optional<HitInfo> Scene::nearestHit(const Ray& ray) const {
    std::optional<HitInfo> nearest;
    for (const std::unique_ptr<Shape>& shape : _shapes) {
        const std::optional<HitInfo> hitInfo = shape->hit(ray);
        if (hitInfo && (!nearest || hitInfo->t < nearest->t)) {
            nearest = hitInfo;
        }
    }
    return nearest;
}
