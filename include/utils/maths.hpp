//
// Created by Jaraxus on 01/09/2022.
//

#ifndef FLASH_MATHS_HPP
#define FLASH_MATHS_HPP

#include <cmath>

#define M_EPSYLON 1e-6

namespace flash {

inline bool near(double x1, double x2) {
    return std::fabs(x2 - x1) < M_EPSYLON;
}

}

#endif //FLASH_MATHS_HPP
