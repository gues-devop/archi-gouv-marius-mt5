#include "light/light.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("light stores its position and colour") {
    const Light light(Vector(1, 2, 3), Colour(0.25, 0.5, 0.75));

    REQUIRE(light.position().x() == 1);
    REQUIRE(light.position().y() == 2);
    REQUIRE(light.position().z() == 3);
    REQUIRE(light.colour().r() == 0.25);
    REQUIRE(light.colour().g() == 0.5);
    REQUIRE(light.colour().b() == 0.75);
}
