//
// Created by Jaraxus on 30/08/2022.
//

#include "../../include/image/PPMImage.h"

#include <cmath>
#include <fstream>
#include <stdio.h>

namespace flash {

PPMImage::PPMImage(std::size_t width, std::size_t height) :
m_height(height),
m_image(width * height),
m_width(width)
{
}

void PPMImage::build(const std::string &name) {
    std::ofstream out(name + ".ppm");
    out << "P3\n" << m_height << " " << m_width << "\n255\n\n";
    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j) {
            auto color = m_image[i * m_width + j];
            out << static_cast<int>(std::round(255 * color.x)) << " "
                << static_cast<int>(std::round(255 * color.y)) << " "
                << static_cast<int>(std::round(255 * color.z)) << "\n";
        }
    }
    out.close();
}

void PPMImage::fill(std::function<Vect3f(float, float)> gradient) {
    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j) {
            m_image[i * m_width + j] = gradient(j / static_cast<float>(m_width), i / static_cast<float>(m_height));
        }
    }
}

void PPMImage::setPixel(std::size_t x, std::size_t y, std::size_t z) {

}

}