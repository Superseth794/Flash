//
// Created by Jaraxus on 30/08/2022.
//

#include <iostream>

#include "../include/image/PPMImage.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    flash::PPMImage image(100, 100);
    image.fill([](float x, float y) {
        return flash::Vect3f(x, y, x * y);
    });
    image.build("test");

    return 0;
}
