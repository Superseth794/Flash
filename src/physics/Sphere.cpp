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
    assert(ray.direction.norm2() == 1);

    auto q = ray.origin - getPosition();
    auto a = static_cast<float>(ray.direction.norm2());
    float b = 2.f * ray.direction.dot(q);
    float c = static_cast<float>(q.norm2()) - m_radius*m_radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant <= 0)
        return std::nullopt;

    float sqrtDis = std::sqrt(discriminant);
    auto t1 = (-b + sqrtDis);

    if (t1 < 0.f)
        return std::nullopt;

    auto x1 = t1 / (2.f * a) * ray.direction + ray.origin;
    auto t2 = (-b - sqrtDis);
    auto x2 = t2 / (2.f * a) * ray.direction + ray.origin;

    auto collisionPoint = x1;
    if (t2 > 0.f && ((x1 - ray.origin).norm2() > (x2 - ray.origin).norm2()))
        collisionPoint = x2;

    return std::make_optional(Collision{
            collisionPoint,
            getColor()
    });
}

}