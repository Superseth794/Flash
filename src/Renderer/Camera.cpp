//
// Created by Jaraxus on 03/09/2022.
//

#include "../../include/Renderer/Camera.hpp"

namespace flash {

Camera::Camera(Vect3d position, double width, double height, double fov) :
m_distanceToScreen(),
m_fov(fov),
m_height(height),
m_position(position),
m_width(width)
{
    computeDistanceToScreen();
}

double Camera::getFov() const {
    return m_fov;
}

double Camera::getHeight() const {
    return m_height;
}

const Vect3d &Camera::getPosition() const {
    return m_position;
}

double Camera::getWidth() const {
    return m_width;
}

Ray Camera::rayAt(double x, double y) const {
    assert(0. <= x && x <= 1.);
    assert(0. <= y && y <= 1.);
    Vect3d pointOnScreen = Vect3d(
            m_position.x + (x - 0.5) * m_width,
            m_position.y + m_distanceToScreen,
            m_position.z + (y - 0.5) * m_height);
    return Ray(m_position, (pointOnScreen - m_position).normalized());
}

void Camera::setFov(double mFov) {
    m_fov = mFov;
}

void Camera::setPosition(const Vect3d &mPosition) {
    m_position = mPosition;
}

void Camera::computeDistanceToScreen() {
    assert(0 <= m_fov && m_fov <= M_PI);
    auto t = std::tan(m_fov / 2.);
    m_distanceToScreen = m_width / (2. * t);
}

}