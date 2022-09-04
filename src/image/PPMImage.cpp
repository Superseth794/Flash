//
// Created by Jaraxus on 30/08/2022.
//

#include "../../include/image/PPMImage.h"

#include <cmath>
#include <fstream>
#include <iostream>

namespace flash {

PPMImage::PPMImage(std::size_t width, std::size_t height) :
m_height(height),
m_image(width * height),
m_width(width)
{
}

Color PPMImage::computeExposure() const {
    const std::size_t accumulationSize = 16;
    double exposure = -1.f;
    double accumulationFactor = std::min(m_width, m_height) / static_cast<double>(accumulationSize);
    Color mediumPoint(0, 0, 0);
    double mediumPointWeight = accumulationSize * accumulationSize;

    for (std::size_t y = 0; y < accumulationSize; ++y) {
        for (std::size_t x = 0; x < accumulationSize; ++x) {
            auto i = static_cast<std::size_t>(std::round(y * accumulationFactor * m_width + x * accumulationFactor));
            Color color = m_image[i];
            mediumPoint += Color(color.r * color.r, color.g * color.g, color.b * color.b);
        }
    }

    return Color(std::sqrt(mediumPoint.r), std::sqrt(mediumPoint.g), std::sqrt(mediumPoint.b));
}

void PPMImage::build(const std::string &name) {
    double sum = 0.;
    double aSum = 0;
    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j) {
            sum += m_image[i * m_width + j].r * m_image[i * m_width + j].r;
            sum += m_image[i * m_width + j].g * m_image[i * m_width + j].g;
            sum += m_image[i * m_width + j].b * m_image[i * m_width + j].b;
            aSum += m_image[i * m_width + j].r;
            aSum += m_image[i * m_width + j].g;
            aSum += m_image[i * m_width + j].b;
        }
    }
    aSum /= double(m_height * m_width * 3);
    std::cout << "variance: " << 1. / double(m_height * m_width * 3) * sum - aSum * aSum << std::endl;

    auto exposure = computeExposure();
    std::cout << "Exposure: " << exposure << std::endl;

    double maxIntensity = 0;
    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j) {
            Color color = m_image[i * m_width + j];
            maxIntensity = std::max(maxIntensity, 1. - std::exp(-color.r * exposure.r));
            maxIntensity = std::max(maxIntensity, 1. - std::exp(-color.g * exposure.g));
            maxIntensity = std::max(maxIntensity, 1. - std::exp(-color.b * exposure.b));
        }
    }

    std::cout << "max: " << maxIntensity << std::endl;


    std::ofstream out(name + ".ppm");
    out << "P3\n" << m_width << " " << m_height << "\n255\n\n";
    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j) {
            auto color = Vect3i::ZERO;
            if (maxIntensity > 0.) {
                auto initColor = m_image[i * m_width + j];
                if (m_height - i < 10)
                    std::cout << initColor << '\n';
                color = (Color(
                    1. - std::exp(-initColor.r * exposure.r),
                    1. - std::exp(-initColor.g * exposure.g),
                    1. - std::exp(-initColor.b * exposure.b)
                ) / maxIntensity).toRGB();
            }
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