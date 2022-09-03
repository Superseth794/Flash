//
// Created by Jaraxus on 01/09/2022.
//

#ifndef FLASH_SCENE_HPP
#define FLASH_SCENE_HPP

#include <string>
#include <vector>

#include "../physics/Collider.h"
#include "PointLight.hpp"
#include "Camera.hpp"

namespace flash {

class Scene {
public:
    Scene(std::string name);

    void addCollider(std::unique_ptr<Collider> && collider);

    void addLight(PointLight && light);

    Color cast(double x, double y);

    Camera& setCamera(Camera && camera); // TODO mutli camera handling

private:
    Camera                                  m_camera;
    std::vector<std::unique_ptr<Collider>>  m_colliders;
    std::vector<PointLight>                 m_lights;
    std::string                             m_name;
};

}

#endif //FLASH_SCENE_HPP
