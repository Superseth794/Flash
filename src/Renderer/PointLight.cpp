//
// Created by Jaraxus on 01/09/2022.
//

#include "../../include/Renderer/PointLight.hpp"

namespace flash {

PointLight::PointLight(Vect3d position, Color color, float intensity) :
m_color(color),
m_intensity(intensity),
m_position(position)
{
}

Color const &PointLight::getColor() const {
    return m_color;
}

float PointLight::getIntensity() const {
    return m_intensity;
}

Vect3d const &PointLight::getPosition() const {
    return m_position;
}

}