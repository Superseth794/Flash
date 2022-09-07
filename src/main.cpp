//
// Created by Jaraxus on 30/08/2022.
//

#include <future>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>
#include <vector>

#include "../include/image/PPMImage.h"
#include "../include/physics/Sphere.hpp"
#include "../include/Renderer/Scene.hpp"
#include "../include/physics/Plane.hpp"
#include "../include/physics/materials/PhongMaterial.h"

void computeImage(flash::PPMImage& image, flash::Scene const& scene, bool showProgress) {
    using namespace flash;
    std::size_t width = image.getWidth();
    std::size_t height = image.getHeight();

    unsigned int totPixels = width * height;
    unsigned int pixelsDone = 0;
    unsigned int lastProgress = -1;

    RandomSetup rdmSetup {
        std::mt19937(std::hash<std::thread::id>()(std::this_thread::get_id())),
        std::uniform_real_distribution(0., 1.)
    };

    for (std::size_t y = 0; y < height; ++y) {
        for (std::size_t x = 0; x < width; ++x) {
            image.setPixel(x, y, scene.cast(x / static_cast<double>(width), y / static_cast<double>(height), rdmSetup));
            if (showProgress) {
                ++pixelsDone;
                int progress = static_cast<int>(static_cast<double>(pixelsDone) / totPixels * 100);
                if (progress % 5 == 0 && progress != lastProgress) {
                    std::cout << "progress " << progress << "%\n";
                    lastProgress = progress;
                }
            }
        }
    }
}

flash::PPMImage computeImageMultiThreaded(std::size_t width, std::size_t height, flash::Scene const& scene) {
    using namespace flash;

    std::size_t nbThreads = std::thread::hardware_concurrency();
    std::cout << "Number of threads used: " << nbThreads << std::endl;

    std::vector<std::thread> threads;
    std::vector<PPMImage> images;
    images.reserve(nbThreads);

    for (std::size_t i = 0; i < nbThreads; ++i) {
        images.emplace_back(width, height);
        threads.emplace_back(computeImage, std::ref(images[i]), std::ref(scene), (i == 0));
    }

    for (auto& thread : threads)
        thread.join();

    PPMImage final(width, height);
    for (auto& image : images)
        for (std::size_t y = 0; y < height; ++y)
            for (std::size_t x = 0; x < width; ++x)
                final.setPixel(x, y, final.getPixel(x, y) + image.getPixel(x, y));

    for (std::size_t y = 0; y < height; ++y)
        for (std::size_t x = 0; x < width; ++x)
            final.setPixel(x, y, final.getPixel(x, y) / static_cast<double>(nbThreads));

    return final;
}

int main() {
    using namespace flash;

    constexpr std::size_t width = 800, height = 450;
    const double fov = 90;

    Scene scene("test", 10);

    auto& camera = scene.setCamera(Camera(Vect3d(0, 0, 30), width, height, M_PI / 180. * fov));

    auto material0 = std::make_shared<PhongMaterial>(Color::WHITE, 1., 1., 0., 1);
    auto material1 = std::make_shared<PhongMaterial>(Color::GREEN, 1., 1., 0., 1);
    auto material2 = std::make_shared<PhongMaterial>(Color::RED, 1., 1., 0., 1);

    scene.addCollider(std::make_unique<Plane>(Vect3d(0, 0, -30), Vect3d::RIGHT, Vect3d::FRONT, material0));
    scene.addCollider(std::make_unique<Sphere>(150, Vect3d(300, 600, 0), material1));
    scene.addCollider(std::make_unique<Sphere>(150, Vect3d(0, 400, 0), material2));

    scene.addLight(PointLight(Vect3d(-100, 150, 200), Color::WHITE, 0.3));
    scene.addLight(PointLight(Vect3d(0, 150, 300), Color::YELLOW, 0.1));
    scene.addLight(PointLight(Vect3d(900, -100, 900), Color::GREEN, 0.2));

    auto image = computeImageMultiThreaded(width, height, scene);
    image.build("test");

    return 0;
}
