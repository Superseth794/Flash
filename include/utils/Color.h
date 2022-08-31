//
// Created by Jaraxus on 31/08/2022.
//

#ifndef FLASH_COLOR_H
#define FLASH_COLOR_H

#include <ostream>
#include "Vectors.h"

namespace flash {

struct Color {
    Color() = default;

    Color(float r, float g, float b, float a = 1);

    Vect3i toRGB() const;

    float r;
    float g;
    float b;
    float a;
};

}

#endif //FLASH_COLOR_H
