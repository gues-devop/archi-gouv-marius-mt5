#include "colour/colour.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("colour stores its red, green, and blue components") {
    const Colour colour(0.1, 0.5, 0.9);

    REQUIRE(colour.r() == 0.1);
    REQUIRE(colour.g() == 0.5);
    REQUIRE(colour.b() == 0.9);
}
