#pragma once

#include "colour/colour.h"
#include "image/image.h"
#include "math/vector.h"
#include "ray/ray.h"
#include "scene/scene.h"

class Camera {
private:
    Vector _position;
    double _screenWidth;

public:
    Camera(const Vector& position, const double screenWidth);

    const Vector& position() const;

    Ray rayThroughCenter() const;

    Ray rayThroughPixel(
        int column,
        int row,
        int imageWidth,
        int imageHeight
    ) const;

    Colour trace(const Ray& ray, const Scene& scene) const;
    Image render(const Scene& scene, int imageWidth, int imageHeight) const;
};
