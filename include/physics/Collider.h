//
// Created by Jaraxus on 31/08/2022.
//

#ifndef FLASH_COLLIDER_H
#define FLASH_COLLIDER_H

#include <memory>
#include <optional>

#include "Ray.h"
#include "../utils/Color.h"
#include "../utils/Vectors.h"
#include "materials/Material.hpp"

namespace flash {

class Material;

struct Collision {
    Vect3d          position;
    Vect3d          normal;
    const Material* material;
};

class Collider {
public:
    Collider(Vect3d const& position, std::shared_ptr<Material> const& material);

    virtual ~Collider() = default;

    virtual std::optional<Collision> cast(Ray const& ray) const = 0;

    virtual bool contactWith(Vect3d const& point) const = 0;

    virtual bool hit(Ray const& ray) const = 0;

    const Material &getMaterial() const;

    const Vect3d &getPosition() const;

private:
    Vect3d                      m_position;
    std::shared_ptr<Material>   m_material;
};

}

#endif //FLASH_COLLIDER_H
