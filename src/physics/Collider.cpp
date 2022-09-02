//
// Created by Jaraxus on 31/08/2022.
//

#include "../../include/physics/Collider.h"

namespace flash {

Collider::Collider(const Vect3d &position, Material material) :
m_position(position),
m_material(material)
{
}

const Material &Collider::getMaterial() const {
    return m_material;
}

const Vect3d &Collider::getPosition() const {
    return m_position;
}

}