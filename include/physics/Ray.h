//
// Created by Jaraxus on 31/08/2022.
//

#ifndef FLASH_RAY_H
#define FLASH_RAY_H

#include <cassert>

#include "../utils/Vectors.h"
#include "../utils/maths.hpp"

namespace flash {

struct Ray {
    Ray() = default;

    Ray(Vect3d origin, Vect3d direction);

    Vect3d at(double t) const;

    bool contactWith(const Vect3d &point) const;

    Vect3d origin;
    Vect3d direction;
};

}

namespace std {

std::ostream& operator<<(std::ostream& stream, flash::Ray const& ray);

}

#endif //FLASH_RAY_H
