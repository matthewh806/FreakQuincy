#include <iostream>
#include "engine/VCO.hpp"

namespace engine {
    double VCO::tick() {
        float freqModVal = 0.0;

        for(const auto& m : m_modulators)
            freqModVal += m->getLastOut();

        return m_waveForm->getOutput(freqModVal);
    }
}