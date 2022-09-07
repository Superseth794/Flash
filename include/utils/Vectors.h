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
    constexpr Vector3() = default;

    constexpr Vector3(T x, T y, T z);

    Vector3<T> operator+(Vector3<T> const& vect) const; // TODO param U

    Vector3<T> operator-(Vector3<T> const& vect) const;

    Vector3<T> operator*(T t) const;

    Vector3<T> operator/(T t) const;

    void operator+=(Vector3<T> const& vect) const;

    void operator-=(Vector3<T> const& vect) const;

    void operator*=(T t) const;

    void operator/=(T t) const;

    T operator[](std::size_t i) const;

    Vector3<T> cross(Vector3<T> const& vect) const;

    T dot(Vector3<T> const& vect) const;

    bool near(Vector3<T> const& vect) const;

    double norm() const;

    double norm2() const;

    Vector3<T> normalize() const;

    Vector3<T>& normalized();

    T x;
    T y;
    T z;

    static inline Vector3<T> ZERO   = Vector3(0, 0, 0);
    static inline Vector3<T> BACK   = Vector3(0, -1, 0);
    static inline Vector3<T> DOWN   = Vector3(0, 0, -1);
    static inline Vector3<T> FRONT  = Vector3(0, 1, 0);
    static inline Vector3<T> LEFT   = Vector3(-1, 0, 0);
    static inline Vector3<T> UP     = Vector3(0, 0, 1);
    static inline Vector3<T> RIGHT  = Vector3(1, 0, 0);
};

template <typename T>
Vector3<T> operator*(T t, Vector3<T> vect);

template <typename T>
Vector3<T> operator/(T t, Vector3<T> vect);

template <typename T>
Vector3<T> operator-(Vector3<T> vect);

using Vect3i = Vector3<int>;
using Vect3d = Vector3<double>;

}

namespace std {

template<typename T>
ostream& operator<<(ostream& stream, flash::Vector3<T> const& vect);

}

#include "Vectors.inl"

#endif //FLASH_VECTOR3_H
