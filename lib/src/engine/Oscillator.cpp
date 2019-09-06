#include "engine/Oscillator.hpp"

namespace engine {

    Oscillator::Oscillator() {
        m_waveForm = std::unique_ptr<WaveForm>(new WaveForm());
    }

    Oscillator::Oscillator(WaveTypes wType, float freq) {
        m_waveForm = std::unique_ptr<WaveForm>(new WaveForm());
        m_waveForm->setWaveType(wType);
        m_waveForm->setFrequency(freq);
    }

    Oscillator::~Oscillator() {

    }
}

