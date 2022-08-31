//
// Created by Jaraxus on 30/08/2022.
//

#ifndef FLASH_VECTOR3_H
#define FLASH_VECTOR3_H

namespace flash
{
    template <typename T>
    struct Vector3 {
        Vector3() = default;
        Vector3(T x, T y, T z);

        T x;
        T y;
        T z;
    };

    using Vect3i = Vector3<int>;
    using Vect3f = Vector3<float>;
}

#include "Vector3.inl"

#endif //FLASH_VECTOR3_H
