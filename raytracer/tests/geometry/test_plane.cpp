#include "geometry/plane.h"
#include "material/flat_shader.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <memory>

TEST_CASE("plane normalises its normal vector") {
    const Plane plane(
        Vector(8, 0, 0),
        Vector(3, 4, 0),
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    );

    REQUIRE(plane.normal().x() == Catch::Approx(0.6));
    REQUIRE(plane.normal().y() == Catch::Approx(0.8));
    REQUIRE(plane.normal().z() == 0);
}

TEST_CASE("plane returns the intersection point and material") {
    const auto material = std::make_shared<FlatShader>(Colour(1, 0, 0));
    const Plane plane(Vector(8, 0, 0), Vector(3, 4, 0), material);
    const Ray ray(Vector(-8, 0, 0), Vector(4, 3, 0));

    const std::optional<HitInfo> hitInfo = plane.hit(ray);

    REQUIRE(hitInfo.has_value());
    REQUIRE(hitInfo->t == Catch::Approx(2));
    REQUIRE(hitInfo->point.x() == Catch::Approx(0));
    REQUIRE(hitInfo->point.y() == Catch::Approx(6));
    REQUIRE(hitInfo->point.z() == Catch::Approx(0));
    REQUIRE(hitInfo->material == material);
}

TEST_CASE("floor returns the expected hit and green material") {
    const auto material = std::make_shared<FlatShader>(Colour(0, 1, 0));
    const Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), material);
    const Ray ray(Vector(0, 8, 0), Vector(3, -4, 0));

    const std::optional<HitInfo> hitInfo = floor.hit(ray);

    REQUIRE(hitInfo.has_value());
    REQUIRE(hitInfo->t == 2);
    REQUIRE(hitInfo->point.x() == 6);
    REQUIRE(hitInfo->point.y() == 0);
    REQUIRE(hitInfo->point.z() == 0);
    REQUIRE(hitInfo->normal.x() == 0);
    REQUIRE(hitInfo->normal.y() == 1);
    REQUIRE(hitInfo->normal.z() == 0);
    REQUIRE(hitInfo->material == material);
    const Colour colour = hitInfo->material->shade(
        *hitInfo,
        Vector(0, 1, 0)
    );
    REQUIRE(colour.r() == 0);
    REQUIRE(colour.g() == 1);
    REQUIRE(colour.b() == 0);
}

TEST_CASE("plane does not intersect a parallel ray") {
    const Plane plane(
        Vector(0, 0, 0),
        Vector(0, 1, 0),
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    );
    const Ray ray(Vector(0, 8, 0), Vector(5, 0, 0));

    REQUIRE_FALSE(plane.hit(ray).has_value());
}

TEST_CASE("plane does not intersect behind the ray") {
    const Plane plane(
        Vector(0, 0, 0),
        Vector(0, 1, 0),
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    );
    const Ray ray(Vector(0, 8, 0), Vector(3, 4, 0));

    REQUIRE_FALSE(plane.hit(ray).has_value());
}

TEST_CASE("plane requires a non-zero normal") {
    REQUIRE_THROWS(Plane(
        Vector(0, 0, 0),
        Vector(0, 0, 0),
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    ));
}
