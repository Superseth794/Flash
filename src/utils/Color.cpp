//
// Created by Jaraxus on 31/08/2022.
//

#include "../../include/utils/Color.h"

#include <cassert>
#include <cmath>

namespace flash {

Color::Color(float r, float g, float b, float a) :
r(r),
g(g),
b(b),
a(a)
{
}

std::ostream& Color::operator<<(std::ostream &stream) {
    stream << r << " " << g << " " << b << " " << a;
    return stream;
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

}
