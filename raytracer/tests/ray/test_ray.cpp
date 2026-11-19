#include "ray/ray.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("ray stores its origin and direction") {
    const Ray ray(Vector(1, 2, 3), Vector(4, 5, 6));

    REQUIRE(ray.origin().x() == 1);
    REQUIRE(ray.origin().y() == 2);
    REQUIRE(ray.origin().z() == 3);
    REQUIRE(ray.direction().x() == 4);
    REQUIRE(ray.direction().y() == 5);
    REQUIRE(ray.direction().z() == 6);
}

TEST_CASE("ray calculates a point at a given distance") {
    const Ray ray(Vector(1, 2, 3), Vector(4, 5, 6));

    const Vector point = ray.at(2);

    REQUIRE(point.x() == 9);
    REQUIRE(point.y() == 12);
    REQUIRE(point.z() == 15);
}
