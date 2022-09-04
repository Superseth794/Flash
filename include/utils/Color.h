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

    Color(double r, double g, double b, double a = 1) noexcept;

    Color operator+(Color const& color) const;

    Color operator-(Color const& color) const;

    Color operator*(double t) const;

    Color operator/(double t) const;

    void operator+=(Color const& color);

    void operator-=(Color const& color);

    void operator*=(double t);

    void operator/=(double t);

    bool operator==(Color const& color) const;

    Color combine(Color const& color) const;

    Vect3i toRGB() const;

    double r;
    double g;
    double b;
    double a;

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

Color operator*(double t, Color const& color);

Color operator/(double t, Color const& color);

}

namespace std {

ostream& operator<<(ostream& os, flash::Color const& color);

}

#endif //FLASH_COLOR_H
