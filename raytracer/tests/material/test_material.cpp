#include "material/flat_shader.h"
#include "light/light.h"
#include "geometry/hit_info.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("flat shader returns its configured colour") {
    const Colour expectedColour(0.25, 0.5, 0.75);
    const FlatShader shader(expectedColour);
    const HitInfo hitInfo{1, Vector(0, 0, 0), Vector(0, 0, 1), nullptr};
    const Light light(Vector(0, 0, 1), Colour(1, 1, 1));

    const Colour result = shader.shade(hitInfo, light);

    REQUIRE(result.r() == expectedColour.r());
    REQUIRE(result.g() == expectedColour.g());
    REQUIRE(result.b() == expectedColour.b());
}
