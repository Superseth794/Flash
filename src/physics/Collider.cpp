//
// Created by Jaraxus on 31/08/2022.
//

#include "../../include/physics/Collider.h"

namespace flash {

Collider::Collider(const Vect3f &position, const Color &color) :
m_position(position),
m_color(color)
{
}

const Vect3f &Collider::getPosition() const {
    return m_position;
}

const Color &Collider::getColor() const {
    return m_color;
}

void Collider::setColor(const Color &color) {
    m_color = color;
}

void Collider::setPosition(const Vect3f &mPosition) {
    m_position = mPosition;
}

}