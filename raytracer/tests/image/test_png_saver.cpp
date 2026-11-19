#include "image/png_saver.h"

#include <catch2/catch_test_macros.hpp>
#include <lodepng.h>

#include <chrono>
#include <filesystem>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

TEST_CASE("PNG saver writes the image pixels to the requested file") {
    Image image(2, 2);
    image.setPixel(0, 0, Colour(1, 0, 0));
    image.setPixel(1, 0, Colour(0, 1, 0));
    image.setPixel(0, 1, Colour(0, 0, 1));
    image.setPixel(1, 1, Colour(-0.5, 0.5, 1.5));
    PngSaver saver;
    const std::string filename =
        "raytracer_png_test_" +
        std::to_string(
            std::chrono::steady_clock::now().time_since_epoch().count()
        ) +
        ".png";
    const std::filesystem::path outputPath =
        std::filesystem::temp_directory_path() / filename;

    REQUIRE_NOTHROW(saver.save(image, outputPath));

    std::vector<unsigned char> decodedPixels;
    unsigned int width = 0;
    unsigned int height = 0;
    const unsigned int error = lodepng::decode(
        decodedPixels,
        width,
        height,
        outputPath.string(),
        LCT_RGB
    );

    REQUIRE(error == 0);
    REQUIRE(width == 2);
    REQUIRE(height == 2);
    const std::vector<unsigned char> expectedPixels{
        255, 0, 0,
        0, 255, 0,
        0, 0, 255,
        0, 128, 255
    };
    CHECK(decodedPixels == expectedPixels);

    std::filesystem::remove(outputPath);
}

TEST_CASE("PNG saver rejects non-finite colour components") {
    Image image(1, 1);
    image.setPixel(
        0,
        0,
        Colour(std::numeric_limits<double>::quiet_NaN(), 0, 0)
    );
    PngSaver saver;

    REQUIRE_THROWS_AS(
        saver.save(image, std::filesystem::path("unused.png")),
        std::invalid_argument
    );
}
