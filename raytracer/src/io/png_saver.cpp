#include "image/png_saver.h"

#include <lodepng.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
unsigned char toByte(double component) {
    if (!std::isfinite(component)) {
        throw std::invalid_argument("Colour components must be finite");
    }

    const double clamped = std::clamp(component, 0.0, 1.0);
    return static_cast<unsigned char>(std::lround(clamped * 255.0));
}
}

void PngSaver::save(
    Image& image,
    const std::filesystem::path& outputPath
) {
    std::vector<unsigned char> pixels;
    pixels.reserve(
        static_cast<std::size_t>(image.width()) * image.height() * 3
    );

    for (unsigned int y = 0; y < image.height(); ++y) {
        for (unsigned int x = 0; x < image.width(); ++x) {
            const Colour& colour = image.pixel(x, y);
            pixels.push_back(toByte(colour.r()));
            pixels.push_back(toByte(colour.g()));
            pixels.push_back(toByte(colour.b()));
        }
    }

    const std::string outputFile = outputPath.string();
    const unsigned int error = lodepng::encode(
        outputFile,
        pixels,
        image.width(),
        image.height(),
        LCT_RGB
    );
    if (error != 0) {
        throw std::runtime_error(
            "Failed to save PNG: " + std::string(lodepng_error_text(error))
        );
    }
}
