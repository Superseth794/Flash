//
// Created by Jaraxus on 31/08/2022.
//

#ifndef FLASH_COLLIDER_H
#define FLASH_COLLIDER_H

#include <optional>

#include "Ray.h"
#include "../utils/Color.h"
#include "../utils/Vectors.h"
#include "Material.hpp"

namespace flash {

struct Collision {
    Vect3d          position;
    Vect3d          normal;
    const Material* material;
};

class Collider {
public:
    Collider(Vect3d const& position, Material material);

    virtual ~Collider() = default;

    virtual std::optional<Collision> cast(Ray const& ray) const = 0;

    virtual bool contactWith(Vect3d const& point) const = 0;

    virtual bool hit(Ray const& ray) const = 0;

    const Material &getMaterial() const;

    const Vect3d &getPosition() const;

private:
    Vect3d      m_position;
    Material    m_material;
};

}

#endif //FLASH_COLLIDER_H
