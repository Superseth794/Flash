//
// Created by Jaraxus on 30/08/2022.
//

#include <iostream>
#include <memory>

#include "../include/image/PPMImage.h"
#include "../include/physics/Sphere.hpp"
#include "../include/Renderer/Scene.hpp"

int main() {
    using namespace flash;

    constexpr std::size_t width = 800, height = 450;
    const double fov = 90;

//    PPMImage image(100, 100);
//    image.fill([](float x, float y) {
//        return Color(x, y, x * y);
//    });
//    image.build("test0");

    Scene scene("test");

    auto& camera = scene.setCamera(Camera(Vect3d::ZERO, width, height, M_PI / 180. * fov));
    std::cout << camera.rayAt(0, 0) << std::endl;
    std::cout << camera.rayAt(0.5, 0.5) << std::endl;
    std::cout << camera.rayAt(1, 1) << std::endl;

    Material material1{Color::GREEN, 2.f, 1.f, 0.f, 7};
    Material material2{Color::WHITE, 3.0f, 2.f, 0.f, 100};

    scene.addCollider(std::make_unique<Sphere>(150, Vect3d(100, 600, 1), material1));
    scene.addCollider(std::make_unique<Sphere>(150, Vect3d(0, 400, 0), material2));

    scene.addLight(PointLight(Vect3d(200, 0, 0), Color::WHITE, 1.f));
    scene.addLight(PointLight(Vect3d(-100, 200, 400), Color::YELLOW, 1.f));
    scene.addLight(PointLight(Vect3d(-900, -100, -900), Color::GREEN, 1.f));

    PPMImage image2(width, height);
    for (std::size_t y = 0; y < height; ++y) {
        for (std::size_t x = 0; x < width; ++x) {
            image2.setPixel(x, y, scene.cast(x / static_cast<double>(width), y / static_cast<double>(height)));
        }
    }
    image2.build("test");

    return 0;
}
