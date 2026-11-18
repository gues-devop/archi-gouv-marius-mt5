#include "sphere/sphere.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("sphere stores its center and radius") {
    const Sphere sphere(Vector(1, 2, 3), 4);

    REQUIRE(sphere.center().x() == 1);
    REQUIRE(sphere.center().y() == 2);
    REQUIRE(sphere.center().z() == 3);
    REQUIRE(sphere.radius() == 4);
}

TEST_CASE("sphere reports when a ray hits it") {
    Sphere sphere(Vector(0, 0, 0), 1);
    Ray ray(Vector(0, 0, -5), Vector(0, 0, 1));

    REQUIRE(sphere.hit(ray));
}

TEST_CASE("sphere reports when a ray misses it") {
    Sphere sphere(Vector(0, 0, 0), 1);
    Ray ray(Vector(0, 2, -5), Vector(0, 0, 1));

    REQUIRE_FALSE(sphere.hit(ray));
}
