#include "engine/oscillator.hpp"

namespace engine {

    Oscillator::Oscillator() {
        m_waveForm = std::unique_ptr<WaveForm>(new WaveForm());
    }

    Oscillator::~Oscillator() {

    }
}

