//
// Created by Jaraxus on 30/08/2022.
//

#include <iostream>

#include "../include/image/PPMImage.h"
#include "../include/physics/Sphere.hpp"

int main() {
    using namespace flash;

    constexpr std::size_t width = 1000, height = 1000;

//    PPMImage image(100, 100);
//    image.fill([](float x, float y) {
//        return Color(x, y, x * y);
//    });
//    image.build("test");

    Sphere sphere(300, {500, 500, 0}, Color::RED);

    PPMImage image2(width, height);
    for (std::size_t y = 0; y < height; ++y) {
        for (std::size_t x = 0; x < width; ++x) {
            auto ray = Ray(Vect3f(x, y, -10), Vect3f(0, 0, 1));
            auto collision = sphere.cast(ray);
            if (collision.has_value())
                image2.setPixel(x, y, collision->color);
            else
                image2.setPixel(x, y, Color::BLACK);
        }
    }
    image2.build("test2");

    return 0;
}
