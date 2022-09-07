//
// Created by Jaraxus on 01/09/2022.
//

#ifndef FLASH_SCENE_HPP
#define FLASH_SCENE_HPP

#include <random>
#include <string>
#include <vector>

#include "../physics/Collider.h"
#include "PointLight.hpp"
#include "Camera.hpp"

namespace flash {

struct RandomSetup {
    std::mt19937                            rdm;
    std::uniform_real_distribution<double>  smallRealsDistrib;
};

class Scene {
public:
    Scene(std::string name, std::size_t raysPerCast);

    void addCollider(std::unique_ptr<Collider> && collider);

    void addLight(PointLight && light);

    Color cast(double x, double y, RandomSetup& setup) const;

    Camera& setCamera(Camera && camera); // TODO multi camera handling

private:
    Camera                                  m_camera;
    std::vector<std::unique_ptr<Collider>>  m_colliders;
    std::vector<PointLight>                 m_lights;
    std::string                             m_name;
    std::size_t                             m_raysPerCast;
};

}

#endif //FLASH_SCENE_HPP
