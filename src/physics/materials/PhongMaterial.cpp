//
// Created by Jaraxus on 07/09/2022.
//

#include "../../../include/physics/materials/PhongMaterial.h"

namespace flash {

PhongMaterial::PhongMaterial(const Color &color, double specularReflection, double diffuseReflection,
                             double ambientReflection, double shininess) : m_color(color),
                                                                           m_specularReflection(specularReflection),
                                                                           m_diffuseReflection(diffuseReflection),
                                                                           m_ambientReflection(ambientReflection),
                                                                           m_shininess(shininess)
                                                                           {}

std::optional<RayHitResult> PhongMaterial::computeHitResult(const Collision &collision, HitContext context) const {
    auto const& ray = context.incomingRay;
    Color color(0, 0, 0);

    for (auto const& light : context.lights) {
        auto rayToLight = (light->getPosition() - collision.position).normalized();
        double diffusionCoef = rayToLight.dot(collision.normal);
        if (diffusionCoef > 0.)
            color += m_diffuseReflection * diffusionCoef * m_color.combine(light->getColor()) * light->getIntensity();

        auto R = 2 * rayToLight.dot(collision.normal) * collision.normal - rayToLight;
        double specularCoef = R.dot(-ray.direction);
        if (specularCoef > 0.)
            color += m_specularReflection * std::pow(specularCoef, m_shininess) * light->getColor() * light->getIntensity();
    }

    auto result = RayHitResult{
        color
    };
    return std::make_optional<RayHitResult>(result);
}

}