#include <iostream>
#include "engine/VCO.hpp"

namespace engine {
    double VCO::tick() {
        float freqModVal = 0.0;

        for(const auto& m : m_modulators) {
            if(m->bypass()) continue;
            
            freqModVal += m->getLastOut();
        }

        m_lastOut = m_waveForm->getOutput(freqModVal);

        return m_lastOut;
    }
}