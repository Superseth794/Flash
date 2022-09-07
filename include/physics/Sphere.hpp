//
// Created by Jaraxus on 31/08/2022.
//

#ifndef FLASH_SPHERE_HPP
#define FLASH_SPHERE_HPP

#include "Collider.h"

namespace flash {

class Sphere : public Collider {
public:
    Sphere(float radius, Vect3d const& position, Material material);

    std::optional<Collision> cast(const Ray &ray) const override;

    bool contactWith(const Vect3d &point) const override;

    bool hit(Ray const& ray) const override;

private:
    float m_radius;
};

}

#endif //FLASH_SPHERE_HPP
