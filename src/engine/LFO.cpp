#include "engine/LFO.hpp"
#include "engine/AudioSettings.hpp"

namespace engine {
    LFO::LFO() {
        m_rate = 1.0 / AudioSettings::getSampleRate();
        m_state = 0.0;
        m_free = true;
    }
    
    LFO::~LFO() {}

    void LFO::NotePressed(float freq, bool legato) {
        if(!free && !legato)
            m_state = 0.0;
    }

    void LFO::setFrequency(float freq) {
        if(freq < MIN_FREQUENCY) 
            freq = MIN_FREQUENCY;

        if(freq > MAX_FREQUENCY)
            freq = MAX_FREQUENCY;

        m_freq = freq;
    }
}