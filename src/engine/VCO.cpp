#include <iostream>
#include "engine/VCO.hpp"

namespace engine {
    
    VCO::VCO() {
        
    }

    VCO::~VCO() {}

    double VCO::tick() {
        double modVal = 1.0;

        for(const auto& m : m_modulators) {
            modVal *= m->getLastOut();
        }

        return m_waveForm->getOutput() * modVal;
    }
}