//
// Created by Jaraxus on 01/09/2022.
//

#ifndef FLASH_SCENE_HPP
#define FLASH_SCENE_HPP

#include <string>
#include <vector>

#include "../physics/Collider.h"

namespace flash {

class Scene {
public:
    Scene(std::string name);

    void addCollider(std::unique_ptr<Collider> && collider);

    Color cast(float dx, float dy);

private:
    Vect3f                                  m_camaraPosition;
    std::vector<std::unique_ptr<Collider>>  m_colliders;
    std::string                             m_name;
    float                                   m_fov; // angle
};

}

#endif //FLASH_SCENE_HPP
