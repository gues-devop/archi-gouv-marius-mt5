#include "camera/camera.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("camera stores its position and faces positive Z") {
    const Camera camera(Vector(1, 2, 3));

    REQUIRE(camera.position().x() == 1);
    REQUIRE(camera.position().y() == 2);
    REQUIRE(camera.position().z() == 3);
    REQUIRE(camera.direction().x() == 0);
    REQUIRE(camera.direction().y() == 0);
    REQUIRE(camera.direction().z() == 1);
}

TEST_CASE("camera creates a ray through its center") {
    const Camera camera(Vector(1, 2, 3));

    const Ray ray = camera.rayThroughCenter();

    REQUIRE(ray.origin().x() == 1);
    REQUIRE(ray.origin().y() == 2);
    REQUIRE(ray.origin().z() == 3);
    REQUIRE(ray.direction().x() == 0);
    REQUIRE(ray.direction().y() == 0);
    REQUIRE(ray.direction().z() == 1);
}
