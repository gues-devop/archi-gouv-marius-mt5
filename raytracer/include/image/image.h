#pragma once

#include "colour/colour.h"

#include <vector>

class Image {
public:
    Image(unsigned int width, unsigned int height);

    unsigned int width() const;
    unsigned int height() const;
    void setPixel(unsigned int x, unsigned int y, const Colour& colour);
    const Colour& pixel(unsigned int x, unsigned int y) const;

private:
    unsigned int _width;
    unsigned int _height;
    std::vector<Colour> _pixels;
};
