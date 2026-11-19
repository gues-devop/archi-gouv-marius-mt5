#include "camera/camera.h"
#include "material/flat_shader.h"
#include "scene/scene.h"
#include "sphere/sphere.h"

#include <catch2/catch_test_macros.hpp>

#include <memory>

TEST_CASE("camera stores its position") {
    const Camera camera(Vector(1, 2, 3), 5);

    REQUIRE(camera.position().x() == 1);
    REQUIRE(camera.position().y() == 2);
    REQUIRE(camera.position().z() == 3);
}

TEST_CASE("center pixel ray points along positive Z") {
    Camera camera(Vector(0, 0, -1), 5);

    const Ray ray = camera.rayThroughPixel(2, 1, 5, 3);

    REQUIRE(ray.direction().x() == 0);
    REQUIRE(ray.direction().y() == 0);
    REQUIRE(ray.direction().z() == 1);
}

TEST_CASE("top-right pixel ray has the expected direction") {
    Camera camera(Vector(0, 0, -1), 5);

    const Ray ray = camera.rayThroughPixel(4, 0, 5, 3);

    REQUIRE(ray.direction().x() == 2);
    REQUIRE(ray.direction().y() == 1);
    REQUIRE(ray.direction().z() == 1);
}

TEST_CASE("bottom-left pixel ray has the expected direction") {
    Camera camera(Vector(0, 0, -1), 5);

    const Ray ray = camera.rayThroughPixel(0, 2, 5, 3);

    REQUIRE(ray.direction().x() == -2);
    REQUIRE(ray.direction().y() == -1);
    REQUIRE(ray.direction().z() == 1);
}

TEST_CASE("top-left pixel ray uses the pixel size for a larger image") {
    Camera camera(Vector(0, 0, -1), 2);

    const Ray ray = camera.rayThroughPixel(0, 0, 512, 256);

    REQUIRE(ray.direction().x() == -0.998046875);
    REQUIRE(ray.direction().y() == 0.498046875);
    REQUIRE(ray.direction().z() == 1);
}

TEST_CASE("camera trace returns the nearest shape material colour when hit") {
    const Camera camera(Vector(0, 0, -1), 2);
    const Colour expectedColour(0.25, 0.5, 0.75);
    Scene scene(Vector(-1, 1, -1));
    scene.add(std::make_unique<Sphere>(
        Vector(0, 0, 4),
        1,
        std::make_shared<FlatShader>(expectedColour)
    ));

    const Colour result = camera.trace(
        Ray(Vector(0, 0, -1), Vector(0, 0, 1)),
        scene
    );

    REQUIRE(result.r() == expectedColour.r());
    REQUIRE(result.g() == expectedColour.g());
    REQUIRE(result.b() == expectedColour.b());
}

TEST_CASE("camera trace returns black when the ray misses every shape") {
    const Camera camera(Vector(0, 0, -1), 2);
    Scene scene(Vector(-1, 1, -1));
    scene.add(std::make_unique<Sphere>(
        Vector(5, 0, 4),
        1,
        std::make_shared<FlatShader>(Colour(1, 0, 0))
    ));

    const Colour result = camera.trace(
        Ray(Vector(0, 0, -1), Vector(0, 0, 1)),
        scene
    );

    REQUIRE(result.r() == 0);
    REQUIRE(result.g() == 0);
    REQUIRE(result.b() == 0);
}

TEST_CASE("camera renders an image using the scene") {
    const Camera camera(Vector(0, 0, -1), 2);
    const Colour expectedColour(0.25, 0.5, 0.75);
    Scene scene(Vector(-1, 1, -1));
    scene.add(std::make_unique<Sphere>(
        Vector(0, 0, 4),
        1,
        std::make_shared<FlatShader>(expectedColour)
    ));

    const Image image = camera.render(scene, 1, 1);

    REQUIRE(image.width() == 1);
    REQUIRE(image.height() == 1);
    REQUIRE(image.pixel(0, 0).r() == expectedColour.r());
    REQUIRE(image.pixel(0, 0).g() == expectedColour.g());
    REQUIRE(image.pixel(0, 0).b() == expectedColour.b());
}
