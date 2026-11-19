#include "image/image.h"

#include <catch2/catch_test_macros.hpp>

#include <stdexcept>

TEST_CASE("setPixel sets the requested pixel and leaves the others black") {
    constexpr unsigned int width = 5;
    constexpr unsigned int height = 4;
    constexpr unsigned int pixelX = 3;
    constexpr unsigned int pixelY = 2;
    const Colour black(0, 0, 0);
    const Colour colour(1, 0.5, 0.25);
    Image image(width, height);

    REQUIRE(image.width() == width);
    REQUIRE(image.height() == height);

    image.setPixel(pixelX, pixelY, colour);

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            const Colour& pixel = image.pixel(x, y);
            if (x == pixelX && y == pixelY) {
                CHECK(pixel.r() == colour.r());
                CHECK(pixel.g() == colour.g());
                CHECK(pixel.b() == colour.b());
            } else {
                CHECK(pixel.r() == black.r());
                CHECK(pixel.g() == black.g());
                CHECK(pixel.b() == black.b());
            }
        }
    }
}

TEST_CASE("pixel coordinates outside the image are rejected") {
    Image image(5, 4);
    const Colour colour(1, 0.5, 0.25);

    REQUIRE_THROWS_AS(image.setPixel(5, 2, colour), std::out_of_range);
    REQUIRE_THROWS_AS(image.pixel(3, 4), std::out_of_range);
}
