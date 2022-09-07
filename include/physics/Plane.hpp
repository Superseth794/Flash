//
// Created by Jaraxus on 03/09/2022.
//

#ifndef FLASH_PLANE_HPP
#define FLASH_PLANE_HPP

#include "Collider.h"

namespace flash {

class Plane : public Collider {
public:
    Plane(Vect3d origin, Vect3d u, Vect3d v, Material material);

    std::optional<Collision> cast(const Ray &ray) const override;

    bool contactWith(const Vect3d &point) const override;

    bool hit(const Ray &ray) const override;

private:
    Vect3d m_u;
    Vect3d m_v;
    Vect3d m_normal;
};

}

#endif //FLASH_PLANE_HPP
