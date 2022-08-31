//
// Created by Jaraxus on 30/08/2022.
//

#ifndef FLASH_PPMIMAGE_H
#define FLASH_PPMIMAGE_H

#include <functional>
#include <string>
#include <vector>

#include "../utils/Vector3.h"

namespace flash {

class PPMImage {
public:
    PPMImage(std::size_t width, std::size_t height);

    void build(std::string const &name);

    void fill(std::function<Vect3f(float,float)> gradient);

    void setPixel(std::size_t x, std::size_t y, std::size_t z);

private:
    std::size_t         m_height;
    std::vector<Vect3f> m_image;
    std::size_t         m_width;
};

}

#endif //FLASH_PPMIMAGE_H