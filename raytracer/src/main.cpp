#include "greeting.h"

#include <iostream>
#include "camera/camera.h"
#include "colour/colour.h"
#include "ray/ray.h"
#include "sphere/sphere.h"

int main() {
    std::cout << "Hello, Raytracer!\n";

    Camera camera(Vector(0, 0, -1));
    Ray ray = camera.rayThroughCenter();

    // Sphere, centre et rayon
    Sphere sphere(Vector(0, 0, 9), 5);


    Colour colour(0, 0, 0);
    bool hit = sphere.hit(ray);
    if (hit) {
       colour = Colour(1, 0, 0);
    }

    std::cout << "Colour: (" << colour.r() << ", " << colour.g() << ", " << colour.b() << ")\n"; 

    return 0;
}
