//
// Created by Jaraxus on 31/08/2022.
//

#include "../../include/physics/Sphere.hpp"
#include "../../include/utils/maths.hpp"

namespace flash {

Sphere::Sphere(float radius, const Vect3d &position, std::shared_ptr<Material> const& material) :
Collider(position, material),
m_radius(radius)
{
}

std::optional<Collision> Sphere::cast(const Ray &ray) const {
    assert(near(ray.direction.norm2(), 1.f));

    auto q = ray.origin - getPosition();
    auto a = static_cast<float>(ray.direction.norm2());
    double b = 2.f * ray.direction.dot(q);
    double c = static_cast<float>(q.norm2()) - m_radius*m_radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant <= 0)
        return std::nullopt;

    double sqrtDis = std::sqrt(discriminant);
    auto t1 = (-b + sqrtDis) / (2.f * a);

    if (t1 < 0.f)
        return std::nullopt;
    else if (near(t1, 0.f))
        return std::nullopt;

    auto x1 = t1 * ray.direction + ray.origin;
    auto t2 = (-b - sqrtDis) / (2.f * a);
    auto x2 = t2 * ray.direction + ray.origin;

    auto collisionPoint = x1;

    if ((t2 < 0.f))
            return std::nullopt;
    if (t2 > 0.f && ((x1 - ray.origin).norm2() > (x2 - ray.origin).norm2()))
        collisionPoint = x2;

    return std::make_optional(Collision{
            collisionPoint,
            (collisionPoint - getPosition()).normalized(),
            &getMaterial()
    });
}

bool Sphere::contactWith(const Vect3d &point) const {
    return near((point - getPosition()).norm2(), m_radius * m_radius);
}

bool Sphere::hit(Ray const& ray) const {
    assert(near(ray.direction.norm2(), 1.f));

    auto q = ray.origin - getPosition();
    auto a = static_cast<float>(ray.direction.norm2());
    double b = 2.f * ray.direction.dot(q);
    double c = static_cast<float>(q.norm2()) - m_radius*m_radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant <= 0)
        return false; // TODO check limit discriminant == 0

    double sqrtDis = std::sqrt(discriminant);
    auto t1 = (-b + sqrtDis) / (2.f * a);

    return (t1 > 0 && !near(t1, 0.));
}

}