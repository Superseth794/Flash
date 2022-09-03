//
// Created by Jaraxus on 03/09/2022.
//

#ifndef FLASH_CAMERA_HPP
#define FLASH_CAMERA_HPP

#include "../utils/Vectors.h"
#include "../physics/Ray.h"

namespace flash {

class Camera {
public:
    Camera(Vect3d position, double width, double height, double fov); // TODO add self rotation

    double getFov() const;

    double getHeight() const;

    const Vect3d &getPosition() const;

    double getWidth() const;

    Ray rayAt(double x, double y) const;

    void setFov(double mFov);

    void setPosition(const Vect3d &mPosition);

private:
    void computeDistanceToScreen();

    double  m_distanceToScreen;
    double  m_fov;
    double  m_height;
    Vect3d  m_position;
    double  m_width;
};

}

#endif //FLASH_CAMERA_HPP
