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

    constexpr std::size_t width = 1000, height = 1000;

//    PPMImage image(100, 100);
//    image.fill([](float x, float y) {
//        return Color(x, y, x * y);
//    });
//    image.build("test0");

    Scene scene("test");
    scene.addCollider(std::make_unique<Sphere>(300, Vect3f(100, -1000, 0), Color::GREEN));
    scene.addCollider(std::make_unique<Sphere>(300, Vect3f(0, 100, 0), Color::RED));

    PPMImage image2(width, height);
    for (std::size_t y = 0; y < height; ++y) {
        for (std::size_t x = 0; x < width; ++x) {
            image2.setPixel(x, y, scene.cast(x - width / 2.f, y - height / 2.f));
        }
    }
    image2.build("test");

    return 0;
}
