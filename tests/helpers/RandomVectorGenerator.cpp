//
// Created by Jaraxus on 05/09/2022.
//

#include "RandomVectorGenerator.h"

namespace flash::test {

RandomVectorGenerator::RandomVectorGenerator(Vect3d const &lower, Vect3d const &upper) :
        m_rand(),
        m_current(),
        m_distX(lower.x, upper.x),
        m_distY(lower.y, upper.y),
        m_distZ(lower.z, upper.z) {
    static_cast<void>(RandomVectorGenerator::next());
}

const Vect3d &RandomVectorGenerator::get() const {
    return m_current;
}

bool RandomVectorGenerator::next() {
    m_current.x = m_distX(m_rand);
    m_current.y = m_distY(m_rand);
    m_current.z = m_distZ(m_rand);
    return true;
}

}

Catch::Generators::GeneratorWrapper<flash::Vect3d> randomVector(flash::Vect3d low, flash::Vect3d high) {
    return Catch::Generators::GeneratorWrapper<flash::Vect3d>(
            Catch::Detail::make_unique<flash::test::RandomVectorGenerator>(low, high)
    );
}