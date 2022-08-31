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

    Color(float r, float g, float b, float a = 1) noexcept;

    Color operator+(Color const& color) const;

    Color operator*(float t) const;

    Color& operator+=(Color const& color);

    Color& operator*=(float t);

    Vect3i toRGB() const;

    float r;
    float g;
    float b;
    float a;

    static const Color BLACK;
    static const Color BLUE;
    static const Color CYAN;
    static const Color GREEN;
    static const Color MAGENTA;
    static const Color ORANGE;
    static const Color RED;
    static const Color YELLOW;
    static const Color WHITE;
};

}

#endif //FLASH_COLOR_H
