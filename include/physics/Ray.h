//
// Created by Jaraxus on 31/08/2022.
//

#ifndef FLASH_RAY_H
#define FLASH_RAY_H

#include "../utils/Vectors.h"

namespace flash {

struct Ray {
    Ray() = default;

    Ray(Vect3f origin, Vect3f direction) : origin(origin), direction(direction) {}

    Vect3f origin;
    Vect3f direction;
};

}

#endif //FLASH_RAY_H
