#include <iostream>
#include "engine/VCO.hpp"

namespace engine {
    void VCO::setFrequency(double freq) {
        float pitchOffset = m_masterPitchOffset + ((float)1/100.0) * m_fineTunePitchOffset;
        float oscFreq = utilities::semitoneShiftToFreq(freq, pitchOffset);

        logger->debug("id: {}, freq: {}, shiftedFreq: {}", getId(), freq, oscFreq);
        m_waveForm->setFrequency(oscFreq); 
    }

    double VCO::tick(double input) {
        float freqModVal = 0.0;

        for(const auto& m : m_modulators) {
            if(m->bypass()) continue;
            
            freqModVal += m->getLastOut();
        }

        m_lastOut = m_waveForm->getOutput(freqModVal);

        return m_lastOut;
    }
}