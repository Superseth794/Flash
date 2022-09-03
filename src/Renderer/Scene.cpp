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
            double distance2 = (c->position - cameraPosition).norm2();
            if (distance2 < closestDistance2) {
                collision = c;
                closestDistance2 = distance2;
            }
        }
    }

    if (!collision)
        return Color::BLACK;

    auto material = collision->material;

    Color color(0, 0, 0);

    for (auto& light: m_lights) {
//        auto lightProjection = (light.getPosition() - ray.origin).dot(ray.direction) * ray.direction + ray.origin;
//        auto distanceToProjection = static_cast<float>((lightProjection - light.getPosition()).norm2());
//        if (distanceToProjection <= 8.f) {
//            color = Color::YELLOW * (1.f - distanceToProjection / 8.f);
//            break;
//        }

        Ray rayToLight(collision->position, (light.getPosition() - collision->position).normalized());

        bool isHidden = false;
        for (auto& collider : m_colliders) {
            if (collider->hit(rayToLight)) {
                isHidden = true;
                break;
            }
        }

        if (!isHidden) {
            // TODO add other Phong components
            double diffusionCoef = rayToLight.direction.dot(collision->normal);
            if (diffusionCoef > 0.)
                color += material->diffuseReflection * diffusionCoef * material->color.combine(light.getColor());

            auto R = 2 * rayToLight.direction.dot(collision->normal) * collision->normal - rayToLight.direction;
            double specularCoef = R.dot(-ray.direction);
            if (specularCoef > 0.)
//                color = Color(specularCoef, specularCoef, specularCoef);
                color += material->specularReflection * std::pow(specularCoef, material->shininess) * light.getColor() * 1;
        }
    }

    return color;
}

void Scene::addLight(PointLight && light) {
    m_lights.emplace_back(light);
}

Camera &Scene::setCamera(Camera &&camera) {
    m_camera = camera;
    return m_camera;
}

}