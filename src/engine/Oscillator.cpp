#include "engine/oscillator.hpp"

namespace engine {

    Oscillator::Oscillator() {
        m_waveForm = std::unique_ptr<WaveForm>(new WaveForm());
    }

    Oscillator::~Oscillator() {

    }

    void Oscillator::notePressed(float freq, bool legato) {
        m_waveForm->setFrequency(freq);
    }

    double Oscillator::tick() {
        m_waveForm->getOutput();
    }

}

