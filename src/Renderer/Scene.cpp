//
// Created by Jaraxus on 01/09/2022.
//

#include <limits>

#include "../../include/Renderer/Scene.hpp"

namespace flash {

Scene::Scene(std::string name) :
m_name(name),
m_fov(0.785375f)
{
}

void Scene::addCollider(std::unique_ptr<Collider> &&collider) {
    m_colliders.emplace_back(std::forward<std::unique_ptr<Collider>>(collider));
}

Color Scene::cast(float dx, float dy) {
    Color finalColor = Color::BLACK;
    double closestDistance2 = std::numeric_limits<float>::infinity();
    Ray ray(m_camaraPosition + Vect3f(dx, 0, dy), Vect3f(0, 1, 0)); // move according to camera orientation

    for (auto& collider: m_colliders) {
        auto collision = collider->cast(ray);
        if (collision.has_value()) {
            double distance2 = (collision->position - m_camaraPosition).norm2();
            if (distance2 < closestDistance2) {
                finalColor = collision->color;
                closestDistance2 = distance2;
            }
        }
    }

    return finalColor;
}

}