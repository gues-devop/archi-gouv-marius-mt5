#include "camera/camera.h"

Camera::Camera(const Vector& position) : _position(position) {}

const Vector& Camera::position() const {
    return _position;
}

Vector Camera::direction() const {
    return Vector(0, 0, 1);
}

Ray Camera::rayThroughCenter() const {
    return Ray(_position, direction());
}