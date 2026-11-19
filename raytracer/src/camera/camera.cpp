#include "camera/camera.h"

#include <stdexcept>

Camera::Camera(const Vector& position, const double screenWidth) :
    _position(position), _screenWidth(screenWidth) {}

const Vector& Camera::position() const {
    return _position;
}

Ray Camera::rayThroughCenter() const {
    const Vector direction(0, 0, 1);
    return Ray(_position, direction);
}

Ray Camera::rayThroughPixel(
    int column,
    int row,
    int imageWidth,
    int imageHeight
) const {
    const double pixelSize = _screenWidth / imageWidth;

    const double x = ((column + 0.5) - (imageWidth / 2.0)) * pixelSize;
    const double y = -((row + 0.5) - (imageHeight / 2.0)) * pixelSize;

    const Vector pixelPosition(x, y, 0);
    const Vector direction = pixelPosition - _position;

    return Ray(_position, direction);
}

Colour Camera::trace(const Ray& ray, const Scene& scene) const {
    const std::optional<HitInfo> hitInfo = scene.nearestHit(ray);
    if (hitInfo) {
        return hitInfo->material->shade(*hitInfo, scene.toLight());
    }

    return Colour(0, 0, 0);
}

Image Camera::render(
    const Scene& scene,
    int imageWidth,
    int imageHeight
) const {
    if (imageWidth <= 0 || imageHeight <= 0) {
        throw std::invalid_argument("Image dimensions must be positive");
    }

    Image image(
        static_cast<unsigned int>(imageWidth),
        static_cast<unsigned int>(imageHeight)
    );
    for (int row = 0; row < imageHeight; ++row) {
        for (int column = 0; column < imageWidth; ++column) {
            const Ray ray = rayThroughPixel(
                column,
                row,
                imageWidth,
                imageHeight
            );
            image.setPixel(
                static_cast<unsigned int>(column),
                static_cast<unsigned int>(row),
                trace(ray, scene)
            );
        }
    }
    return image;
}