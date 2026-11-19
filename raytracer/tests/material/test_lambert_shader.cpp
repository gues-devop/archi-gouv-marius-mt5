#include "material/lambert_shader.h"

#include "geometry/hit_info.h"
#include "light/light.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Lambert shader returns the surface colour for aligned white light") {
    const Colour surfaceColour(0.8, 0.4, 0.2);
    const LambertShader shader(surfaceColour);
    const HitInfo hitInfo{1, Vector(0, 0, 0), Vector(0, 0, 1), nullptr};
    const Light light(Vector(0, 0, 5), Colour(1, 1, 1));

    const Colour result = shader.shade(hitInfo, light);

    CHECK(result.r() == Catch::Approx(0.8));
    CHECK(result.g() == Catch::Approx(0.4));
    CHECK(result.b() == Catch::Approx(0.2));
}

TEST_CASE("Lambert shader scales colour by the normal and light colours") {
    const Colour surfaceColour(0.8, 0.4, 0.2);
    const LambertShader shader(surfaceColour);
    const HitInfo hitInfo{1, Vector(0, 0, 0), Vector(0, 0, 1), nullptr};
    const Light light(Vector(3, 0, 4), Colour(0.5, 1, 0.25));

    const Colour result = shader.shade(hitInfo, light);

    CHECK(result.r() == Catch::Approx(0.32));
    CHECK(result.g() == Catch::Approx(0.32));
    CHECK(result.b() == Catch::Approx(0.04));
}

TEST_CASE("Lambert shader returns black for light behind the surface") {
    const LambertShader shader(Colour(0.8, 0.4, 0.2));
    const HitInfo hitInfo{1, Vector(0, 0, 0), Vector(0, 0, 1), nullptr};
    const Light light(Vector(0, 0, -1), Colour(1, 1, 1));

    const Colour result = shader.shade(hitInfo, light);

    REQUIRE(result.r() == 0);
    REQUIRE(result.g() == 0);
    REQUIRE(result.b() == 0);
}

TEST_CASE("Lambert shader returns black when the point light is at the hit point") {
    const LambertShader shader(Colour(0.8, 0.4, 0.2));
    const HitInfo hitInfo{1, Vector(0, 0, 0), Vector(0, 0, 1), nullptr};
    const Light light(Vector(0, 0, 0), Colour(1, 1, 1));

    const Colour result = shader.shade(hitInfo, light);

    REQUIRE(result.r() == 0);
    REQUIRE(result.g() == 0);
    REQUIRE(result.b() == 0);
}

TEST_CASE("Lambert shader accepts the unit direction used by a scene") {
    const LambertShader shader(Colour(0.8, 0.4, 0.2));
    const HitInfo hitInfo{1, Vector(0, 0, 0), Vector(0, 0, 1), nullptr};
    const Vector toLight(0.6, 0, 0.8);

    const Colour result = shader.shade(hitInfo, toLight);

    CHECK(result.r() == Catch::Approx(0.64));
    CHECK(result.g() == Catch::Approx(0.32));
    CHECK(result.b() == Catch::Approx(0.16));
}
