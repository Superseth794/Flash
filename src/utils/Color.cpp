//
// Created by Jaraxus on 31/08/2022.
//

#include "../../include/utils/Color.h"

#include <cassert>
#include <cmath>

namespace flash {

Color::Color(double r, double g, double b, double a) noexcept :
r(r),
g(g),
b(b),
a(a)
{
}

Color Color::operator+(Color const& color) const {
    return Color(r + color.r, g + color.g, b + color.b, a + color.a);
}

Color Color::operator-(Color const& color) const {
    return Color(r - color.r, g - color.g, b - color.b, a - color.a);
}

Color Color::operator*(double t) const {
    return Color(r * t, g * t, b * t, a * t);
}

Color Color::operator/(double t) const {
    assert(t != 0.);
    return Color(r / t, g / t, b / t, a / t);
}

void Color::operator+=(Color const& color) {
    r += color.r;
    g += color.g;
    b += color.b;
    a += color.a;
}

void Color::operator-=(Color const& color) {
    r -= color.r;
    g -= color.g;
    b -= color.b;
    a -= color.a;
}

void Color::operator*=(double t) {
    r *= t;
    g *= t;
    b *= t;
    a *= t;
}

void Color::operator/=(double t) {
    r /= t;
    g /= t;
    b /= t;
    a /= t;
}

bool Color::operator==(Color const& color) const {
    return (this == &color) || (near(r, color.r) && near(g, color.g) && near(b, color.b) && near(a, color.a));
}

Color Color::combine(Color const& color) const {
    return Color(r * color.r, g * color.g, b * color.b, a * color.a);
}

Vect3i Color::toRGB() const {
    assert(0. <= r && r < 256);
    assert(0. <= r && g < 256);
    assert(0. <= r && b < 256);
    return Vect3i(
            static_cast<int>(std::round(255 * r)),
            static_cast<int>(std::round(255 * g)),
            static_cast<int>(std::round(255 * b)));
}

Color operator*(double t, Color const& color) {
    return color * t;
}

Color operator/(double t, Color const& color) {
    return color / t;
}

[[maybe_unused]] const Color Color::BLACK = Color(0, 0, 0);
[[maybe_unused]] const Color Color::BLUE = Color(0, 0, 1);
[[maybe_unused]] const Color Color::CYAN = Color(0, 1, 1);
[[maybe_unused]] const Color Color::GREEN = Color(0, 1, 0);
[[maybe_unused]] const Color Color::MAGENTA = Color(1, 0, 1);
[[maybe_unused]] const Color Color::ORANGE = Color(1, 0.5, 0);
[[maybe_unused]] const Color Color::RED = Color(1, 0, 0);
[[maybe_unused]] const Color Color::YELLOW = Color(1, 1, 0);
[[maybe_unused]] const Color Color::WHITE = Color(1, 1, 1);

}

namespace std {

ostream& operator<<(ostream& os, flash::Color const& color) {
    os << "(r: " << color.r << ", g: " << color.g << ", b: " << color.b << ')';
    return os;
}

}