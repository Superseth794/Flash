//
// Created by Jaraxus on 30/08/2022.
//

#include <memory>

#include "../include/image/PPMImage.h"
#include "../include/physics/Sphere.hpp"
#include "../include/Renderer/Scene.hpp"

int main() {
    using namespace flash;

    constexpr std::size_t width = 800, height = 450;

//    PPMImage image(100, 100);
//    image.fill([](float x, float y) {
//        return Color(x, y, x * y);
//    });
//    image.build("test0");

    Scene scene("test");

    Material material1{Color::GREEN, 0.3f, 1.f, 0.3f};
    Material material2{Color::RED, 0.3f, 1.f, 0.3f};

    scene.addCollider(std::make_unique<Sphere>(150, Vect3d(100, 900, 0), material1));
    scene.addCollider(std::make_unique<Sphere>(150, Vect3d(0, 400, 0), material2));

    scene.addLight(PointLight(Vect3d(200, 0, 0), Color::WHITE, 1.f));
    scene.addLight(PointLight(Vect3d(-100, 200, 400), Color::WHITE, 1.f));

    PPMImage image2(width, height);
    for (std::size_t y = 0; y < height; ++y) {
        for (std::size_t x = 0; x < width; ++x) {
            image2.setPixel(x, y, scene.cast(x - width / 2.f, y - height / 2.f));
        }
    }
    image2.build("test");

    return 0;
}
