//
// Created by Jaraxus on 03/09/2022.
//

#include "../../include/physics/Ray.h"

namespace flash {

Ray::Ray(Vect3d origin, Vect3d direction) :
origin(origin),
direction(direction)
{
    assert(near(direction.norm(), 1.));
}

Vect3d Ray::at(double t) const {
    assert(0. <= t);
    return origin + direction * t;
}

bool Ray::contactWith(const Vect3d &point) const {
    auto delta = origin - point;
    return near(delta.x / direction.x, delta.y / direction.y, delta.z / direction.z);
}

}

namespace std {

ostream& operator<<(ostream& os, flash::Ray const& ray) {
    os << '[' << ray.origin << " -> " << ray.direction << ']';
    return os;
}

}