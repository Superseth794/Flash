//
// Created by Jaraxus on 01/09/2022.
//

#include <limits>

#include "../../include/Renderer/Scene.hpp"

namespace flash {

Scene::Scene(std::string name) :
m_camera(Vect3d::ZERO, 0, 0, 0),
m_name(std::move(name))
{
}

void Scene::addCollider(std::unique_ptr<Collider> &&collider) {
    m_colliders.emplace_back(std::forward<std::unique_ptr<Collider>>(collider));
}

Color Scene::cast(double x, double y) {
    assert(0. <= x && x <= 1.);
    assert(0. <= y && y <= 1.);

    std::optional<Collision> collision = std::nullopt;
    double closestDistance2 = std::numeric_limits<float>::infinity();

    auto cameraPosition = m_camera.getPosition();
    auto ray = m_camera.rayAt(x, y);

    for (auto& collider: m_colliders) {
        auto c = collider->cast(ray);
        if (c) {
            if (!collider->contactWith(c->position)) {
                collider->contactWith(c->position);
            }
            double distance2 = (c->position - cameraPosition).norm2();
            if (distance2 < closestDistance2) {
                collision = c;
                closestDistance2 = distance2;
            }
        }
    }

    if (!collision) {
        double gradient = std::fabs(x - 0.5) / 2.;
        return Color(gradient, gradient, 0.25 + 0.25 * gradient);
    }

    std::vector<PointLight const*> lights;

    for (auto& light: m_lights) {
        Ray rayToLight(collision->position, (light.getPosition() - collision->position).normalized());

        bool isHidden = false;
        for (auto& collider : m_colliders) {
            if (collider->hit(rayToLight)) {
                isHidden = true;
                break;
            }
        }

        if (!isHidden)
            lights.emplace_back(&light);
    }

    auto material = collision->material;
    auto rayHitResult = material->computeHitResult(*collision, HitContext{ray, lights});

    if (rayHitResult)
        return rayHitResult->color;

    return Color::BLACK;
}

void Scene::addLight(PointLight && light) {
    m_lights.emplace_back(light);
}

Camera &Scene::setCamera(Camera &&camera) {
    m_camera = camera;
    return m_camera;
}

}