#include "image/image.h"

#include <cstddef>
#include <limits>
#include <stdexcept>

namespace {
std::size_t pixelCount(unsigned int width, unsigned int height) {
    if (height != 0 &&
        width > std::numeric_limits<std::size_t>::max() / height) {
        throw std::length_error("Image dimensions are too large");
    }

    return static_cast<std::size_t>(width) * height;
}

std::size_t pixelIndex(
    unsigned int x,
    unsigned int y,
    unsigned int width,
    unsigned int height
) {
    if (x >= width || y >= height) {
        throw std::out_of_range("Pixel coordinates are outside the image");
    }

    return static_cast<std::size_t>(y) * width + x;
}
}

Image::Image(unsigned int width, unsigned int height)
    : _width(width),
      _height(height),
      _pixels(pixelCount(width, height), Colour(0, 0, 0)) {}

unsigned int Image::width() const {
    return _width;
}

unsigned int Image::height() const {
    return _height;
}

void Image::setPixel(unsigned int x, unsigned int y, const Colour& colour) {
    _pixels[pixelIndex(x, y, _width, _height)] = colour;
}

const Colour& Image::pixel(unsigned int x, unsigned int y) const {
    return _pixels[pixelIndex(x, y, _width, _height)];
}
