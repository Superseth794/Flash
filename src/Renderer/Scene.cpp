//
// Created by Jaraxus on 01/09/2022.
//

#include <limits>

#include "../../include/Renderer/Scene.hpp"

namespace flash {

Scene::Scene(std::string name) :
m_camaraPosition(),
m_name(std::move(name)),
m_fov(0.785375f)
{
}

void Scene::addCollider(std::unique_ptr<Collider> &&collider) {
    m_colliders.emplace_back(std::forward<std::unique_ptr<Collider>>(collider));
}

Color Scene::cast(float dx, float dy) {
    std::optional<Collision> collision = std::nullopt;
    double closestDistance2 = std::numeric_limits<float>::infinity();
    Ray ray(m_camaraPosition + Vect3d(dx, 0, dy), Vect3d(0, 1, 0)); // move according to camera orientation

    for (auto& collider: m_colliders) {
        auto c = collider->cast(ray);
        if (c) {
            double distance2 = (c->position - m_camaraPosition).norm2();
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
                color += material->specularReflection * std::pow(specularCoef, material->shininess) * material->color.combine(light.getColor());
        }
    }

    return color;
}

void Scene::addLight(PointLight && light) {
    m_lights.emplace_back(light);
}

}