//
// Created by Jaraxus on 01/09/2022.
//

#ifndef FLASH_MATERIAL_HPP
#define FLASH_MATERIAL_HPP

#include "../utils/Color.h"

namespace flash {

struct Material {
    Color color;
    float specularReflection;
    float diffuseReflection;
    float ambientReflection;
};

}

#endif //FLASH_MATERIAL_HPP
