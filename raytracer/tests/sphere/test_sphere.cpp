#include "sphere/sphere.h"
#include "material/flat_shader.h"
#include "light/light.h"

#include <catch2/catch_test_macros.hpp>

#include <memory>

TEST_CASE("sphere stores its center and radius") {
    const Sphere sphere(
        Vector(1, 2, 3),
        4,
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    );

    REQUIRE(sphere.center().x() == 1);
    REQUIRE(sphere.center().y() == 2);
    REQUIRE(sphere.center().z() == 3);
    REQUIRE(sphere.radius() == 4);
}

TEST_CASE("sphere returns hit information for the closest intersection") {
    Sphere sphere(
        Vector(0, 0, 0),
        1,
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    );
    const Ray ray(Vector(0, 0, -5), Vector(0, 0, 1));

    const std::optional<HitInfo> hitInfo = sphere.hit(ray);

    REQUIRE(hitInfo.has_value());
    REQUIRE(hitInfo->t == 4);
    REQUIRE(hitInfo->point.x() == 0);
    REQUIRE(hitInfo->point.y() == 0);
    REQUIRE(hitInfo->point.z() == -1);
    REQUIRE(hitInfo->normal.x() == 0);
    REQUIRE(hitInfo->normal.y() == 0);
    REQUIRE(hitInfo->normal.z() == -1);
    const Light light(Vector(0, 0, -2), Colour(1, 1, 1));
    const Colour shaded = hitInfo->material->shade(*hitInfo, light);
    REQUIRE(shaded.r() == 1);
    REQUIRE(shaded.g() == 0);
    REQUIRE(shaded.b() == 0);
}

TEST_CASE("sphere reports when a ray misses it") {
    Sphere sphere(
        Vector(0, 0, 0),
        1,
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    );
    const Ray ray(Vector(0, 2, -5), Vector(0, 0, 1));

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("sphere returns no hit when all intersections are behind the ray") {
    const Sphere sphere(
        Vector(0, 0, 0),
        1,
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    );
    const Ray ray(Vector(0, 0, 5), Vector(0, 0, 1));

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("sphere does not report an intersection at the ray origin") {
    const Sphere sphere(
        Vector(0, 0, 0),
        1,
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    );
    const Ray ray(Vector(0, 0, -1), Vector(0, 0, -1));

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("sphere radius must be positive") {
    REQUIRE_THROWS(Sphere(
        Vector(0, 0, 0),
        0,
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    ));
}

TEST_CASE("sphere ignores a negative intersection when the ray starts inside") {
    const Sphere sphere(
        Vector(0, 0, 0),
        1,
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    );
    const Ray ray(Vector(0, 0, 0), Vector(0, 0, 1));

    const std::optional<HitInfo> hitInfo = sphere.hit(ray);

    REQUIRE(hitInfo.has_value());
    REQUIRE(hitInfo->point.x() == 0);
    REQUIRE(hitInfo->point.y() == 0);
    REQUIRE(hitInfo->point.z() == 1);
    REQUIRE(hitInfo->t == 1);
    REQUIRE(hitInfo->normal.z() == 1);
}

TEST_CASE("sphere finds the forward hit when the ray starts inside it") {
    const Sphere sphere(
        Vector(0, 0, 1),
        5,
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    );
    const Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));

    const std::optional<HitInfo> hitInfo = sphere.hit(ray);

    REQUIRE(hitInfo.has_value());
    REQUIRE(hitInfo->t == 7);
    REQUIRE(hitInfo->point.x() == 0);
    REQUIRE(hitInfo->point.y() == 0);
    REQUIRE(hitInfo->point.z() == 6);
    REQUIRE(hitInfo->normal.x() == 0);
    REQUIRE(hitInfo->normal.y() == 0);
    REQUIRE(hitInfo->normal.z() == 1);
}
