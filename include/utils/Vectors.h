//
// Created by Jaraxus on 30/08/2022.
//

#ifndef FLASH_VECTOR3_H
#define FLASH_VECTOR3_H

#include <ostream>

namespace flash
{
template <typename T>
struct Vector3 {
    Vector3() = default;

    Vector3(T x, T y, T z);

    Vector3<T> operator+(Vector3<T> const& vect) const;

    Vector3<T> operator-(Vector3<T> const& vect) const;

    void operator+=(Vector3<T> const& vect) const;

    void operator-=(Vector3<T> const& vect) const;

    T operator[](std::size_t i) const;

    Vector3<T> cross(Vector3<T> const& vect) const;

    T dot(Vector3<T> const& vect) const;

    double norm() const;

    double norm2() const;

    Vector3<T> nomalize() const;

    Vector3<T>& normalized();

    T x;
    T y;
    T z;
};

using Vect3i = Vector3<int>;
using Vect3f = Vector3<float>;

}

namespace std {

template<typename T>
ostream& operator<<(ostream& stream, flash::Vector3<T> const& vect);

}

#include "Vectors.inl"

#endif //FLASH_VECTOR3_H