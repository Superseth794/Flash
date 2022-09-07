//
// Created by Jaraxus on 05/09/2022.
//

#ifndef FLASH_RANDOMVECTORGENERATOR_H
#define FLASH_RANDOMVECTORGENERATOR_H

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>

#include <random>

#include "utils/Vectors.h"

namespace flash::test {

class RandomVectorGenerator : public Catch::Generators::IGenerator<Vect3d> {
public:
    RandomVectorGenerator(Vect3d const& lower, Vect3d const& upper);

    const Vect3d &get() const override;

    bool next() override;

private:
    Vect3d                              m_current;
    std::uniform_real_distribution<>    m_distX;
    std::uniform_real_distribution<>    m_distY;
    std::uniform_real_distribution<>    m_distZ;
    std::random_device                  m_rand;
};

}

Catch::Generators::GeneratorWrapper<flash::Vect3d> randomVector(flash::Vect3d low, flash::Vect3d high);

#endif //FLASH_RANDOMVECTORGENERATOR_H
