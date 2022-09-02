//
// Created by Jaraxus on 30/08/2022.
//

#include "../../include/image/PPMImage.h"

#include <cmath>
#include <fstream>

namespace flash {

PPMImage::PPMImage(std::size_t width, std::size_t height) :
m_height(height),
m_image(width * height),
m_width(width)
{
}

void PPMImage::build(const std::string &name) {
    double maxColor = -1;
    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j) {
            Color color = m_image[i * m_width + j];
            maxColor = std::max(maxColor, color.r);
            maxColor = std::max(maxColor, color.g);
            maxColor = std::max(maxColor, color.b);
        }
    }

    std::ofstream out(name + ".ppm");
    out << "P3\n" << m_width << " " << m_height << "\n255\n\n";
    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j) {
            auto color = (m_image[i * m_width + j] / maxColor).toRGB();
            out << color.x << " " << color.y << " " << color.z << "\n";
        }
    }
    out.close();
}

void PPMImage::fill(std::function<Color(float, float)> const& gradient) {
    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j) {
            m_image[i * m_width + j] = gradient(j / static_cast<float>(m_width), i / static_cast<float>(m_height));
        }
    }
}

void PPMImage::setPixel(std::size_t x, std::size_t y, Color color) {
    assert(0 <= x && x <= m_width);
    assert(0 <= y && y <= m_height);
    m_image[(m_height - y - 1) * m_width + x] = color;
}

}