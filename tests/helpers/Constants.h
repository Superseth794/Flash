//
// Created by Jaraxus on 05/09/2022.
//

#ifndef FLASH_CONSTANTS_H
#define FLASH_CONSTANTS_H

#include "utils/Vectors.h"

namespace flash::test {

static constexpr double LOWER = -10.;

static constexpr Vect3d LOWER_VECTOR(-10., -10., -10.);

static constexpr double UPPER = -10.;

static constexpr Vect3d UPPER_VECTOR(10., 10., 10.);

static constexpr int ITERATION_COUNT = 10;

static constexpr int ITERATION_COUNT_LOW = 5;

}

#endif //FLASH_CONSTANTS_H
