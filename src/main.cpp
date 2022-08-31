//
// Created by Jaraxus on 30/08/2022.
//

#include <iostream>

#include "../include/image/PPMImage.h"

int main() {
    using namespace flash;

    PPMImage image(100, 100);
    image.fill([](float x, float y) {
        return Color(x, y, x * y);
    });
    image.build("test");

    Vect3f a(10, 15, 2), b(7, 7, 7);
    std::cout << "cross: " << a.cross(b) << std::endl;
    std::cout << "dot: " << a.dot(b) << std::endl;
    std::cout << "norm: " << b.norm() << std::endl;
    std::cout << "normalized: " << b.normalized() << std::endl;

    return 0;
}
