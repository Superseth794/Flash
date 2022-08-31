//
// Created by Jaraxus on 31/08/2022.
//

#include "../../include/utils/Color.h"

#include <cassert>
#include <cmath>

namespace flash {

Color::Color(float r, float g, float b, float a) noexcept :
r(r),
g(g),
b(b),
a(a)
{
}

Color Color::operator+(Color const& color) const {
    return Color(r + color.r, g + color.g, b + color.b, a + color.a);
}

Color Color::operator*(float t) const {
    return Color(r * t, g * t, b * t, a * t);
}

Color& Color::operator*=(float t) {
    r *= t;
    g *= t;
    b *= t;
    a *= t;
}

Color& Color::operator+=(Color const& color) {
    r += color.r;
    g += color.g;
    b += color.b;
    a += color.a;
}

Vect3i Color::toRGB() const {
    assert(0.f <= r && r <= 1.f);
    assert(0.f <= g && g <= 1.f);
    assert(0.f <= b && b <= 1.f);
    return Vect3i(
            static_cast<int>(std::round(255 * r)),
            static_cast<int>(std::round(255 * g)),
            static_cast<int>(std::round(255 * b)));
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
