//
// Created by Jaraxus on 30/08/2022.
//

#ifndef FLASH_PPMIMAGE_H
#define FLASH_PPMIMAGE_H

#include <functional>
#include <string>
#include <vector>

#include "../utils/Color.h"

namespace flash {

class PPMImage {
public:
    PPMImage(std::size_t width, std::size_t height);

    void build(std::string const &name);

    void fill(std::function<Color(float,float)> const& gradient);

    void setPixel(std::size_t x, std::size_t y, Color color);

private:
    std::size_t         m_height;
    std::vector<Color> m_image;
    std::size_t         m_width;
};

}

#endif //FLASH_PPMIMAGE_H