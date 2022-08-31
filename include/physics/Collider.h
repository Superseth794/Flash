//
// Created by Jaraxus on 31/08/2022.
//

#ifndef FLASH_COLLIDER_H
#define FLASH_COLLIDER_H

#include <optional>

#include "Ray.h"
#include "../utils/Color.h"
#include "../utils/Vectors.h"

namespace flash {

struct Collision {
    Vect3f  position;
    Color   color;
};

class Collider {
public:
    Collider(Vect3f const& position, Color const& color);

    virtual std::optional<Collision> cast(Ray const& ray) const = 0;

    const Vect3f &getPosition() const;

    const Color &getColor() const;

    void setColor(const Color &color);

    void setPosition(const Vect3f &mPosition);

private:
    Vect3f m_position;
    Color m_color;
};

}

#endif //FLASH_COLLIDER_H
