//
// Created by Jaraxus on 30/08/2022.
//

#include <chrono>
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

void computeImage(flash::PPMImage& image, flash::Scene const& scene, bool showProgress, bool randomizeRays) {
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
            image.setPixel(x, y, scene.cast(x / static_cast<double>(width), y / static_cast<double>(height), rdmSetup, randomizeRays));
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
        threads.emplace_back(computeImage, std::ref(images[i]), std::ref(scene), (i == 0), true);
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

    Scene scene("test", 1);

    auto& camera = scene.setCamera(Camera(Vect3d(0, 0, 0), width, height, M_PI / 180. * fov));

    auto materialW = std::make_shared<PhongMaterial>(Color::WHITE, 0.8, 0.5, 0., 8);
    auto material0 = std::make_shared<PhongMaterial>(Color::YELLOW, 0.8, 0.5, 0., 16);
    auto material1 = std::make_shared<PhongMaterial>(Color::MAGENTA, 0.8, 0.5, 0., 8);
    auto material2 = std::make_shared<PhongMaterial>(Color::CYAN, 0.8, 0.5, 0., 4);

    scene.addCollider(std::make_unique<Plane>(Vect3d(0, 0, -120), Vect3d::RIGHT, Vect3d::FRONT, materialW));

//    scene.addCollider(std::make_unique<Sphere>(50, Vect3d(-40, 200, 35.35), material0));
//    scene.addCollider(std::make_unique<Sphere>(50, Vect3d(0, 200, -35.35), material1));
//    scene.addCollider(std::make_unique<Sphere>(50, Vect3d(40.35, 200, 35.35), material2));

    scene.addLight(PointLight(Vect3d(0, 1000, 0), Color::WHITE, 0.65));
    scene.addLight(PointLight(Vect3d(-100, 150, 0), Color::WHITE, 0.65));
//    scene.addLight(PointLight(Vect3d(0, 150, 300), Color::YELLOW, 0.1));
//    scene.addLight(PointLight(Vect3d(900, -100, 900), Color::GREEN, 0.2));

    auto start = std::chrono::system_clock::now();

//    auto image = computeImageMultiThreaded(width, height, scene);
    PPMImage image(width, height);
    computeImage(image, scene, false, false);
    image.build("test");

    auto end = std::chrono::system_clock::now();

    std::cout << "Time elapsed: " << getTime(end - start) << std::endl;

    return 0;
}
