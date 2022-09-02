//
// Created by Jaraxus on 01/09/2022.
//

#ifndef FLASH_POINTLIGHT_HPP
#define FLASH_POINTLIGHT_HPP

#include "../utils/Color.h"

namespace flash {

class PointLight {
public:
    PointLight(Vect3d position, Color color, float intensity);

    Color const&  getColor() const;

    Vect3d const& getPosition() const;

private:
    Color   m_color;
    float   m_intensity;
    Vect3d  m_position;
};

}

#endif //FLASH_POINTLIGHT_HPP
