//
// Created by Jaraxus on 07/09/2022.
//

#ifndef FLASH_PHONGMATERIAL_H
#define FLASH_PHONGMATERIAL_H

#include "Material.hpp"

namespace flash {

class PhongMaterial : public Material {
public:
    PhongMaterial(const Color &color, double specularReflection, double diffuseReflection, double ambientReflection,
                  double shininess);

    std::optional<RayHitResult> computeHitResult(const Collision &collision, HitContext context) const override;

private:
    Color   m_color;
    double  m_specularReflection;
    double  m_diffuseReflection;
    double  m_ambientReflection;
    double  m_shininess;
};

}

#endif //FLASH_PHONGMATERIAL_H
