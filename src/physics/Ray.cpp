//
// Created by Jaraxus on 03/09/2022.
//

#include "../../include/physics/Ray.h"

namespace flash {

Ray::Ray(Vect3d origin, Vect3d direction) :
origin(origin),
direction(direction)
{
    assert(near(direction.norm(), 1.f));
}

}

namespace std {

ostream& operator<<(ostream& os, flash::Ray const& ray) {
    os << '[' << ray.origin << " -> " << ray.direction << ']';
    return os;
}

}