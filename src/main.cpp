//
// Created by Jaraxus on 30/08/2022.
//

#include <iostream>
#include <memory>

#include "../include/image/PPMImage.h"
#include "../include/physics/Sphere.hpp"
#include "../include/Renderer/Scene.hpp"
#include "../include/physics/Plane.hpp"
#include "../include/physics/materials/PhongMaterial.h"

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

    auto material0 = std::make_shared<PhongMaterial>(Color::WHITE, 1., 1., 0., 1);
    auto material1 = std::make_shared<PhongMaterial>(Color::GREEN, 1., 1., 0., 1);
    auto material2 = std::make_shared<PhongMaterial>(Color::RED, 1., 1., 0., 1);

    scene.addCollider(std::make_unique<Plane>(Vect3d(0, 0, -30), Vect3d::RIGHT, Vect3d::FRONT, material0));
    scene.addCollider(std::make_unique<Sphere>(150, Vect3d(300, 600, 0), material1));
    scene.addCollider(std::make_unique<Sphere>(150, Vect3d(0, 400, 0), material2));

    scene.addLight(PointLight(Vect3d(-100, 150, 200), Color::WHITE, 0.3));
    scene.addLight(PointLight(Vect3d(0, 150, 300), Color::YELLOW, 0.1));
    scene.addLight(PointLight(Vect3d(900, -100, 900), Color::GREEN, 0.2));

    PPMImage image2(width, height);
    for (std::size_t y = 0; y < height; ++y) {
        for (std::size_t x = 0; x < width; ++x) {
            image2.setPixel(x, y, scene.cast(x / static_cast<double>(width), y / static_cast<double>(height)));
        }
    }
    image2.build("test");

    return 0;
}
