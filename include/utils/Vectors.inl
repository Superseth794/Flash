//
// Created by Jaraxus on 30/08/2022.
//

#include "Vectors.h"
#include "maths.hpp"

#include <cmath>

namespace flash {

template<typename T>
Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

template<typename T>
Vector3 <T> Vector3<T>::operator+(const Vector3 <T> &vect) const {
    return Vector3<T>(x + vect.x, y + vect.y, z + vect.z);
}

template<typename T>
Vector3 <T> Vector3<T>::operator-(const Vector3 <T> &vect) const {
    return Vector3<T>(x - vect.x, y - vect.y, z - vect.z);
}

template<typename T>
Vector3 <T> Vector3<T>::operator*(T t) const {
    return Vector3<T>(x * t, y * t, z * t);
}

template<typename T>
Vector3 <T> Vector3<T>::operator/(T t) const {
    assert(t != 0);
    return Vector3<T>(x / t, y / t, z / t);
}

template<typename T>
void Vector3<T>::operator+=(const Vector3 <T> &vect) const {
    x += vect.x;
    y += vect.y;
    z += vect.z;
}

template<typename T>
void Vector3<T>::operator-=(const Vector3 <T> &vect) const {
    x -= vect.x;
    y -= vect.y;
    z -= vect.z;
}

template<typename T>
void Vector3<T>::operator*=(T t) const {
    x *= t;
    y *= t;
    z *= t;
}

template<typename T>
void Vector3<T>::operator/=(T t) const {
    assert(t != 0);
    x /= t;
    y /= t;
    z /= t;
}

template<typename T>
T Vector3<T>::operator[](std::size_t i) const {
    assert(0 <= i && i <= 3);
    return (i == 0 ? x : (i == 1 ? x : y));
}

template<typename T>
Vector3 <T> Vector3<T>::cross(const Vector3 <T> &vect) const {
    return Vector3<T>(y * vect.z - z * vect.y, z * vect.x - x * vect.z, x * vect.y - y * vect.x);
}

template<typename T>
T Vector3<T>::dot(const Vector3 <T> &vect) const {
    return x * vect.x + y * vect.y + z * vect.z;
}

template<typename T>
bool Vector3<T>::near(Vector3<T> const& vect) const {
    return flash::near(x, vect.x) && flash::near(y, vect.y) && flash::near(z, vect.z);
}

template<typename T>
double Vector3<T>::norm() const {
    return std::sqrt(norm2());
}

template<typename T>
double Vector3<T>::norm2() const {
    return x * x + y * y + z * z;
}

template<typename T>
Vector3 <T> Vector3<T>::normalize() const {
    double norm = this->norm();
    assert(norm != 0.);
    return Vector3<T>(x / norm, y / norm, z / norm);
}

template<typename T>
Vector3 <T> &Vector3<T>::normalized() { // TODO fix &
    double norm = this->norm();
    assert(norm != 0.);
    x /= norm;
    y /= norm;
    z /= norm;
    return *this;
}

template <typename T>
Vector3<T> operator*(T t, Vector3<T> vect) {
    return vect * t;
}

}

namespace std {

template<typename T>
ostream& operator<<(ostream& stream, flash::Vector3<T> const& vect) {
    stream << '(' << vect.x << ',' << vect.y << ',' << vect.z << ')';
    return stream;
}

}