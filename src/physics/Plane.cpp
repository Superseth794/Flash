//
// Created by Jaraxus on 03/09/2022.
//

#include "../../include/physics/Plane.hpp"

namespace flash {

Plane::Plane(Vect3d origin, Vect3d u, Vect3d v, Material material) :
Collider(origin, material),
m_normal(),
m_u(u),
m_v(v)
{
    assert(near(u.norm2(), 1.)); // TODO add isUnitary function
    assert(near(u.norm2(), 1.));
    m_normal = m_u.cross(m_v);
}

std::optional<Collision> Plane::cast(const Ray &ray) const {
    auto r = -ray.direction;
    double matrixDet =
            m_u.x * m_v.y * r.z + m_v.x * r.y * m_u.z +
            r.x * m_u.y * m_v.z - m_u.z * m_v.y * r.x -
            m_v.z * r.y * m_v.x - r.z * m_u.y * m_v.x;

    if (near(matrixDet, 0.))
        return std::nullopt;

    auto b = ray.origin - getPosition();

    double k = (m_u.y * m_u.z - m_v.y * m_u.z) * b.x + (m_v.x * m_u.z - m_u.x * m_u.z) * b.y + (m_u.x * m_v.y - m_v.x * m_u.y) * b.z;

    if (k < 0.)
        return std::nullopt;

    double s = (m_v.y * r.z - r.y * m_u.z) * b.x + (r.x * m_u.z - m_v.x * r.z) * b.y + (m_v.x * r.y - r.x * m_v.y) * b.z;
    double t = (r.y * m_u.z - m_u.y * r.z) * b.x + (m_u.x * r.z - r.x * m_u.z) * b.y + (r.x * m_u.y - m_u.x * r.y) * b.z;

    return std::make_optional(Collision{
            Vect3d(s, t, k) / matrixDet,
            m_normal,
            &getMaterial()
    });
}

bool Plane::hit(const Ray &ray) const {
    auto r = -ray.direction;
    double matrixDet =
            m_u.x * m_v.y * r.z + m_v.x * r.y * m_u.z +
            r.x * m_u.y * m_v.z - m_u.z * m_v.y * r.x -
            m_v.z * r.y * m_v.x - r.z * m_u.y * m_v.x;

    if (near(matrixDet, 0.))
        return false;

    auto b = ray.origin - getPosition();

    double k = (m_u.y * m_u.z - m_v.y * m_u.z) * b.x + (m_v.x * m_u.z - m_u.x * m_u.z) * b.y + (m_u.x * m_v.y - m_v.x * m_u.y) * b.z;

    return k * matrixDet > 0; // sign is the same as k / matrixDet
}

}