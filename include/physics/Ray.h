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

    Ray(Vect3d origin, Vect3d direction) : origin(origin), direction(direction) {
        auto d = direction.norm();
        if (!near(d, 1.f))
            float x = near(d, 1.f);
        assert(near(d, 1.f));
    }

    Vect3d origin;
    Vect3d direction;
};

}

#endif //FLASH_RAY_H
