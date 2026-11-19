#include "geometry/plane.h"
#include "material/flat_shader.h"
#include "scene/scene.h"
#include "sphere/sphere.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <memory>

namespace {
const Ray testRay(Vector(0, 0, -1), Vector(0, 0, 1));

void addSphereAndPlane(Scene& scene, bool addPlaneFirst) {
    auto sphere = std::make_unique<Sphere>(
        Vector(0, 0, 9),
        5,
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    );
    auto plane = std::make_unique<Plane>(
        Vector(0, 0, 2),
        Vector(0, 0, -1),
        std::make_shared<FlatShader>(Colour(0, 0, 1))
    );

    if (addPlaneFirst) {
        scene.add(std::move(plane));
        scene.add(std::move(sphere));
    } else {
        scene.add(std::move(sphere));
        scene.add(std::move(plane));
    }
}
}

TEST_CASE("scene finds the nearest hit when the sphere is added first") {
    Scene scene(Vector(-1, 1, -1));
    addSphereAndPlane(scene, false);

    const std::optional<HitInfo> hitInfo = scene.nearestHit(testRay);

    REQUIRE(hitInfo.has_value());
    REQUIRE(hitInfo->t == 3);
    const Colour colour = hitInfo->material->shade(*hitInfo, scene.toLight());
    REQUIRE(colour.r() == 0);
    REQUIRE(colour.g() == 0);
    REQUIRE(colour.b() == 1);
}

TEST_CASE("scene finds the nearest hit when the plane is added first") {
    Scene scene(Vector(-1, 1, -1));
    addSphereAndPlane(scene, true);

    const std::optional<HitInfo> hitInfo = scene.nearestHit(testRay);

    REQUIRE(hitInfo.has_value());
    REQUIRE(hitInfo->t == 3);
}

TEST_CASE("scene keeps the sphere when a plane is farther away") {
    Scene scene(Vector(-1, 1, -1));
    scene.add(std::make_unique<Sphere>(
        Vector(0, 0, 9),
        5,
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    ));
    scene.add(std::make_unique<Plane>(
        Vector(0, 0, 20),
        Vector(0, 0, -1),
        std::make_shared<FlatShader>(Colour(0, 0, 1))
    ));

    const std::optional<HitInfo> hitInfo = scene.nearestHit(testRay);

    REQUIRE(hitInfo.has_value());
    REQUIRE(hitInfo->t == 5);
    const Colour colour = hitInfo->material->shade(*hitInfo, scene.toLight());
    REQUIRE(colour.r() == 1);
    REQUIRE(colour.g() == 0);
    REQUIRE(colour.b() == 0);
}

TEST_CASE("scene reports no hit when none of its shapes are hit") {
    Scene scene(Vector(-1, 1, -1));
    scene.add(std::make_unique<Sphere>(
        Vector(6, 0, 9),
        5,
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    ));

    REQUIRE_FALSE(scene.nearestHit(testRay).has_value());
}

TEST_CASE("empty scene reports no hit") {
    const Scene scene(Vector(-1, 1, -1));

    REQUIRE_FALSE(scene.nearestHit(testRay).has_value());
}

TEST_CASE("scene normalises the direction to the light") {
    const Scene scene(Vector(0, 3, -4));

    REQUIRE(scene.toLight().x() == Catch::Approx(0));
    REQUIRE(scene.toLight().y() == Catch::Approx(0.6));
    REQUIRE(scene.toLight().z() == Catch::Approx(-0.8));
}

TEST_CASE("scene requires a non-zero direction to the light") {
    REQUIRE_THROWS(Scene(Vector(0, 0, 0)));
}
