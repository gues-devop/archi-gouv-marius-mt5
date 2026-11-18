#pragma once

#include "math/vector.h"
#include "ray/ray.h"

class Camera {
public:
    explicit Camera(const Vector& position);

    const Vector& position() const;
    Vector direction() const;
    Ray rayThroughCenter() const;

private:
    Vector _position;
};
