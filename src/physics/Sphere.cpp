//
// Created by Jaraxus on 31/08/2022.
//

#include "../../include/physics/Sphere.hpp"

namespace flash {

Sphere::Sphere(float radius, const Vect3f &position, const Color &color) :
Collider(position, color),
m_radius(radius)
{
}

std::optional<Collision> Sphere::cast(const Ray &ray) const {
    auto oc = ray.origin - getPosition();
    auto a = ray.direction.dot(ray.direction);
    auto b = 2.0 * oc.dot(ray.direction);
    auto c = oc.dot(oc) - m_radius*m_radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant <= 0)
        return std::nullopt;

    auto unit_direction = ray.direction.normalize();
    float t = 0.5f*(unit_direction.y + 1.0f);
    auto col = Color(1.0, 1.0, 1.0) * (1.0f-t) + getColor() * t;
    return Collision {
        Vect3f (0, 0, 0),
        col
    };
}

}