//
// Created by Jaraxus on 01/09/2022.
//

#ifndef FLASH_MATERIAL_HPP
#define FLASH_MATERIAL_HPP

#include "../utils/Color.h"

namespace flash {

struct Material {
    Color color;
    double specularReflection;
    double diffuseReflection;
    double ambientReflection;
    double shininess;
};

}

#endif //FLASH_MATERIAL_HPP
