//
// Created by Jaraxus on 01/09/2022.
//

#ifndef FLASH_MATERIAL_HPP
#define FLASH_MATERIAL_HPP

#include <optional>
#include <vector>

#include "../Collider.h"

#include "../../utils/Color.h"
#include "../../Renderer/PointLight.hpp"

namespace flash {

struct HitContext {
    const Ray&                              incomingRay;
    const std::vector<const PointLight*>&   lights;
};

struct RayHitResult {
    Color color;
};

class Collision;

class Material {
public:
    virtual std::optional<RayHitResult> computeHitResult(Collision const& collision, HitContext context) const = 0;
};

}

#endif //FLASH_MATERIAL_HPP
