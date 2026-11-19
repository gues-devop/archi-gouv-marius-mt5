#include <filesystem>
#include <iostream>

#include "camera/camera.h"
#include "colour/colour.h"
#include "image/image.h"
#include "image/png_saver.h"
#include "material/lambert_shader.h"
#include "geometry/plane.h"
#include "scene/scene.h"
#include "sphere/sphere.h"

#include <memory>

int main() {
    std::cout << "Hello, Raytracer!\n";

    const int imageWidth = 512;
    const int imageHeight = 512;

    Camera camera(Vector(0, 0, -1), 2.0);
    Scene scene(Vector(-1, 1, -1));

    const auto material = std::make_shared<LambertShader>(Colour(1, 0, 0));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, material));
    scene.add(std::make_unique<Plane>(
        Vector(0, -5, 0),
        Vector(0, 1, 0),
        std::make_shared<LambertShader>(Colour(0.8, 0.8, 0.8))
    ));

    Image image = camera.render(scene, imageWidth, imageHeight);

    PngSaver saver;
    saver.save(image, "output.png");

    return 0;
}

